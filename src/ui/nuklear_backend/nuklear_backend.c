#include <stdio.h>
#include "raylib.h"

#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include "raylib-nuklear.h"

void nuklear_setup()
{
    printf("Nuklear is setup\n\n");
}

// clang -g src/main.c src/csv_reader/*.c src/theory/*.c src/utility/*.c src/midi/*.c src/ui/*.c src/ui/nuklear_backend/*.c -I/usr/local/include -L/usr/local/lib -lportmidi -lraylib -o build/nashville_transposer
