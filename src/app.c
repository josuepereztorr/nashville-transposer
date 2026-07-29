// std
#include <stdio.h>

// vendor
#include "raylib.h"
#include "ui/vendor/raylib-nuklear.h"

// shared
#include "app.h"
#include "ui/theme.h"
#include "midi/midi.h"
#include "csv_reader/csv_reader.h"
#include "theory/theory.h"

// views

#define CSV_DATA_PATH "./data/midi_notes.csv"
#define UI_NAME "Nashville Transposer"

static AppContext app_ctx = {0};
static struct nk_context *nk_ctx = NULL;

// Initializes a window based on the monitor dimensions and initializes a Nuklear context.
int app_init(void)
{
    // SETUP DATA LAYER
    // get data from csv
    char rows[CSV_MAX_ROWS][CSV_MAX_BUFFER_SIZE] = {0};
    int rows_read = csv_read(CSV_DATA_PATH, rows);

    if (rows_read < 0)
    {
        fprintf(stderr, "csv_read: failed to load data from '%s' or there was an error during reading\n", CSV_DATA_PATH);
        return -1;
    }

    // parse and load data into memory
    for (int row = 0; row < rows_read; row++)
    {
        int error = theory_row_parser(rows[row]);

        if (error < 0)
        {
            fprintf(stderr, "theory_row_parser: failed to parse the string\n");
            return -1;
        }
    }

    // SETUP UI CONTEXT

    // initializes a window and OpenGL context. Set's up a temporary 1x1 window.
    InitWindow(1, 1, UI_NAME);
    struct nk_vec2 monitor_dimensions = get_monitor_dimensions();

    // resizes the current window to the monitor dimensions and toggles fullscreen mode.
    SetWindowSize(monitor_dimensions.x, monitor_dimensions.y);
    // ToggleFullscreen();

    // *filename is relative to the project root directory
    Font font = LoadFontEx("assets/fonts/inter/Inter_18pt-Regular.ttf", 18.0f, NULL, 0);

    // initializes the Nuklear context for use with Raylib. Loads the default font and sets up GL resources.
    nk_ctx = InitNuklearEx(font, 18.0f);

    if (nk_ctx == NULL)
    {
        fprintf(stderr, "Failed to initialize the UI context.\n");
        return -1;
    }

    // global parameters
    nk_ctx->style.window.fixed_background = nk_style_item_color(NK_TRANSPARENT);
    nk_ctx->style.window.spacing = nk_vec2(0, 0);
    nk_ctx->style.window.padding = nk_vec2(0, 0);
    nk_ctx->style.window.group_padding = nk_vec2(0, 0);

    // SETUP MIDI
    int error = midi_initialize(&app_ctx.device);

    if (error == -1)
    {
        fprintf(stderr, "ERROR: failed to initialize midi - midi_initialize()\n");
        return -1;
    }

    return 0;
}

void app_terminate()
{
    midi_terminate();
    UnloadNuklear(nk_ctx);
    CloseWindow();
}

// returns the current monitor's dimensions
struct nk_vec2 get_monitor_dimensions(void)
{
    // returns the index of the current monitor where the window is placed and gets the current monitor dimensions.
    int monitor = GetCurrentMonitor();
    return (struct nk_vec2){
        .x = (float)GetMonitorWidth(monitor),
        .y = (float)GetMonitorHeight(monitor)};
}

AppContext *app_get_context(void)
{
    return &app_ctx;
}

struct nk_context *app_get_ui_context(void)
{
    return nk_ctx;
}