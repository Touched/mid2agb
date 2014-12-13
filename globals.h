#ifndef MID2AGB_GLOBALS_H_
#define MID2AGB_GLOBALS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint32_t time;
    uint8_t type;
    uint8_t param1;
    uint16_t padding;
    uint32_t param2;
} Event;

/*
 * Global options
 */
extern int option_b, option_exact_gate_time, option_compression_enabled, option_clock_per_beat;

extern Event *control_events_buffer;

extern Event *merged_events_buffer;

extern Event *meta_events_buffer;

extern uint32_t *buffer_512;

extern FILE *input_file_fp;

extern FILE *output_file_fp;

extern char *input_file_name;

extern char *output_file_name;

extern int option_voicegroup;

extern int option_priority;

extern int option_reverb;

extern int option_volume;

extern char *assembler_label;

extern uint16_t midi_format_short;

extern uint16_t midi_number_of_tracks;

extern uint16_t midi_time_div;

extern long midi_header_end;

extern uint32_t midi_absolute_time;

extern uint16_t midi_format_short;

extern uint16_t midi_number_of_tracks;

extern uint16_t midi_time_div;

extern long midi_header_end;

extern long track_data_start;

extern uint8_t last_control_event_byte;

extern uint8_t sfile_num_blocks;

extern int midi_channel;

extern int negative_one_thing;

extern int starts_at_zero_thing;

extern long Offset;

#endif /* MID2AGB_GLOBALS_H_ */