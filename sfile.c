#include "sfile.h"
#include "midi.h"

int print_sfile_header() {
    fprintf(output_file_fp, "\t.include \"MPlayDef.s\"\n\n");
    fprintf(output_file_fp, "\t.equ\t%s_grp, voicegroup%03u\n", assembler_label, option_voicegroup);
    fprintf(output_file_fp, "\t.equ\t%s_pri, %u\n", assembler_label, option_priority);

    if (option_reverb >= 0)
        fprintf(output_file_fp, "\t.equ\t%s_rev, reverb_set+%u\n", assembler_label, option_reverb);
    else
        fprintf(output_file_fp, "\t.equ\t%s_rev, 0\n", assembler_label);

    fprintf(output_file_fp, "\t.equ\t%s_mvl, %u\n", assembler_label, option_volume);
    fprintf(output_file_fp, "\t.equ\t%s_key, %u\n", assembler_label, midi_key);
    fprintf(output_file_fp, "\t.equ\t%s_tbs, %u\n", assembler_label, option_clock_per_beat);
    fprintf(output_file_fp, "\t.equ\t%s_exg, %u\n", assembler_label, option_exact_gate_time);
    fprintf(output_file_fp, "\t.equ\t%s_cmp, %u\n", assembler_label, option_compression_enabled);

    fprintf(output_file_fp, "\n\t.section .rodata\n");
    fprintf(output_file_fp, "\t.global\t%s\n", assembler_label);

    return fprintf(output_file_fp, "\t.align\t2\n");
}

int print_sfile_footer() {
    signed int v0;
    int v1;
    FILE *v2;
    signed int v3;
    signed int i;
    int v5;
    signed int v6;
    signed int v7;

    fprintf(output_file_fp, "\n@******************************************************@\n");
    fprintf(output_file_fp, "\t.align\t2\n");
    fprintf(output_file_fp, "\n%s:\n", assembler_label);
    if (!option_b)
        sfile_num_blocks = 0;
    fprintf(output_file_fp, "\t.byte\t%u\t@ NumTrks\n", sfile_num_tracks - 1);
    fprintf(output_file_fp, "\t.byte\t%u\t@ NumBlks\n", sfile_num_blocks);
    fprintf(output_file_fp, "\t.byte\t%s_pri\t@ Priority\n", assembler_label);
    fprintf(output_file_fp, "\t.byte\t%s_rev\t@ Reverb.\n", assembler_label);
    fprintf(output_file_fp, "\n");
    fprintf(output_file_fp, "\t.word\t%s_grp\n", assembler_label);
    v0 = 1;
    fprintf(output_file_fp, "\n");
    if (sfile_num_tracks <= 1)                  // Output track pointers
    {
        v2 = output_file_fp;
    }
    else {
        v1 = assembler_label;
        v2 = output_file_fp;
        do {
            v3 = v0++;
            fprintf(v2, "\t.word\t%s_%u\n", v1, v3);
            v1 = assembler_label;
            v2 = output_file_fp;
        }
        while (v0 < sfile_num_tracks);
    }
    for (i = 1; i <= sfile_num_blocks; ++i) {
        v6 = 1;
        fprintf(v2, "\n");
        v2 = output_file_fp;
        v5 = assembler_label;
        if (sfile_num_tracks > 1) {
            do {
                v7 = v6++;
                fprintf(v2, "\t.word\t%s_%u_B%u\n", v5, v7, i);
                v5 = assembler_label;
                v2 = output_file_fp;
            }
            while (v6 < sfile_num_tracks);
        }
    }
    return fprintf(v2, "\n\t.end\n");
}

