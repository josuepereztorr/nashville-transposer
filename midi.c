#include <stdio.h>
#include <portmidi.h>

#define MAX_DEVICES 10

typedef struct
{
    int id;
    const PmDeviceInfo *device_info;
} MidiDevice;

// stores all devies (inputs/outputs)
MidiDevice devices[MAX_DEVICES] = {0};
int device_count = 0;

// Represents an open midi connection to the selected midi device
PortMidiStream *stream = NULL;

PmError midi_start();
PmError read_events();
int select_device();
void add_devices(int tolal_num_of_devices);
void print_buffer(PmEvent buffer[]);
void print_devices();

// Adds PmDeviceInfo structs to devices[], filtered by input devices.
void add_devices(int tolal_num_of_devices)
{
    for (int i = 0; i < tolal_num_of_devices; i++)
    {
        // Pm_GetDeviceInfo - takes an id as a parameter and returns a pointer to a PmDeviceInfo struct
        const PmDeviceInfo *device_info = Pm_GetDeviceInfo(i);

        // if id is out of range or if the device designates a deleted virtual device, the function returns NULL.
        // only store midi inputs
        if (device_info == NULL)
        {
            continue;
        }

        if (device_info->output != 1)
        {
            // add to MidiDevice array
            devices[i].id = i;
            devices[i].device_info = device_info;
            device_count++;
        }
    }
}

// Prints to the console and asks the user for an id. Returns an id.
int select_device()
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
            // TODO - find better fultering method
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
    printf("You have selected %d\n\n", selected_id);
    return selected_id;
}

// Reads a continuous input of PmEvents.
PmError read_events()
{

    // PmEvent
    PmEvent buffer[1];

    // loop while waiting for data
    // TODO - find a way to end this loop
    while (1)
    {
        // returns the number of PmEvents read
        int num_of_events = Pm_Read(stream, buffer, 1);

        if (num_of_events < 0)
        {
            // PmError value will be returned
            return num_of_events;
        }

        if (num_of_events > 0)
        {
            print_buffer(buffer);
        }
    }
}

PmError midi_start()
{
    /* PortMidi is designed to support multiple interfaces (such as  ALSA, CoreMIDI and WinMM).
    It is possible to return pmNoError because there are no supported interfaces. In that case,
    zero devices will be available.*/
    PmError error = Pm_Initialize();

    if (error != pmNoError)
    {
        return error;
    };

    // total number of devices (virtual/hardwired)
    int tolal_num_of_devices = Pm_CountDevices();

    if (tolal_num_of_devices < 0)
    {
        return pmNoDevice;
    };

    add_devices(tolal_num_of_devices);

    print_devices();

    int selected_id = select_device();

    // Pm_OpenInput requires: PortMidiStream, PmDeviceId, bufferSize
    error = Pm_OpenInput(&stream, selected_id, NULL, 512, NULL, NULL);

    if (error != pmNoError)
    {
        return error;
    };

    read_events();

    error = Pm_Close(stream);

    if (error != pmNoError)
    {
        return error;
    };

    error = Pm_Terminate();

    // If Pm_Terminate fails, the program will just end
    if (error != pmNoError)
    {
        return error;
    }

    return pmNoError;
}

// Prints to the console a list of devices with their id, name, and type
void print_devices()
{
    // print devices structs
    printf("Avilable Devices: \n");

    for (int i = 0; i < device_count; i++)
    {
        printf("Id: %d\n", devices[i].id);
        printf("Name: %s\n", devices[i].device_info->name);

        if (devices[i].device_info->input != 1)
        {
            printf("Type: Output\n\n");
            continue;
        }

        printf("Type: Input\n\n");
        continue;
    };
}

void print_buffer(PmEvent buffer[])
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