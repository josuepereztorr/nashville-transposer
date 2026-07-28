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

typedef struct
{
   int count;
   MidiDevice *devices;
} ConnectedDevices;

/* Initializes PortMidi and loads all available devices into memory.
   Returns the number of devices found. */
int midi_initialize(void);

// Terminates the previous instance of PortMidi and then calls midi_initialize().
int midi_refresh(void);

// Opens a MIDI device for input. Returns pmNoError or a nonzero int (PmError) for a failed connection.
PmError midi_connect_device(int id);

// Reads PmEvents from the open MIDI stream. Returns a nonzero int (PmError) for an error during reading operations.
PmError midi_read(void);

// Closes a MIDI stream. Returns pmNoError or a nonzero int (PmError) for a failed termination.
PmError midi_terminate(void);

ConnectedDevices *midi_get_connected_devices(void);

#endif