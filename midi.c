#include "midi.h"

#include <stdio.h>

#include "globals.h"
#include "utils.h"

uint16_t midi_format_short;

uint16_t midi_number_of_tracks;

uint16_t midi_time_div;

long midi_header_end = 0;

long track_data_start;

int last_control_event_byte;

uint8_t sfile_num_blocks;

int midi_channel;

int negative_one_thing;

int starts_at_zero_thing;

/*
 * TODO: Implement this better, it only works for 4 char strings and is ugly besides
 */
signed int strcmp_input_file(char *compareStr) {
    signed int i = 0;

    do {
        if (compareStr[i] != fgetc(input_file_fp))
            return -1;
        ++i;
    }
    while (i < 4);
    return 0;
}

uint32_t read_variable_length_quantity() {
    uint32_t i = 0;
    int8_t byte;

    do {
        byte = (int8_t) fgetc(input_file_fp);
        i = ((byte & 0x7F) + i) << 7;
    } while (byte >= 0);
    return i + byte;
}

int read_variable_length_and_seek_past() {
    int result;
    result = fseek(input_file_fp, read_variable_length_quantity(), SEEK_CUR);
    if (result)
        print_error("%s", input_file_name);
    return result;
}

int move_to_track_start() {
    int result;

    result = fseek(input_file_fp, track_data_start, 0);
    if (result)
        print_error("%s", input_file_name);
    midi_absolute_time = 0;
    last_control_event_byte = -128;
    return result;
}

uint16_t read_short() {
    uint16_t result = 0;
    fread(&result, sizeof(uint16_t), 1, input_file_fp);
    return result;
}

uint32_t read_signed_24bit() {
    uint32_t result = 0;
    result = (uint32_t) getc(input_file_fp);
    result |= (uint32_t) getc(input_file_fp) << 8;
    result |= (uint32_t) getc(input_file_fp) << 16;

    return result;
}

uint32_t read_int() {
    uint32_t result;
    fread(&result, sizeof(uint32_t), 1, input_file_fp);
    return result;
}

long parse_midi_header() {
    /* Try seeking to the start */
    if (fseek(input_file_fp, 0, 0))
        print_error("%s", input_file_name);

    if (strcmp_input_file("MThd")) {
        /* Try seeking 128 bytes in (Why would the header ever be here? Seriously WTF) */
        if (fseek(input_file_fp, 128, 0))
            print_error("%s", input_file_name);
        if (strcmp_input_file("MThd"))
            print_error("%s", input_file_name);
    }

    /* Skip four bytes (dword 6 in MIDI) */
    fseek(input_file_fp, 4, SEEK_CUR);

    /* Determine MIDI format */
    midi_format_short = read_short();
    if (midi_format_short >= 2)
        print_error("'format_2' midi unsupported");

    /* Read the rest of the header information */
    midi_number_of_tracks = read_short();
    midi_time_div = read_short();

    /* Only timebase's in ticks per beat are supported; frames per second timediv unsupported */
    if (midi_time_div & 0x8000)
        print_error("%s", "timebase");

    midi_header_end = ftell(input_file_fp);
    return midi_header_end;
}

int check_second_parameter_needed(uint8_t byte) {
    uint8_t type_bits = byte & (uint8_t) 0xF0u;

    /* Parameter two is not used for event type 0xC or 0xD */
    if (type_bits == 0xC0u || type_bits == 0xD0u)
        return 2;

    /* The second parameter is used */
    return 3;
}

signed int control_event(uint8_t *type_and_channel, uint8_t *event_parameter) {
    uint8_t v4;
    signed int result;

    *type_and_channel = (uint8_t) fgetc(input_file_fp);

    /* Is this event a meta event? */
    if (*type_and_channel == 255)
        *event_parameter = (uint8_t) fgetc(input_file_fp);

    /*
     * MIDI channel event. Max type is 0xE, so all these events will be < 0xF0. The MIDI channel event is the upper 4
     * bits of this byte.
     */
    if (*type_and_channel < 0xF0u) {
        /* Is this event valid? */
        if (*type_and_channel >= 0x80u) {
            last_control_event_byte = *type_and_channel;
            *event_parameter = (uint8_t) fgetc(input_file_fp);
        } else {
            *event_parameter = *type_and_channel;
            *type_and_channel = last_control_event_byte;
        }
        return 1;
    }

    return 0;
}

