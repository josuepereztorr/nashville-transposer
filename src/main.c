#include <stdio.h>
#include "csv_reader/csv_reader.h"
#include "theory/theory.h"
#include "midi/midi.h"
#include "ui/ui.h"
#include "ui/nuklear_backend/nuklear_backend.h"

// CSV
#define CSV_DATA_PATH "./data/midi_notes.csv"

void external();

int main()
{
    // buffering set to unbuffered
    setbuf(stdout, NULL);

    // get data from csv
    char rows[CSV_MAX_ROWS][CSV_MAX_BUFFER_SIZE] = {};
    int rows_read = csv_read(CSV_DATA_PATH, rows);

    if (rows_read < 0)
    {
        fprintf(stderr, "csv_read: failed to load data from '%s' or there was an error during reading\n", CSV_DATA_PATH);
        return 1;
    }

    // parse and load data into memory
    for (int row = 0; row < rows_read; row++)
    {
        int error = theory_row_parser(rows[row]);

        if (error < 0)
        {
            fprintf(stderr, "theory_row_parser: failed to parse the string\n");
            return 1;
        }
    }

    // start portMidi and search for devices.
    int num_of_devices = midi_initialize();

    // do i really want to end my program? loop?
    // if (num_of_devices == 0)
    // {
    //     printf("main: no devices found\n");
    //     return 1;
    // }

    // // Connect to a MIDI device
    // PmError error = midi_connect_device();
    // if (error != pmNoError)
    // {
    //     fprintf(stderr, "Pm_OpenInput failed: %d\n ", error);
    // }

    // Read from MIDI Device
    // error = midi_read(external);

    // if (error != pmNoError)
    // {
    //     fprintf(stderr, "midi_read failed: %d\n ", error);
    // }

    // error = midi_terminate();

    // if (error != pmNoError)
    // {
    //     fprintf(stderr, "midi_terminate failed: %d\n ", error);
    // }

    // RAYLIB

    // 1. Anything that should exist only once for the lifetime of the program, doesn't change frame by frame.
    // ex. InitWindow, any LoadX() call, GuiSetStyle()/font - themes, Persistent state variables such as dropdown_open, active_index, appLayout.
    ui_setup();
    nuklear_setup();

    // 2. Loop Condition - checks for ESC or window closed.
    while (!WindowShouldClose())
    {
        // 3. Update/Logic - this is where you read input and update state, don't draw anything.
        // ex. midi events, any logic that changes, update dropdown values

        BeginDrawing();
        // 4. Draw - everything that gets drawn after update logic is computed.
        // ex. dropdown goes last.

        ClearBackground(FILL_COLOR);

        ui_create_containers();

        EndDrawing();
    }

    // 4. Teardown - close everything that was setup.
    // ex. every Loadx() needs a matching UnloadX() function. CloseWindow() goes last.
    CloseWindow();
    return 0;
};

// temp callback function
void external()
{
    // printf("inside of the external function\n");
}

//  Terminal Build Commands
//    clang -g src/main.c src/csv_reader/*.c src/theory/*.c src/utility/*.c src/midi/*.c src/ui/*.c -I/usr/local/include -L/usr/local/lib -lportmidi -lraylib -o build/nashville_transposer
//    ./build/nashville_transposer
/*
    Notes:
    - what happens if the midi device is disconnected while it's reading?
    - would my program freeze? what are the different states of my program?
    - disable or gray out the keboard UI, device information etc if no midi is connected.

    - I would like the start function to handle
        1. Pm_Initialize() - Start PortMidi
        2. Pm_CountDevices() - How many devices are connected?

    TODO
    - Terminal color change

*/