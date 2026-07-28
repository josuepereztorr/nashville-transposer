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

// responsible for holding the devices array and it's size.
static ConnectedDevices conn_devices = {0};

// stores all connected input devices
static MidiDevice devices[MAX_DEVICES] = {0};

// shows the number of available input devices
static int input_device_count = 0;

// Represents an open midi connection to the selected midi device
static PortMidiStream *stream = NULL;

// ─────────────────────────────────────────────────────
// PRIVATE FUNCTION PROTOTYPES
// ─────────────────────────────────────────────────────

static void add_devices(int num_of_devices);
static void print_buffer(PmEvent buffer[]);
static void print_devices(void);
static void print_devices_arr(const MidiDevice devices[]);

// ─────────────────────────────────────────────────────
// PUBLIC FUNCTIONS
// ─────────────────────────────────────────────────────

/* Initializes PortMidi and loads all available devices into memory.
   Returns the number of devices found. */
int midi_initialize(void)
{
    /* PortMidi is designed to support multiple interfaces (such as  ALSA, CoreMIDI and WinMM).
    It is possible to return pmNoError because there are no supported interfaces. In that case,
    zero devices will be available.*/
    PmError error = Pm_Initialize();

    // fprintf(stderr, "DEBUG: midi_initialize: init successful\n");

    // total number of devices (virtual/hardwired)
    int num_of_devices = Pm_CountDevices();
    if (num_of_devices == 0)
    {
        return 0;
    }

    // fprintf(stderr, "DEBUG: midi_initialize: %i midi devices found\n", num_of_devices);

    // adds PmDeviceInfo structs to the devices array, filtered by input devices.
    add_devices(num_of_devices);

    // init data
    conn_devices.count = input_device_count;
    conn_devices.devices = devices;

    // return all the available midi inputs
    return num_of_devices;
}

/* Terminates the previous instance of PortMidi, clears the data from connected devices, and then calls midi_initialize().
   Returns the number of devices found.*/
int midi_refresh(void)
{
    // terminates the previous instance of Pm_Initialize(), closes resources.
    PmError error = Pm_Terminate();
    if (error != pmNoError)
    {
        return error;
    }

    // clear data
    memset(&conn_devices, 0, sizeof(conn_devices));
    memset(devices, 0, sizeof(devices));
    input_device_count = 0;

    // start a new instance and returns the number of devices found.
    return midi_initialize();
}

// Opens a MIDI device for input. Returns pmNoError or a nonzero int (PmError) for a failed connection.
PmError midi_connect_device(int id)
{
    // Pm_OpenInput requires: PortMidiStream, PmDeviceId, bufferSize
    PmError error = Pm_OpenInput(&stream, id, NULL, MAX_BUFFERED_EVENTS, NULL, NULL);

    if (error != pmNoError)
    {
        // connection to midi device failed
        return error;
    };

    const PmDeviceInfo *selected_device = Pm_GetDeviceInfo(id);

    if (selected_device != NULL)
    {
        printf("midi_connect_device: %s connection opened to '%s'\n", selected_device->input ? "INPUT" : "OUTPUT", selected_device->name);
    }
    else
    {
        fprintf(stderr, "Pm_GetDeviceInfo is NULL: pointer for selected_device is out of range or was deleted\n");
    }
    return pmNoError;
}

PmError midi_read(void)
{
    PmEvent event_buffer[1] = {0};
    int events_per_read = 1;

    printf("midi_read: ready to read\n");

    // TODO - Find a way to gracefully recover
    while (1)
    {

        // returns the number of PmEvents read or a PmError
        PmError error = Pm_Read(stream, event_buffer, events_per_read);

        if (error < 0)
        {
            // PmError value will be returned
            return error;
        }
    }

    return pmNoError;
}

PmError midi_terminate(void)
{
    PmError error = Pm_Close(stream);

    if (error != pmNoError)
    {
        return error;
    };

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

// Adds PmDeviceInfo structs to devices[], filtered by input devices.
static void add_devices(int num_of_devices)
{
    input_device_count = 0;
    for (int device = 0; device < num_of_devices; device++)
    {
        // Pm_GetDeviceInfo - takes an id as a parameter and returns a pointer to a PmDeviceInfo struct
        const PmDeviceInfo *device_info = Pm_GetDeviceInfo(device);

        // if id is out of range or if the device designates a deleted virtual device, the function returns NULL.
        if (device_info == NULL)
        {
            continue;
        }

        if (device_info->input)
        {
            // add to MidiDevice array
            devices[input_device_count].id = device;
            devices[input_device_count].device_info = device_info;
            input_device_count++;
        }
    }
}

// ─────────────────────────────────────────────────────
// ACCESSORS
// ─────────────────────────────────────────────────────

ConnectedDevices *midi_get_connected_devices(void)
{
    return &conn_devices;
}

// ─────────────────────────────────────────────────────
// DEBUG PRINTING
// ─────────────────────────────────────────────────────

// Prints to the console a list of devices with their id, name, and type
static void print_devices(void)
{
    // print devices structs
    printf("Avilable Devices: \n");

    for (int i = 0; i < input_device_count; i++)
    {
        printf("Id: %d\n", devices[i].id);
        printf("Name: %s\n", devices[i].device_info->name);

        if (devices[i].device_info->input)
        {
            printf("Type: Input\n\n");
            continue;
        }

        printf("Type: Output\n\n");
        continue;
    };
}

static void print_devices_arr(const MidiDevice devices[])
{
    // print devices structs
    printf("Avilable Devices: \n");

    for (int i = 0; i < input_device_count; i++)
    {
        printf("Id: %d\n", devices[i].id);
        printf("Name: %s\n", devices[i].device_info->name);

        if (devices[i].device_info->input)
        {
            printf("Type: Input\n\n");
            continue;
        }

        printf("Type: Output\n\n");
        continue;
    };
}

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