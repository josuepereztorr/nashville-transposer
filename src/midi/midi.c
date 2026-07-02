#include <stdio.h>
#include "../midi/midi.h"

#define MAX_DEVICES 10
#define MAX_BUFFERED_EVENTS 512

typedef struct
{
    int id;
    const PmDeviceInfo *device_info;
} MidiDevice;

// stores all devices (inputs and outputs)
MidiDevice devices[MAX_DEVICES] = {0};
// Represents an open midi connection to the selected midi device
PortMidiStream *stream = NULL;
int device_count = 0;

static void add_devices(int num_of_devices);
static int select_device();
static void print_buffer(PmEvent buffer[]);
static void print_devices();

int midi_initialize()
{
    /* PortMidi is designed to support multiple interfaces (such as  ALSA, CoreMIDI and WinMM).
    It is possible to return pmNoError because there are no supported interfaces. In that case,
    zero devices will be available.*/
    PmError error = Pm_Initialize();

    printf("midi_initialize: init successful\n");

    // total number of devices (virtual/hardwired)
    int num_of_devices = Pm_CountDevices();

    if (num_of_devices == 0)
    {
        return 0;
    }

    printf("midi_initialize: %i midi devices found\n", num_of_devices);

    add_devices(num_of_devices);

    return num_of_devices;
}

PmError midi_terminate()
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

PmError midi_connect_device()
{
    // only valid for terminal application
    int selected_id = select_device();

    // Pm_OpenInput requires: PortMidiStream, PmDeviceId, bufferSize
    PmError error = Pm_OpenInput(&stream, selected_id, NULL, MAX_BUFFERED_EVENTS, NULL, NULL);

    if (error != pmNoError)
    {
        // connection to midi device failed
        return error;
    };

    const PmDeviceInfo *selected_device = Pm_GetDeviceInfo(selected_id);

    if (selected_device != NULL)
    {
        printf("midi_connect_device: %s connection opened to '%s'\n", selected_device->input ? "INPUT" : "OUTPUT", selected_device->name);
    }
    else
    {
        fprintf(stderr, "Pm_GetDeviceInfo is NULL: pointer for selected_device is out of range or was deleted");
    }

    return pmNoError;
}

PmError midi_read(void (*external_function)())
{
    PmEvent event_buffer[1] = {};
    int events_per_read = 1;

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

        // UI, or other program logic
        // update UI to show key pressed
        // do logic to compare midi key

        if (external_function != NULL)
        {
            external_function();
        }
    }

    return pmNoError;
}

// Adds PmDeviceInfo structs to devices[], filtered by input devices.
static void add_devices(int num_of_devices)
{
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
            devices[device].id = device;
            devices[device].device_info = device_info;
            device_count++;
        }
    }
}

// Prints to the console and asks the user for an id. Returns an id.
static int select_device()
{
    // select a midi connection
    printf("Select a midi device: ");

    int selected_id = -1;
    int is_valid = 0;

    while (!is_valid)
    {
        // ger user input
        scanf("%d", &selected_id);

        for (int i = 0; i < device_count; i++)
        {
            // check if id is within bounds
            // TODO - find better filtering method
            if (selected_id < 0 || selected_id > device_count)
            {
                printf("id is out of range\n");
                break;
            }

            // check if selected_id matches device id
            if (devices[i].id == selected_id)
            {
                is_valid = 1;
                break;
            }
            continue;
        }
    }
    // printf("You have selected %d\n", selected_id);
    return selected_id;
}

// Prints to the console a list of devices with their id, name, and type
static void print_devices()
{
    // print devices structs
    printf("Avilable Devices: \n");

    for (int i = 0; i < device_count; i++)
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