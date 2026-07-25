#include <stdio.h>

#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include "ui/vendor/raylib-nuklear.h"
#include "nuklear_backend.h"

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

// Initialize the Nuklear context for use with Raylib. Loads the default font and sets up GL resources.
struct nk_context *nk_backend_init(int font_size)
{
    // struct nk_context *ctx = InitNuklear(font_size);
    // add themes via theme.c
    return InitNuklear(font_size);
}

// Update the Nuklear context for raylib's state. Forwards Raylib's state into Nuklear, resets per frame.
void nk_backend_update(struct nk_context *ctx)
{
    UpdateNuklear(ctx);
}

// Draw the given Nuklear context in raylib. Walks Nuklear's queue draw commands, issues real Raylib draw calls.
void nk_backend_draw_frame(struct nk_context *ctx)
{
    DrawNuklear(ctx);
}

// Unload the given Nuklear context, along with all internal raylib textures. Frees Nuklear's textures/font/context memory.
void nk_backend_unload(struct nk_context *ctx)
{
    UnloadNuklear(ctx);
}

// clang -g src/main.c src/csv_reader/*.c src/theory/*.c src/utility/*.c src/midi/*.c src/ui/*.c src/ui/nuklear_backend/*.c -I/usr/local/include -L/usr/local/lib -lportmidi -lraylib -o build/nashville_transposer
