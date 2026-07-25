#include <stdio.h>

#include "app_init.h"
#include "ui/vendor/raylib-nuklear.h"

#define UI_NAME "Nashville Transposer"

// Initializes a window based on the monitor dimensions and initializes a Nuklear context.
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

    if (ctx == NULL)
    {
        return NULL;
    }

    // add themes via theme.c

    return ctx;
}