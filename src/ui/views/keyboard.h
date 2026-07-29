/*
 * ============================================================
 * File    : keyboard.h
 * Project : Nashville Transposer
 * ============================================================
 * Author   : Josue Perez Torres
 * Created  : 07-28-2026
 * Modified : 07-28-2026
 * Version  : 1.0.0
 * ============================================================
 * Description:
 *     Public interface for drawing the on-screen piano keyboard.
 * ============================================================
 * Dependencies:
 *     raylib-nuklear.h (vendor) - Nuklear + Raylib integration.
 * ============================================================
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

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

void draw_keyboard_container(struct nk_context *ui_ctx, AppContext *app_ctx);

#endif