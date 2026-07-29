/*
 * ============================================================
 * File    : app.h
 * Project : Nashville Transposer
 * ============================================================
 * Author   : Josue Perez Torres
 * Created  : 07-28-2026
 * Modified : 07-28-2026
 * Version  : 1.0.0
 * ============================================================
 * Description:
 *     Public interface for app initialization, teardown, and
 *     access to shared app/UI state.
 * ============================================================
 * Dependencies:
 *     raylib.h (vendor) - windowing/rendering.
 *     raylib-nuklear.h (vendor) - Nuklear + Raylib integration.
 * ============================================================
 */

#ifndef APP_H
#define APP_H

// ------------------------------------------------------------
// INCLUDES
// ------------------------------------------------------------

// vendor
#include "raylib.h"
#include "ui/vendor/raylib-nuklear.h"

// shared
#include "midi/midi.h"

// ------------------------------------------------------------
// TYPE DEFINITIONS
// ------------------------------------------------------------

typedef struct
{
    MidiDevice device;
    PmEvent event;
    int current_key_selected;
    int target_key_selected;
} AppContext;

// ------------------------------------------------------------
// PUBLIC FUNCTION PROTOTYPES
// ------------------------------------------------------------

int app_init(void);
void app_terminate(void);
struct nk_vec2 get_monitor_dimensions(void);
AppContext *app_get_context(void);
struct nk_context *app_get_ui_context(void);
struct nk_user_font *app_get_title_font(void);
struct nk_user_font *app_get_display_font(void);

#endif