int strcmp_midi_text(char *string) {
    long start_pos;
    int next_ch;

    /* Save position for later */
    start_pos = ftell(input_file_fp);
    read_variable_length_quantity();

    /* Compare text */
    while (*string && (next_ch = fgetc(input_file_fp), *string++ == next_ch));

    /* Try seeking back */
    if (fseek(input_file_fp, start_pos, 0))
        print_error("%s", input_file_name);

    /* Return 0 if equal, otherwise return the first unequal character */
    return *string;
}

int increment_blocks(Event *buffer, uint8_t type) {
    /* Create block event */
    buffer->type = type;
    buffer->param1 = sfile_num_blocks++;
    buffer->param2 = 0;

    /* Skip text event */
    return read_variable_length_and_seek_past();
}

signed int next_meta_event(Event *buffer) {
    int numerator;
    int denom_exponent;
    int denominator;
    signed int clock_ticks;
    int time_sig;
    uint8_t type_byte;
    uint8_t parameter;

    /* Convert delta time into absolute time */
    midi_absolute_time += read_variable_length_quantity();
    buffer->time = midi_absolute_time;
    if (control_event(&type_byte, &parameter)) {
        if (check_second_parameter_needed(type_byte) == 3) {
            return fgetc(input_file_fp);
        }
        return -1;
    }

    /* Skip any SysEx event */
    if (type_byte == 0xF0u || type_byte == 0xF7u) {
        read_variable_length_and_seek_past();
        return -1;
    }

    /* If it isn't a meta event, we have an invalid MIDI file, as we've check all other possible event types */
    if (type_byte != 255)
        print_error("%s", input_file_name);

    if (parameter < 1u || parameter > 0xFu) {
        /* Interpret important meta events */
        switch (parameter) {
            case 0x2Fu:
                /* End of track */
                fgetc(input_file_fp);
                buffer->type = 0xFFu;
                buffer->param1 = 0;
                buffer->param2 = 0;
                break;
            case 0x51u:
                /* Tempo */
                fgetc(input_file_fp);
                buffer->type = 25;
                buffer->param1 = 0;
                buffer->param2 = read_signed_24bit();
                break;
            case 0x58u:
                /* Time signature */
                fgetc(input_file_fp);
                buffer->type = 24;
                buffer->param1 = 0;

                /* Convert to clock ticks */
                numerator = fgetc(input_file_fp);
                buffer->param2 = 96 * numerator * (uint32_t) option_clock_per_beat;

                /* Calculate proper time signature denomintator */
                denom_exponent = fgetc(input_file_fp);
                /* pow(2, denom_exponent) */
                denominator = 1 << denom_exponent;

                /* Ignore metronome */
                fgetc(input_file_fp);

                /* Ignore 32nds */
                fgetc(input_file_fp);

                clock_ticks = buffer->param2;
                time_sig = clock_ticks / denominator;
                buffer->param2 = (uint32_t) time_sig;

                if ((denominator - 1) & clock_ticks || time_sig <= 0 || time_sig >= 65536)
                    print_error("%s", "time sign");
                break;
            default:                                  // Skip
                read_variable_length_and_seek_past();
                return -1;
        }
        return 0;
    }
    else {
        /* Text meta event handler. These check for special text events which handle looping within a MIDI file */

        /* Loop start marker */
        if (!strcmp_midi_text("[")) {
            increment_blocks(buffer, 20);
            return 0;
        }

        /* No idea */
        if (!strcmp_midi_text("][")) {
            increment_blocks(buffer, 19);
            return 0;
        }
        /* Loop end marker (goto [) */
        if (!strcmp_midi_text("]")) {
            increment_blocks(buffer, 18);
            return 0;
        }

        /* No idea */
        if (!strcmp_midi_text(":")) {
            increment_blocks(buffer, 17);
            return 0;
        }

        /* No text event */
        read_variable_length_and_seek_past();
        return -1;
    }
}

// Returns 0 if not at track end, 255 if it is
int track_end(Event *buffer) {
    // Basically a very complicated way of checking for 0xFF at buffer[0]
    // Yeah...

    return -((uint8_t) (buffer->type - 255) < 1);
}

signed int is_music_note_event(Event *event) {
    char event_type; // al@1
    signed int result; // eax@3

    event_type = event->type;

    // Notes are numbered between 0 and 127, with 0x40 being added when copying from the MIDI file
    if ((uint8_t) event_type < 0x40u || (uint8_t) event_type >= 0xC0u)
        result = 0;
    else
        result = -1;
    return result;
}

