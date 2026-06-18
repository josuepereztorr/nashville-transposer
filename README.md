# nashville-transposer

Application that reads a note input from a connected MIDI keyboard. The user selects the current and target musical key, plays a note, and the program displays the note's Nashville Number System (NNS) equivalent.

## MIDI Protocol

MIDI stands for Musical Instrument Digitial Interface (MIDI). It is a communication protocol used to interface musical devices together.

### MIDI Message Structure

A MIDI messsage (24 bits) contains one Status byte and two Data bytes.

#### Status Byte

A Status byte (8-bits) is always the first byte in a MIDI message. The message contains the type of message and on which channel it's sending the data on. The first bit is always a 1, then it has 3 bits to indicate the type of MIDI message, ex. "X001XXXX". Finally, the last 4 are reserved for the channel ex. "XXXX1111".

"1XXXXXXX" - The first bit is always a 1.
"X001XXXX" - Bits 3-4 indicate the type of MIDI messsage, which equate to 8 different kinds.
"XXXX1111" - The last four bits indicate the channel number, which equate to 16 different channels.

#### Data Bytes

The Data byte (1 byte) carries the content of the status message. Each data byte starts with a zero, leaving 7 bits for the data, ex. "0XXXXXXX". In decimal, that is a range of 0-127.

#### Type of Messages

Groupings of MIDI data by numerical designation.
"1000XXXX" - Note off (Channel Specific)
"1001XXXX" - Note on (Channel Specific)
"1010XXXX" - Polyphonic Aftertouch (Channel Specific)
"1011XXXX" - Control Change (Channel Specific)
"1100XXXX" - Program Change (Channel Specific)
"1101XXXX" - Channel Aftertouch (Channel Specific)
"1110XXXX" - Pitch Bend Change (Channel Specific)
"1111XXXX" - System Messages (Global)

#### Note On

Note On messsages send information about which key is pressed, at what velocity, and on which channel.

#### Note Off

Note Off messsages send information about which key is released, at what velocity, and on which channel.

## PortMidi - Library

### Lifecycle

1. Pm_Initialize() - Start PortMidi
2. Pm_CountDevices() - How many devices are connected?
3. Pm_GetDeviceInfo() - Find keyboard by name
4. Pm_OpenInput() - Open a connection to it
5. Pm_Read() - Wait for and read incoming notes
6. Pm_Close() - Close connection
7. Pm_Terminate() - End PortMidi

### Functions

## Resources

MIDI 1.0 Detailed Specification
https://drive.google.com/file/d/1ewRrvMEFRPlKon6nfSCxqnTMEu70sz0c/view

The MIDI Protocol: MIDI Messages | Simon Hutchinson
https://www.youtube.com/watch?v=2BccxWkUgaU

PortMidi Documentation - Cross-Platform MIDI IO
https://portmidi.github.io/portmidi_docs/
