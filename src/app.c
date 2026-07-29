/*
 * ============================================================
 * File    : app.c
 * Project : Nashville Transposer
 * ============================================================
 * Author   : Josue Perez Torres
 * Created  : 07-28-2026
 * Modified : 07-28-2026
 * Version  : 1.0.0
 * ============================================================
 * Description:
 *     Initializes the application window, Nuklear UI context,
 *     fonts, and MIDI connection at startup. Provides accessors
 *     for shared app state and UI context.
 * ============================================================
 * Dependencies:
 *     raylib.h (vendor) - windowing/rendering.
 *     raylib-nuklear.h (vendor) - Nuklear + Raylib integration.
 * ============================================================
 */

// ------------------------------------------------------------
// INCLUDES
// ------------------------------------------------------------

// std
#include <stdio.h>

// vendor
#include "raylib.h"
#include "ui/vendor/raylib-nuklear.h"

// shared
#include "app.h"
#include "ui/theme.h"
#include "midi/midi.h"

// ------------------------------------------------------------
// CONSTANT & MACROS
// ------------------------------------------------------------

#define UI_NAME "Nashville Transposer"
#define FONT_PATH "assets/fonts/inter/Inter_18pt-Regular.ttf"

// ------------------------------------------------------------
// PRIVATE VARIABLES
// ------------------------------------------------------------

static AppContext app_ctx = {0};
static struct nk_context *nk_ctx = NULL;

static Font font_title = {0};
static struct nk_user_font nk_font_title = {0};

static Font font_display = {0};
static struct nk_user_font nk_font_display = {0};

// ------------------------------------------------------------
// PUBLIC FUNCTIONS
// ------------------------------------------------------------

// Initializes a window based on the monitor dimensions and initializes a Nuklear context.
int app_init(void)
{
    // SETUP UI CONTEXT

    // initializes a window and OpenGL context. Set's up a temporary 1x1 window.
    InitWindow(1, 1, UI_NAME);
    struct nk_vec2 monitor_dimensions = get_monitor_dimensions();

    // resizes the current window to the monitor dimensions and toggles fullscreen mode.
    SetWindowSize(monitor_dimensions.x, monitor_dimensions.y);
    ToggleFullscreen();

    // *filename is relative to the project root directory
    Font font = LoadFontEx(FONT_PATH, 18.0f, NULL, 0);

    // initializes the Nuklear context for use with Raylib. Loads the default font and sets up GL resources.
    nk_ctx = InitNuklearEx(font, 18.0f);

    if (nk_ctx == NULL)
    {
        fprintf(stderr, "Failed to initialize the UI context.\n");
        return -1;
    }

    // add additional font sizes
    font_title = LoadFontEx(FONT_PATH, 24.0f, NULL, 0);
    nk_font_title.userdata = nk_handle_ptr(&font_title);
    nk_font_title.height = 24.0f;
    nk_font_title.width = nk_raylib_font_get_text_width_user_font;

    font_display = LoadFontEx(FONT_PATH, 150.0f, NULL, 0);
    nk_font_display.userdata = nk_handle_ptr(&font_display);
    nk_font_display.height = 150.0f;
    nk_font_display.width = nk_raylib_font_get_text_width_user_font;

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

void app_terminate(void)
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

struct nk_user_font *app_get_title_font(void)
{
    return &nk_font_title;
}

struct nk_user_font *app_get_display_font(void)
{
    return &nk_font_display;
}