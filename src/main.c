#include <stdio.h>
#include "csv_reader/csv_reader.h"
#include "theory/theory.h"
#include "midi/midi.h"
#include "ui/ui.h"
#include "ui/raygui.h"

// CSV
#define CSV_DATA_PATH "./data/midi_notes.csv"

// UI
#define UI_NAME "Nashville Transposer"

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

    // Start the UI
    InitWindow((GetScreenWidth()), (GetScreenHeight()), UI_NAME);
    // ToggleFullscreen();

    // const char *text = "; Digital Input; Digital Output; Midi Keyboard";
    // int is_active = 0;
    // int is_editable = 0;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Clears the frame
        ClearBackground(background);

        // other logic
        ui_create_keyboard();
        // ui_create_drowndown();

        // Rectangle rec = {0};
        // rec.height = 200;
        // rec.width = 400;
        // rec.x = 20;
        // rec.y = 20;

        // if (GuiDropdownBox(rec, text, &is_active, is_editable))
        // {
        //     is_editable = !is_editable;
        // }

        // DrawText(TextFormat("Selected index: %i", is_active), 400, 400, 20, WHITE);
        EndDrawing();
    }

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