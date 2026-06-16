#include <stdio.h>
#include <portmidi.h>

int main() {
    /* PortMidi is designed to support multiple interfaces (such as  ALSA, CoreMIDI and WinMM). 
    It is possible to return pmNoError because there are no supported interfaces. In that case, 
    zero devices will be available.*/
    PmError err = Pm_Initialize();
    if (err != pmNoError) {
        printf("Failed to initialize PortMidi: %s/n", Pm_GetErrorText(err));
    };
    printf("Initilization Complete\n");

    // See how many devices are connected. If id < 1, no devices found. 
    // int num_of_devices = Pm_CountDevices()-(Pm_CountDevices()-1);
    int num_of_devices = Pm_CountDevices();
    if (num_of_devices < 0) {
        printf("No MIDI devices found");
    };
    printf("%d MIDI divces found\n", num_of_devices);

    // Get the numebr of devices. By default, the computer has two. 
    printf("Devices available are: \n");
    for (int i = 0; i < num_of_devices; i++)
    {
        if (Pm_GetDeviceInfo(i) == NULL) {
            printf("Device id is out of range or null\n");
        }
        printf("%s ", Pm_GetDeviceInfo(i)->name);
        if (Pm_GetDeviceInfo(i)->input != 1) {
            printf("- OUTPUT\n");
        } else {
            printf("- INPUT\n");
        }
    };
    

    // call after using PortMidi
    err = Pm_Terminate();
    if (err != pmNoError) {
        printf("Failed to terminate PortMidi: %s/n", Pm_GetErrorText(err));
    };
    printf("Termination Complete\n");
    return 0;
};