signed int compare_event_maybe(Event *control_event, Event *meta_event) {
    char meta_event_type;
    char control_event_type;
    char control_event_param;
    char meta_event_param;

    // Control event is before the meta event
    if (meta_event->time > control_event->time)
        return -1;

    // Control event is after the meta event
    if (meta_event->time < control_event->time)
        return 1;

    control_event_type = control_event->type;
    meta_event_type = meta_event->type;

    if (control_event_type < (uint8_t) meta_event_type)
        return -1;
    if (control_event_type > (uint8_t) meta_event_type)
        return 1;

    // TODO: Does this ever happen?
    if (control_event_type == 0x25 || control_event_type == 1) {
        meta_event_param = meta_event->param1;
        control_event_param = control_event->param1;
        if (meta_event_param > (uint8_t) control_event_param)
            return -1;
        if (meta_event_param < (uint8_t) control_event_param)
            return 1;
    }
    else {
        // Controller event
        if (control_event_type == 0x22 && meta_event->param1 != control_event->param1)
            return 1;
    }
    return 0;
}

uint32_t read_track_and_chunksize() {
    FILE *v0; // esi@4
    int32_t v1; // eax@5
    long result; // eax@8

    if (fseek(input_file_fp, Offset, 0))
        print_error("%s", input_file_name);
    if (strcmp_input_file("MTrk")) {
        v0 = input_file_fp;
        do {
            v1 = read_int();
            if (fseek(v0, v1, 1))
                print_error("%s", input_file_name);
            v0 = input_file_fp;
        }
        while (strcmp_input_file("MTrk"));
    }
    Offset = read_int();
    result = ftell(input_file_fp);
    track_data_start = result;
    Offset += result;
    return result;
}

int assert_a_leq_b(int a1, int a2) {
    int result; // eax@1

    result = a1;
    if (a2 <= a1)
        print_error("MIDI�C�x���g���������܂��B");
    return result;
}

int buffer_track_meta_events(char *buffer, int max_events) {
    char *events_buffer; // ebx@1
    int i; // edi@1
    int v4; // eax@4
    int end_of_track; // eax@4

    i = 0;
    move_to_track_start();
    events_buffer = buffer;
    do {
        assert_a_leq_b(i, max_events);              // make sure there is space in the buffer
        while (next_meta_event(events_buffer));
        v4 = i;
        events_buffer += 12;                        // Each event in the mid2agb buffer takes up 12 bytes.
        // dword time (NOT delta time), dword for type, dword for parameter
        ++i;
        end_of_track = track_end((Event *) &buffer[12 * v4]);
    }
    while (!end_of_track);
    return end_of_track;
}

signed int find_note_finish(Event *buffer) {
    signed int result; // eax@9
    char v2; // al@12
    char parameter; // [sp+6h] [bp-2h]@1
    char type_byte; // [sp+7h] [bp-1h]@1

    buffer->param2 += read_variable_length_quantity();
    if (control_event((uint8_t *) &type_byte, (int) &parameter)) {
        if ((type_byte & 0xF0) == 0x80u) {
            fgetc(input_file_fp);
            if ((type_byte & 0xF) == midi_channel) {
                if (*(_BYTE * )(buffer + 4) - parameter == 64) {
                    --*(_DWORD * ) & buffer_512[4 * *(_BYTE * )(buffer + 4) - 256];
                    if (!*(_DWORD * ) & buffer_512[4 * *(_BYTE * )(buffer + 4) - 256])
                        return 0;
                }
            }
            return -1;
        }
        if ((type_byte & 0xF0) == 0x90u) {
            --input_file_fp->_cnt;
            if (input_file_fp->_cnt < 0)
                v2 = _filbuf(input_file_fp);
            else
                v2 = *input_file_fp->_ptr++;
            if ((type_byte & 0xF) == midi_channel && *(_BYTE * )(buffer + 4) - parameter == 64) {
                if (v2)
                    return 0;
                --*(_DWORD * ) & buffer_512[4 * *(_BYTE * )(buffer + 4) - 256];
                if (!*(_DWORD * ) & buffer_512[4 * *(_BYTE * )(buffer + 4) - 256])
                    return 0;
            }
            return -1;
        }
        if (check_second_parameter_needed(type_byte) == 3) {
            --input_file_fp->_cnt;
            if (input_file_fp->_cnt < 0) {
                _filbuf(input_file_fp);
                result = -1;
            }
            else {
                ++input_file_fp->_ptr;
                result = -1;
            }
            return result;
        }
        return -1;
    }
    if (type_byte == -16 || type_byte == -9) {
        read_variable_length_and_seek_past();
        return -1;
    }
    if (type_byte != -1)
        print_error(unk_40C0F0, input_file_name);
    if (parameter == 47)
        print_error("KEYOFF�C�x���g������܂��");
    read_variable_length_and_seek_past();
    return -1;
}

