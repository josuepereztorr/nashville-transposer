/*
 * ============================================================
 * File    : midi.h
 * Project : Nashville Transposer
 * ============================================================
 * Author   : Josue Perez Torres
 * Created  : 07-28-2026
 * Modified : 07-28-2026
 * Version  : 1.0.0
 * ============================================================
 * Description:
 *     Public interface for MIDI device connection, reading,
 *     and termination via the PortMidi API.
 * ============================================================
 * Dependencies:
 *     portmidi.h (brew) - MIDI device I/O.
 * ============================================================
 */

#ifndef MIDI_H
#define MIDI_H

// ------------------------------------------------------------
// INCLUDES
// ------------------------------------------------------------

// vendor
#include <portmidi.h>

// ------------------------------------------------------------
// TYPE DEFINITIONS
// ------------------------------------------------------------

typedef struct
{
   int id;
   const PmDeviceInfo *device_info;
} MidiDevice;

// ------------------------------------------------------------
// PUBLIC FUNCTION PROTOTYPES
// ------------------------------------------------------------

// Initializes PortMidi and connects specifically to the Arturia MiniLab 3.
int midi_initialize(MidiDevice *device);

// Reads PmEvents from the open MIDI stream. Returns a nonzero int (PmError) for an error during reading operations.
PmEvent midi_read(void);

// Closes a MIDI stream. Returns pmNoError or a nonzero int (PmError) for a failed termination.
PmError midi_terminate(void);

#endif