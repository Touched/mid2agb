#ifndef MID2AGB_MIDI_H_
#define MID2AGB_MIDI_H_

#include <stdint.h>

long parse_midi_header();
uint32_t read_track_and_chunksize();

#endif /* MID2AGB_MIDI_H_ */