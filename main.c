#include <stdio.h>
#include "midi.c"
#include "theory.c"

int main()
{
    // midi_start();
    read_cvs();
    return 0;
};

// clang main.c -I/usr/local/include -L/usr/local/lib -lportmidi -o nashville_transposer
// ./nashville_transposer