#ifndef MID2AGB_MIDI_H_
#define MID2AGB_MIDI_H_

#include <stdint.h>
#include "globals.h"

long parse_midi_header();

long read_track_and_chunksize();

int buffer_track_meta_events(Event *buffer, int max_events);

signed int is_music_note_event(Event *event);

signed int compare_event_maybe(Event *control_event, Event *meta_event);

int buffer_track_control_events(Event *buffer, int max_events);

#endif /* MID2AGB_MIDI_H_ */