#include <stdio.h>
#include <string.h>
#include <portmidi.h>

#define MAX_DEVICES 50

int main()
{
    /* PortMidi is designed to support multiple interfaces (such as  ALSA, CoreMIDI and WinMM).
    It is possible to return pmNoError because there are no supported interfaces. In that case,
    zero devices will be available.*/
    PmError err = Pm_Initialize();
    if (err != pmNoError)
    {
        printf("Failed to initialize PortMidi: %s\n", Pm_GetErrorText(err));
        Pm_Terminate();
        return -1;
    };
    printf("Initilization Complete\n");

    // See how many devices are connected. If id < 1, no devices found.
    int num_of_devices = Pm_CountDevices();
    if (num_of_devices < 0)
    {
        printf("No MIDI devices found\n");
        Pm_Terminate();
        return -1;
    };
    // printf("%d MIDI divces found\n", num_of_devices);

    /* pointer array, DO NOT STORE ACTUAL PmDeviceInfo STRUCTS!
    let PortMidi handle this*/
    // TODO: add a const for MAX NUMBER OF DEVICES
    typedef struct
    {
        int id;
        const PmDeviceInfo *device;
    } MidiDevice;
    // const PmDeviceInfo *devices[50] = {0};
    MidiDevice devices[MAX_DEVICES] = {0};

    // Get the number of devices. By default, the computer has two, an input and an output.
    printf("Available devices: \n");
    for (int i = 0; i < num_of_devices; i++)
    {
        // Pm_GetDeviceInfo - takes an id as a parameter and returns a pointer to a PmDeviceInfo struct
        const PmDeviceInfo *device = Pm_GetDeviceInfo(i);
        // if id is out of range or if the device designates a deleted virtual device, the function returns NULL.
        if (device == NULL)
        {
            printf("Device with an id of #%d is out of range or null\n", i);
            // skip the current iteration
            continue;
        }

        // add pointer to device array
        devices[i].id = i;
        devices[i].device = device;
    };

    // print devices structs
    const int size_of_device_array = sizeof(devices) / sizeof(devices[0]);
    printf("Size of array: %d\n", size_of_device_array);
    int p_array_count = 0;
    for (int i = 0; i < size_of_device_array; i++)
    {
        if ((devices[i].device != NULL) && devices[i].device->input)
        {
            // filter out macOS midi device
            int name = strcmp(devices[i].device->name, "Network Josue's Macbook Session");
            if (name == 0)
            {
                continue;
            }

            p_array_count++;
            printf("Id: %d\n", devices[i].id);
            printf("Name: %s\n", devices[i].device->name);
            if (devices[i].device->input != 1)
            {
                printf("Type: Output\n\n");
            }
            else
            {
                printf("Type: Input\n\n");
            }
        };
        continue;
    };
    printf("Pointers (non-null) in Array: %d\n", p_array_count);

    if (p_array_count > 0)
    {
        // select a midi connection
        printf("Select a midi device: ");

        int selected_id = -1;
        int is_valid = 0;
        while (!is_valid)
        {
            // ger user input
            scanf("%d", &selected_id);

            // iterate through the pointer array
            for (int i = 0; i < size_of_device_array; i++)
            {
                // check if id is within bounds
                if (selected_id < 0 || selected_id > size_of_device_array)
                {
                    printf("id is out of range\n");
                    break;
                }

                // check if the id provides a valid device.
                // check if the device is an input
                if ((devices[i].device != NULL) && devices[i].device->input)
                {
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
        }

        // open a connection to the selected midi device
        // Pm_OpenInput requires: PortMidiStream, PmDeviceId, bufferSize
        PortMidiStream *stream = NULL;
        err = Pm_OpenInput(&stream, selected_id, NULL, 512, NULL, NULL);
        if (err != pmNoError)
        {
            printf("Failed to initialize PortMidi: %s\n", Pm_GetErrorText(err));
            Pm_Terminate();
            return -1;
        };

        // PmEvent
        PmEvent buffer[1];
        int result;

        // loop while waiting for data
        // TODO - ADD ERROR HANDLING
        while (1)
        {
            result = Pm_Read(stream, buffer, 1);

            // if no midi messages are detected loop again
            if (result == 0)
            {
                continue;
            }

            if (result < 0)
            {
                printf("Failed to read data: %s\n", Pm_GetErrorText(result));
                err = Pm_Close(stream);
                if (err != pmNoError)
                {
                    printf("Failed to close input: %s\n", Pm_GetErrorText(err));
                    return -1;
                };
                Pm_Terminate();
                return -1;
            }

            // raw bytes come back across multiple events
            // printf("%d", result);
            printf("32-Bit Message: %x\n", buffer[0].message);

            printf("Buffer Message: %d\n", buffer[0].message);
            printf("Status: %d  Note: %d  Velocity: %d\n\n",
                   // unpacks the status out of the 32-bit integer (4 bytes)
                   Pm_MessageStatus(buffer[0].message),
                   // unpacks data 1 out of the 32-bit integer (4 bytes)
                   Pm_MessageData1(buffer[0].message),
                   // unpacks data 1 out of the 32-bit integer (4 bytes)
                   Pm_MessageData2(buffer[0].message));
        }

        err = Pm_Close(stream);
        if (err != pmNoError)
        {
            printf("Failed to close input: %s\n", Pm_GetErrorText(err));
            return -1;
        };
    }
    else
    {
        printf("NO CONNECTED DEVICES\n");
    }

    // call after using PortMidi
    err = Pm_Terminate();
    if (err != pmNoError)
    {
        printf("Failed to terminate PortMidi: %s\n", Pm_GetErrorText(err));
        return -1;
    };
    printf("Termination Complete\n");
    return 0;
};

// clang main.c -I/usr/local/include -L/usr/local/lib -lportmidi -o nashville_transposer
// ./nashville_transposer