int print_sfile_body() {
    int result; // eax@1
    signed int current_track; // esi@1
    char v2; // cl@3
    int sfile_current_track; // ecx@4
    int v4; // ecx@8
    unsigned __int8
    v5; // sf@8
    unsigned __int8
    v6; // of@8

    Offset = midi_header_end;
    read_track_and_chunksize();
    current_track = 1;
    buffer_track_meta_events((char *) meta_events_buffer, 1000);// only 1000 events can fit in the 12k buffer (12 bytes per event)
    result = midi_header_end;
    Offset = midi_header_end;
    sfile_num_tracks = 1;
    if (midi_number_of_tracks >= 1) {
        LOOP:
        read_track_and_chunksize();
        midi_channel = 0;
        while (1) {
            buffer_track_control_events((char *) control_events_buffer, 10000);
            result = (int) meta_events_buffer;
            v2 = midi_channel;
            if (negative_one_thing != -1) {
                merge_buffers_maybe(control_events_buffer, meta_events_buffer, merged_events_buffer, 10000);
                sfile_current_track = sfile_num_tracks;
                if (sfile_num_tracks <= 1)            // First track
                {
                    remove_tempo_events_from_buffer(meta_events_buffer);
                    sfile_current_track = sfile_num_tracks;
                }
                printf("Track%d = Midi-Ch.%d\n", sfile_current_track,(
                unsigned __int8)midi_channel + 1);// Print conversion process to stdout

                // Conversions and the like performed here before printing the track
                convert_event_times(merged_events_buffer);
                adjust_times_something(merged_events_buffer, control_events_buffer, 10000);
                split_note_into_on_off_events_maybe(control_events_buffer, merged_events_buffer, 10000);
                mystery1(merged_events_buffer, control_events_buffer, 10000);
                mystery2(control_events_buffer, merged_events_buffer, 10000);
                swap_event_buffers(&merged_events_buffer, &control_events_buffer);
                increment_counter_when_type24_something(control_events_buffer);
                if (option_compression_enabled)
                    compress_events_probably(control_events_buffer);
                print_sfile_track(control_events_buffer);
                v4 = sfile_num_tracks;
                result = sfile_num_tracks++ + 1;
                v6 = __SETO__(v4, 16);
                v5 = v4 - 16 < 0;
                v2 = midi_channel;
                if (!(v5 ^ v6))
                    break;
            }
            midi_channel = v2 + 1;
            if ( (unsigned __int8)midi_channel >= 0x10u )
            {
                ++current_track;
                if (current_track <= midi_number_of_tracks)
                    goto LOOP;
                return result;
            }
        }
    }
    return result;
}

