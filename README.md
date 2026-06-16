# nashville-transposer

Application that reads a note input from a connected MIDI keyboard. The user selects the current and target musical key, plays a note, and the program displays the note's NNS (Nashville Number System) equivalent.

## PortMidi Lifecycle

1. Pm_Initialize() - Start PortMidi
2. Pm_CountDevices() - How many devices are connected?
3. Pm_GetDeviceInfo() - Find keyboard by name
4. Pm_OpenInput() - Open a connection to it
5. Pm_Poll() + Pm_Read() - Wait for and read incoming notes
6. Pm_Close() - Close connection
7. Pm_Terminate() - End PortMidi
