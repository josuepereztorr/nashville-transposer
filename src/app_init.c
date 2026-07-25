#include <stdio.h>

#include "app_init.h"
#include "ui/vendor/raylib-nuklear.h"
#include "ui/theme.h"

#define UI_NAME "Nashville Transposer"

// Initialize the Nuklear context for use with Raylib. Loads the default font and sets up GL resources.
struct nk_context *app_init(int font_size)
{
    // initializes a window and OpenGL context. Set's up a temporary 1x1 window.
    InitWindow(1, 1, UI_NAME);

    // returns the index of the current monitor where the window is placed and gets the current monitor dimensions.
    int monitor = GetCurrentMonitor();
    int screen_width = GetMonitorWidth(monitor);
    int screen_height = GetMonitorHeight(monitor);

    // resizes the current window to the monitor dimensions and toggles fullscreen mode.
    SetWindowSize(screen_width, screen_height);
    ToggleFullscreen();

    // initializes the Nuklear context for use with Raylib. Loads the default font and sets up GL resources.
    struct nk_context *ctx = InitNuklear(font_size);
    // add themes via theme.c

    return ctx;
}

// clang -g src/*.c src/csv_reader/*.c src/theory/*.c src/utility/*.c src/midi/*.c src/ui/*.c -I/usr/local/include -L/usr/local/lib -lportmidi -lraylib -o build/nashville_transposer
