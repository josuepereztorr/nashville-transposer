/*
 * ============================================================
 * File    : main.c
 * Project : Nashville Transposer
 * ============================================================
 * Author   : Josue Perez Torres
 * Created  : 07-28-2026
 * Modified : 07-28-2026
 * Version  : 1.0.0
 * ============================================================
 * Description:
 *     Application entry point. Initializes the app and MIDI
 *     connection, runs the main render/update loop, and handles
 *     shutdown.
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
#include "midi/midi.h"
#include "ui/theme.h"

// views
#include "ui/views/layout.h"

// ------------------------------------------------------------
// PRIVATE VARIABLES
// ------------------------------------------------------------

static AppContext *app_ctx = NULL;
static struct nk_context *ui_ctx = NULL;

// ------------------------------------------------------------
// PUBLIC FUNCTIONS
// ------------------------------------------------------------

int main(void)
{
    // buffering set to unbuffered
    setbuf(stdout, NULL);

    // init app
    int error = app_init();

    if (error != 0)
    {
        // failure
        return 1;
    }

    // get contexts
    app_ctx = app_get_context();
    ui_ctx = app_get_ui_context();

    SetTargetFPS(60);

    // returns the current monitor's dimensions
    struct nk_vec2 monitor_size = get_monitor_dimensions();

    // checks for ESC or window closed.
    while (!WindowShouldClose())
    {
        // actively checks (polls) raylib's live state and forwards it to Nuklear (ui library)
        UpdateNuklear(ui_ctx);

        app_ctx->event = midi_read();

        // window size
        struct nk_rect window_size = nk_rect(0, 0, monitor_size.x, monitor_size.y);

        // describes the ui
        if (nk_begin(ui_ctx, "main", window_size, NK_WINDOW_NO_SCROLLBAR))
        {
            // app layout
            draw_layout(ui_ctx, app_ctx);
        }
        nk_end(ui_ctx);

        BeginDrawing();
        ClearBackground(RL_FILL_COLOR); // note: this is just a fallback color. the background color is set in app_init().
        DrawNuklear(ui_ctx);
        EndDrawing();
    }

    // release resources
    app_terminate();

    return 0;
}