signed int print_sfile_track(Event *a1) {
    signed int v1; // esi@1
    char *v2; // edi@2
    Event *v3; // eax@5
    int v4; // ebx@10
    Event *v5; // edi@11
    signed int v6; // eax@11
    int v7; // ST10_4@18
    Event *v8; // esi@19
    int v9; // eax@27
    int v10; // ST10_4@39
    int v11; // eax@41
    int v13; // [sp-4h] [bp-14h]@11
    signed int v14; // [sp-4h] [bp-14h]@20

    fprintf(
            output_file_fp,
            "\n@**************** Track %u (Midi-Chn.%u) ****************@\n\n",
            sfile_num_tracks,
            (
    unsigned __int8)midi_channel + 1);
    v1 = 0;
    fprintf(output_file_fp, "%s_%u:\n", assembler_label, sfile_num_tracks);
    sub_402A10(dword_40DEC0);
    dword_40DEE0 = 0;
    dword_40DEFC = 0;
    dword_40DF04 = 0;
    dword_40DF20 = 0;
    dword_40DF30 = 96 * clock_per_beat_flag;
    dword_40DEF8 = 0;
    dword_40DF14 = 0;
    *(_DWORD *) dword_40DF10 = 0;
    dword_40DF18 = 0;
    reset_something();
    if (!is_music_note_event(a1)) {
        v2 = &a1->type;
        while (*v2 != 34 || v2[1] != 7) {
            v3 = (Event *) (v2 + 8);
            v2 += 12;
            ++v1;
            if (is_music_note_event(v3))
                goto LABEL_8;
        }
        v1 = -1;
    }
    LABEL_8:
    if (v1 >= 0)
        fprintf_and_reset("\tVOL   , 127*%s_mvl/mxv", assembler_label);
    v4 = 0;
    if (!track_end(a1)) {
        do {
            v5 = &a1[v4];
            v6 = is_music_note_event(&a1[v4]);
            v13 = (int) &a1[v4];
            if (v6) {
                sub_401980(v13);
            }
            else {
                if (sub_404FF0(v13)) {
                    if (dword_40DF24)
                        fprintf_and_reset("PEND");
                    dword_40DF24 = 0;
                }
                if (sub_404FD0((int) &a1[v4])) {
                    v7 = dword_40DF20++;
                    fprintf(output_file_fp, "@ %03u   ----------------------------------------\n", v7);
                }
                v8 = &a1[v4] + 4;
                switch (a1[v4].type) {
                    default:
                        v14 = v5->time;
                        goto LABEL_40;
                    case 1:
                        sub_401B40((int) &a1[v4]);
                        break;
                    case 0x11:
                        sub_402790((int) &a1[v4]);
                        break;
                    case 0x12:
                        fprintf_and_reset("GOTO");
                        sub_4029C0("%s_%u_B%u", assembler_label, sfile_num_tracks, dword_40DF04);
                        sub_402790((int) &a1[v4]);
                        break;
                    case 0x13:
                        fprintf_and_reset("GOTO");
                        sub_4029C0("%s_%u_B%u", assembler_label, sfile_num_tracks, dword_40DF04);
                        sub_402790((int) &a1[v4]);
                        dword_40DF04 = dword_40DEFC;
                        break;
                    case 0x14:
                        sub_402790((int) &a1[v4]);
                        dword_40DF04 = dword_40DEFC;
                        break;
                    case 0x15:
                        dword_40DF30 = a1[v4].param2;
                        sub_402830(&a1[v4].time);
                        break;
                    case 0x16:
                        v9 = a1[v4].param2;
                        if (v9 < 0) {
                            fprintf(output_file_fp, "%s_%u_%03lu:\n", assembler_label, sfile_num_tracks, v9 & 0x7FFFFFFF);
                            reset_something();
                            dword_40DF24 = 1;
                        }
                        v14 = v5->time;
                        goto LABEL_40;
                    case 0x17:
                        fprintf_and_reset("PATT");
                        sub_4029C0("%s_%u_%03lu", assembler_label, sfile_num_tracks, a1[v4].param2);
                        if (!sub_404FF0((int) &a1[v4 + 1])) {
                            do {
                                ++v8;
                                ++v4;
                                if (LOBYTE(v8->time) == 49)
                                    dword_40DEE0 = BYTE1(v8->time);
                            }
                            while (!sub_404FF0((int) &v8->param2));
                        }
                        reset_something();
                        break;
                    case 0x19:
                        fprintf_and_reset("TEMPO , %u*%s_tbs/2", 60000000 / a1[v4].param2, assembler_label);
                        v14 = v5->time;
                        goto LABEL_40;
                    case 0x21:
                        sub_402840(&a1[v4].time, "VOICE ", "%u", a1[v4].param1);
                        break;
                    case 0x22:
                        sub_401C10((int) &a1[v4]);
                        break;
                    case 0x23:
                        sub_402840(&a1[v4].time, "BEND  ", "c_v%+d", a1[v4].param2 - 64);
                        break;
                    case 0x31:
                        v10 = a1[v4].param1;
                        dword_40DEE0 = a1[v4].param1;
                        fprintf_and_reset("KEYSH , %s_key%+d", assembler_label, v10);
                        v14 = v5->time;
                    LABEL_40:
                        sub_402A10(v14);
                        break;
                }
            }
            v11 = 3 * v4++ + 3;
        }
        while (!track_end((Event *) ((char *) a1 + 4 * v11)));
    }
    return fprintf_and_reset("FINE");
}