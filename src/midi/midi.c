/*
 * ============================================================
 * File    : midi.c
 * Project : Nashville Transposer
 * ============================================================
 * Author   : Josue Perez Torres
 * Created  : 07-28-2026
 * Modified : 07-28-2026
 * Version  : 1.0.0
 * ============================================================
 * Description :
 *      Manages device discovery through the PortMidi API.
 * ============================================================
 * Dependencies:
 *      portmidi.h (brew) - handles MIDI devices into I/O.
 * ============================================================
 */

// ─────────────────────────────────────────────────────
// INCLUDES
// ─────────────────────────────────────────────────────

// file header
#include "../midi/midi.h"

// standard library
#include <stdio.h>
#include <string.h>

// vendor
#include <portmidi.h>

// ─────────────────────────────────────────────────────
// CONSTANT & MACROS
// ─────────────────────────────────────────────────────

#define MAX_BUFFERED_EVENTS 512

// ─────────────────────────────────────────────────────
// TYPE DEFINITIONS
// ─────────────────────────────────────────────────────

// ─────────────────────────────────────────────────────
// PRIVATE VARIABLES
// ─────────────────────────────────────────────────────

// Represents an open midi connection to the selected midi device
static PortMidiStream *stream = NULL;

// ─────────────────────────────────────────────────────
// PRIVATE FUNCTION PROTOTYPES
// ─────────────────────────────────────────────────────

static int get_mini_lab_id(int num_of_devices);
static void print_buffer(PmEvent buffer[]);

// ─────────────────────────────────────────────────────
// PUBLIC FUNCTIONS
// ─────────────────────────────────────────────────────

// Initializes PortMidi and connects specifically to the Arturia MiniLab 3.
int midi_initialize(MidiDevice *device)
{
    /* PortMidi is designed to support multiple interfaces (such as  ALSA, CoreMIDI and WinMM).
    It is possible to return pmNoError because there are no supported interfaces. In that case,
    zero devices will be available.*/
    PmError error = Pm_Initialize();

    if (error != pmNoError)
    {
        // no need to run midi_terminate() since no portMidi fucntion got init
        fprintf(stderr, "ERROR: failed to initialize midi - Pm_Initialize()\n");
        return -1;
    }

    // returns the total number of devices (virtual/hardwired), no filter
    int num_of_devices = Pm_CountDevices();

    if (num_of_devices == 0)
    {
        fprintf(stderr, "ERROR: no devices found - Pm_CountDevices()\n");
        midi_terminate();
        return -1;
    }

    // adds PmDeviceInfo structs to the devices array, filtered by input devices.
    int id = get_mini_lab_id(num_of_devices);

    if (id == -1)
    {
        fprintf(stderr, "ERROR: failed to retrieve the id for Mini Lab 3 - get_mini_lab_id()\n");
        midi_terminate();
        return -1;
    }

    // pass the device info into the MidiDevice ptr
    const PmDeviceInfo *device_info_ptr = Pm_GetDeviceInfo(id);
    device->id = id;
    device->device_info = device_info_ptr;

    // connect device
    error = Pm_OpenInput(&stream, id, NULL, MAX_BUFFERED_EVENTS, NULL, NULL);

    if (error != pmNoError)
    {
        fprintf(stderr, "ERROR: failed to connect to Mini Lab 3 - Pm_OpenInput()\n");
        midi_terminate();
        return -1;
    }

    return 1;
}

// check for 0 events
PmEvent midi_read(void)
{
    PmEvent event_buffer[1] = {0};
    int events_per_read = 1;

    // returns the number of PmEvents read or a PmError
    PmError error = Pm_Read(stream, event_buffer, events_per_read);

    if (error < 0)
    {
        fprintf(stderr, "ERROR: error reading PmEvent\n");
    }

    return event_buffer[0];
}

PmError midi_terminate(void)
{
    PmError error = (PmError){0};

    // can't close a stream that wasn't been created.
    if (stream != NULL)
    {
        error = Pm_Close(stream);

        if (error != pmNoError)
        {
            fprintf(stderr, "ERROR: error closing Pm_Close()\n");
            return error;
        };

        // reset stream - ptrs are NULL, structs are {0}
        stream = NULL;
    }

    error = Pm_Terminate();

    if (error != pmNoError)
    {
        return error;
    }

    return pmNoError;
}

// ─────────────────────────────────────────────────────
// PRIVATE FUNCTIONS
// ─────────────────────────────────────────────────────

// function that only adds the Arturia Mini Lab 3 as an input.
static int get_mini_lab_id(int num_of_devices)
{
    for (int device_id = 0; device_id < num_of_devices; device_id++)
    {
        // Pm_GetDeviceInfo - takes an id as a parameter and returns a pointer to a PmDeviceInfo struct
        const PmDeviceInfo *device_info = Pm_GetDeviceInfo(device_id);

        // if id is out of range or if the device designates a deleted virtual device, the function returns NULL.
        if (device_info == NULL)
        {
            continue;
        }

        int result = strcmp(device_info->name, "Minilab3 MIDI");

        if (device_info->input && result == 0)
        {
            return device_id;
        }
    }

    return -1;
}

// ─────────────────────────────────────────────────────
// DEBUG PRINTING
// ─────────────────────────────────────────────────────

// Prints a the raw MIDI message as well as the unpacked Message, data1, and data2.
static void print_buffer(PmEvent buffer[])
{
    // raw bytes come back across multiple events
    printf("32-Bit Message: %x\n", buffer[0].message);

    // extracted 3-byte midi message (status, data1, data2)
    printf("Status: %d  Note: %d  Velocity: %d\n\n",
           // unpacks the status out of the 32-bit integer (4 bytes)
           Pm_MessageStatus(buffer[0].message),
           // unpacks data 1 out of the 32-bit integer (4 bytes)
           Pm_MessageData1(buffer[0].message),
           // unpacks data 1 out of the 32-bit integer (4 bytes)
           Pm_MessageData2(buffer[0].message));
}