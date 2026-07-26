#include <stdio.h>
#include "csv_reader/csv_reader.h"
#include "theory/theory.h"
#include "midi/midi.h"
#include "ui/ui.h"
#include "ui/theme.h"

#include "app_init.h"
#include "raylib.h"
#include "ui/vendor/raylib-nuklear.h"

#include "ui/views/history_container.h"
#include "ui/views/layout.h"

// CSV
#define CSV_DATA_PATH "./data/midi_notes.csv"

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

    /* ----------------------------------------------------------------------------------------------------------*/
    // RAYLIB
    struct nk_context *ctx = app_init(0);
    Vector2 monitor_size = get_monitor_dimensions();

    if (ctx == NULL)
    {
        fprintf(stderr, "Failed to initialize the UI context.");
        CloseWindow();
        return 1;
    }

    // checks for ESC or window closed.
    while (!WindowShouldClose())
    {
        // check for state change
        UpdateNuklear(ctx);

        // need to refactor into Nuklear views
        ui_create_containers();

        // describes the ui
        if (nk_begin(ctx, "main", nk_rect(0, 0, monitor_size.x, monitor_size.y), NK_WINDOW_NO_SCROLLBAR))
        {
            // app layout
            draw_layout(ctx);
        }
        nk_end(ctx);

        BeginDrawing();
        ClearBackground(BLACK); // note: this is just a fallback color. the background color is set in app_init().
        DrawNuklear(ctx);
        EndDrawing();
    }

    // release resources
    UnloadNuklear(ctx);
    CloseWindow();

    /* ----------------------------------------------------------------------------------------------------------*/

    return 0;
};