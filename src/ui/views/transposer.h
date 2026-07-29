/*
 * ============================================================
 * File    : transposer.h
 * Project : Nashville Transposer
 * ============================================================
 * Author   : Josue Perez Torres
 * Created  : 07-28-2026
 * Modified : 07-28-2026
 * Version  : 1.0.0
 * ============================================================
 * Description:
 *     Public interface for the transposer card view.
 * ============================================================
 * Dependencies:
 *     raylib-nuklear.h (vendor) - Nuklear + Raylib integration.
 * ============================================================
 */

#ifndef TRANSPOSER_H
#define TRANSPOSER_H

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

void draw_transposer_container(struct nk_context *ui_ctx, AppContext *app_ctx);

#endif