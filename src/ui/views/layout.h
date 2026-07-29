/*
 * ============================================================
 * File    : layout.h
 * Project : Nashville Transposer
 * ============================================================
 * Author   : Josue Perez Torres
 * Created  : 07-28-2026
 * Modified : 07-28-2026
 * Version  : 1.0.0
 * ============================================================
 * Description:
 *     Public interface for the main app layout and shared UI
 *     drawing helpers (containers, dropdowns, title labels).
 * ============================================================
 * Dependencies:
 *     raylib-nuklear.h (vendor) - Nuklear + Raylib integration.
 * ============================================================
 */

#ifndef LAYOUT_H
#define LAYOUT_H

// ------------------------------------------------------------
// INCLUDES
// ------------------------------------------------------------

// vendor
#include "../vendor/raylib-nuklear.h"

// shared
#include "../../app.h"
#include "../../midi/midi.h"

// ------------------------------------------------------------
// CONSTANT & MACROS
// ------------------------------------------------------------

#define CARD_HEIGHT_RATIO_15 0.15f
#define CARD_HEIGHT_RATIO_20 0.20f
#define CARD_HEIGHT_RATIO_30 0.30f

// ------------------------------------------------------------
// PUBLIC FUNCTION PROTOTYPES
// ------------------------------------------------------------

void draw_layout(struct nk_context *ui_ctx, AppContext *app_ctx);
struct nk_rect draw_container(struct nk_context *ui_ctx, struct nk_rect rect, struct nk_color rect_color, struct nk_color border_color);
void draw_dropdown(struct nk_context *ui_ctx, struct nk_rect padding_container, float row_width, const char *title, const char **dropdown_items, int item_count, int *selected);
void draw_title_label(struct nk_context *ui_ctx, const char *title, float row_height);

#endif