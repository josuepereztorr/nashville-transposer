/*
 * ============================================================
 * File    : midi_device.h
 * Project : Nashville Transposer
 * ============================================================
 * Author   : Josue Perez Torres
 * Created  : 07-28-2026
 * Modified : 07-28-2026
 * Version  : 1.0.0
 * ============================================================
 * Description:
 *     Public interface for the MIDI device info card view.
 * ============================================================
 * Dependencies:
 *     raylib-nuklear.h (vendor) - Nuklear + Raylib integration.
 * ============================================================
 */

#ifndef MIDI_DEVICE_H
#define MIDI_DEVICE_H

// ------------------------------------------------------------
// INCLUDES
// ------------------------------------------------------------

// vendor
#include "../vendor/raylib-nuklear.h"

// shared
#include "../../app.h"

// ------------------------------------------------------------
// PUBLIC FUNCTION PROTOTYPES
// ------------------------------------------------------------

void draw_midi_device_container(struct nk_context *ui_ctx, AppContext *app_ctx);

#endif