int find_when_note_finishes_and_return(char *buffer) {
    char store; // bl@1
    __int32 prev_pos; // edi@1
    int result; // eax@3

    prev_pos = ftell(input_file_fp);
    store = last_control_event_byte;
    *((_DWORD *) buffer + 2) = 0;
    ++*(_DWORD * ) & buffer_512[4 * (unsigned __int8)buffer[4] - 256];
    while (find_note_finish((int) buffer));
    result = fseek(input_file_fp, prev_pos, 0);
    if (result)
        print_error(unk_40C0E4, input_file_name);
    last_control_event_byte = store;
    return result;
}

int buffer_track_control_events(char *a1, int a2) {
    signed int i; // eax@1
    int j; // ebx@3
    char *v4; // esi@3
    int v5; // eax@6
    int result; // eax@6

    move_to_track_start();
    i = 0;                                        // zero out buffer
    do {
        i += 4;
        *(_DWORD * ) & buffer_512[i - 4] = 0;
    }
    while (i < 512);
    j = 0;
    v4 = a1;
    negative_one_thing = -1;
    starts_at_zero_thing = 0;
    do {
        assert_a_leq_b(j, a2);
        while (next_control_event((Event *) v4));
        v5 = j;
        v4 += 12;
        ++j;
        result = track_end((Event *) &a1[12 * v5]);
    }
    while (!result);
    return result;
}

signed int next_control_event(Event *buffer) {
    uint8_t type_byte;
    uint8_t parameter;

    midi_absolute_time += read_variable_length_quantity();
    buffer->time = midi_absolute_time;

    if (control_event(&type_byte, &parameter)) {
        /* Check if this event is on the current midi channel */
        if ((type_byte & 0xF) == midi_channel) {
            switch (type_byte & 0xF0) {
                default:
                    if (check_second_parameter_needed(type_byte) != 3)
                        return -1;
                    fgetc(input_file_fp);
                    return -1;
                case 0x90:
                    /* Note on */
                    buffer->param1 = (uint8_t) fgetc(input_file_fp);

                    if (buffer->param1) {
                        buffer->type = parameter + (uint8_t) 0x40;
                        find_when_note_finishes_and_return((char *) buffer);
                        if (buffer->param2) {
                            if (parameter < (uint8_t) negative_one_thing)
                                negative_one_thing = parameter;
                            if (parameter > (uint8_t) starts_at_zero_thing)
                                starts_at_zero_thing = parameter;
                            return 0;
                        }
                    }
                    return -1;
                case 0xB0:
                    /* Controller event */
                    buffer->type = 0x22u;
                    buffer->param1 = parameter;
                    buffer->param2 = (uint8_t) fgetc(input_file_fp);
                    break;
                case 0xC0:
                    /* Program change */
                    buffer->type = 0x21u;
                    buffer->param2 = 0;
                    buffer->param1 = parameter;
                    break;
                case 0xE0:
                    /* Pitch bend */
                    buffer->type = 0x23u;
                    buffer->param1 = parameter;
                    buffer->param2 = (uint8_t) fgetc(input_file_fp);
                    break;
            }
            return 0;
        }
        if (check_second_parameter_needed(type_byte) == 3) {
            fgetc(input_file_fp);
            return -1;
        }
        return -1;
    }

    if (type_byte == -16 || type_byte == -9) {
        read_variable_length_and_seek_past();
        return -1;
    }

    if (type_byte != -1)
        print_error("%s", input_file_name);

    if (parameter == 47) {
        fgetc(input_file_fp);
        buffer->param1 = 0;
        buffer->param2 = 0;
        buffer->type = 255;
        return 0;
    }

    read_variable_length_and_seek_past();
    return -1;
}