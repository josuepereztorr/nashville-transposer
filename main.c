#include <stdio.h>
#include <portmidi.h>

int main() {
    /* PortMidi is designed to support multiple interfaces (such as  ALSA, CoreMIDI and WinMM). 
    It is possible to return pmNoError because there are no supported interfaces. In that case, 
    zero devices will be available.*/
    PmError err = Pm_Initialize();
    if (err != pmNoError) {
        printf("Failed to initialize PortMidi: %s/n", Pm_GetErrorText(err));
        Pm_Terminate();
        return -1;
    };
    printf("Initilization Complete\n");

    // See how many devices are connected. If id < 1, no devices found. 
    // int num_of_devices = Pm_CountDevices()-(Pm_CountDevices()-1);
    int num_of_devices = Pm_CountDevices();
    if (num_of_devices < 0) {
        printf("No MIDI devices found");
        Pm_Terminate();
        return -1;
    };
    printf("%d MIDI divces found\n", num_of_devices);

    /* pointer array, DO NOT STORE ACTUAL PmDeviceInfo STRUCTS! 
    let PortMidi handle this*/
    // TODO: add a const for MAX NUMBER OF DEVICES
    const PmDeviceInfo *devices[50] = {0};

    // Get the number of devices. By default, the computer has two, an input and an output.
    printf("Devices available are: \n");
    for (int i = 0; i < num_of_devices; i++)
    {
        // Pm_GetDeviceInfo - takes an id as a parameter and returns a pointer to a PmDeviceInfo struct
        const PmDeviceInfo *device = Pm_GetDeviceInfo(i);
        // if id is out of range or if the device designates a deleted virtual device, the function returns NULL.
        if (device == NULL) {
            printf("Device with an id of #%d is out of range or null\n", i);
            // skip the current iteration
            continue;
        }

        // add pointer to device array
        devices[i] = device;

        printf("%s ", device->name);
        if (device->input != 1) {
            printf("- OUTPUT\n");
        } else {
            printf("- INPUT\n");
        }
    };

    // print devices structs
    printf("Size of Devices Array:");
    const int size_of_device_array = sizeof(devices)/sizeof(devices[0]);
    printf("%d\n", size_of_device_array);
    printf("Pointers in Array:");
    int p_array_count = 0;
    for (int i = 0; i < size_of_device_array; i++)
    {
        if (devices[i] != NULL) {
            p_array_count++;
            printf("%s\n", devices[i]->name);
        };
        continue;
    };
    printf("%d\n", p_array_count);
    
    // call after using PortMidi
    err = Pm_Terminate();
    if (err != pmNoError) {
        printf("Failed to terminate PortMidi: %s/n", Pm_GetErrorText(err));
        return -1;
    };
    printf("Termination Complete\n");
    return 0;
};