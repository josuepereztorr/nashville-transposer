// std
#include <stdio.h>

// vendor
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "raylib.h"
#include "ui/vendor/nuklear.h"
#include "ui/vendor/raylib-nuklear.h"

// shared
#include "app_init.h"
#include "ui/theme.h"

// views

#define UI_NAME "Nashville Transposer"

// Initializes a window based on the monitor dimensions and initializes a Nuklear context.
struct nk_context *app_init(int font_size)
{
    // initializes a window and OpenGL context. Set's up a temporary 1x1 window.
    InitWindow(1, 1, UI_NAME);
    struct nk_vec2 monitor_dimensions = get_monitor_dimensions();

    // resizes the current window to the monitor dimensions and toggles fullscreen mode.
    SetWindowSize(monitor_dimensions.x, monitor_dimensions.y);
    ToggleFullscreen();

    // *filename is relative to the project root directory
    Font font = LoadFontEx("assets/fonts/inter/Inter_18pt-Regular.ttf", 18.0f, NULL, 0);

    // initializes the Nuklear context for use with Raylib. Loads the default font and sets up GL resources.
    struct nk_context *ctx = InitNuklearEx(font, 18.0f);

    if (ctx == NULL)
    {
        return NULL;
    }

    // global parameters
    ctx->style.window.fixed_background = nk_style_item_color(NK_TRANSPARENT);
    ctx->style.window.spacing = nk_vec2(0, 0);
    ctx->style.window.padding = nk_vec2(0, 0);
    ctx->style.window.group_padding = nk_vec2(0, 0);

    return ctx;
}

// returns the current monitor's dimensions
struct nk_vec2 get_monitor_dimensions()
{
    // returns the index of the current monitor where the window is placed and gets the current monitor dimensions.
    int monitor = GetCurrentMonitor();
    return (struct nk_vec2){
        .x = (float)GetMonitorWidth(monitor),
        .y = (float)GetMonitorHeight(monitor)};
}