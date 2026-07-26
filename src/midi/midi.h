#ifndef MIDI_H
#define MIDI_H

// vendor
#include <portmidi.h>

/* Initializes porMidi and loads all available devices into memory.
   Returns the number of devices found. */
int midi_initialize();

// Closes a MIDI stream. Returns pmNoError or a nonzero int (PmError) for a failed termination.
PmError midi_terminate();

// Opens a MIDI device for input. Returns pmNoError or a nonzero int (PmError) for a failed connection.
PmError midi_connect_device();

// Reads PmEvents from the open MIDI stream. Returns a nonzero int (PmError) for an error during reading operations.
PmError midi_read(void (*external_function)());

#endif