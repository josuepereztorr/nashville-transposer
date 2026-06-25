#include "midi.c"

int main()
{
    midi_start();
    return 0;
};

// clang main.c -I/usr/local/include -L/usr/local/lib -lportmidi -o nashville_transposer
// ./nashville_transposer