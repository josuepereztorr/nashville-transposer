#ifndef MIDI_H
#define MIDI_H

// vendor
#include <portmidi.h>

// the max number of devices that can be connected
#define MAX_DEVICES 10

typedef struct
{
   int id;
   const PmDeviceInfo *device_info;
} MidiDevice;

// Initializes PortMidi and connects specifically to the Arturia MiniLab 3.
int midi_initialize(MidiDevice *device);

// Reads PmEvents from the open MIDI stream. Returns a nonzero int (PmError) for an error during reading operations.
PmEvent midi_read(void);

// Closes a MIDI stream. Returns pmNoError or a nonzero int (PmError) for a failed termination.
PmError midi_terminate(void);

#endif