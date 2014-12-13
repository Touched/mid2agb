#include "globals.h"

Event *control_events_buffer = NULL;

Event *merged_events_buffer = NULL;

Event *meta_events_buffer = NULL;

char *buffer_512 = NULL;

FILE *input_file_fp = NULL;

FILE *output_file_fp = NULL;

char *input_file_name = NULL, *output_file_name = NULL;

char *assembler_label = NULL;

int option_voicegroup = 0;
int option_priority = 0;
int option_reverb = INT32_MAX;
int option_volume = 127;
int option_b = false;
int option_exact_gate_time = false;
int option_compression_enabled = true;
int option_clock_per_beat = 1;

uint32_t midi_absolute_time;