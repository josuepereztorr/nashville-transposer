#ifndef MIDI_H
#define MIDI_H

// vendor
#include <portmidi.h>

#define MAX_DEVICES 10

typedef struct
{
   int id;
   const PmDeviceInfo *device_info;
} MidiDevice;

typedef struct
{
   int count;
   const MidiDevice *devices;
} ConnectedDevices;

/* Initializes PortMidi and loads all available devices into memory.
   Returns the number of devices found. */
int midi_initialize();

//
int midi_refresh();

// Closes a MIDI stream. Returns pmNoError or a nonzero int (PmError) for a failed termination.
PmError midi_terminate();

// Opens a MIDI device for input. Returns pmNoError or a nonzero int (PmError) for a failed connection.
PmError midi_connect_device();

const MidiDevice *midi_get_devices();

// Opens the default MIDI device for input. Returns pmNoError or a nonzero int (PmError) for a failed connection.
// PmError midi_connect_default_device();

// Reads PmEvents from the open MIDI stream. Returns a nonzero int (PmError) for an error during reading operations.
PmError midi_read(void (*external_function)());

void print_devices_arr(const MidiDevice *devices);

#endif