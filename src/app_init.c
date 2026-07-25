#include <stdio.h>

#include "app_init.h"
#include "ui/vendor/raylib-nuklear.h"
#include "ui/theme.h"
#include "raylib.h"

#define UI_NAME "Nashville Transposer"

// Initializes a window based on the monitor dimensions and initializes a Nuklear context.
struct nk_context *app_init(int font_size)
{
    // initializes a window and OpenGL context. Set's up a temporary 1x1 window.
    InitWindow(1, 1, UI_NAME);

    Vector2 monitor_dimensions = get_monitor_dimensions();

    // resizes the current window to the monitor dimensions and toggles fullscreen mode.
    SetWindowSize(monitor_dimensions.x, monitor_dimensions.y);
    ToggleFullscreen();

    // initializes the Nuklear context for use with Raylib. Loads the default font and sets up GL resources.
    struct nk_context *ctx = InitNuklear(font_size);

    if (ctx == NULL)
    {
        return NULL;
    }

    // add transperent window since the window color is
    // ctx->style.window.fixed_background = nk_style_item_color(NK_FILL_COLOR);
    ctx->style.window.fixed_background = nk_style_item_color(NK_TRANSPARENT);

    return ctx;
}

// returns the current monitor's dimensions
Vector2 get_monitor_dimensions()
{
    // returns the index of the current monitor where the window is placed and gets the current monitor dimensions.
    int monitor = GetCurrentMonitor();
    return (Vector2){
        .x = GetMonitorWidth(monitor),
        .y = GetMonitorHeight(monitor)};
}