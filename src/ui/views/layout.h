#ifndef LAYOUT_H
#define LAYOUT_H

// vendor
#include "../vendor/raylib-nuklear.h"

// shared
#include "../../app.h"
#include "../../midi/midi.h"

#define CARD_HEIGHT_RATIO_15 0.15f
#define CARD_HEIGHT_RATIO_20 0.20f
#define CARD_HEIGHT_RATIO_30 0.30f

void draw_layout(struct nk_context *ctx, AppContext *app_ctx);
struct nk_rect draw_container(struct nk_context *ui_ctx, struct nk_rect rect, struct nk_color rect_color, struct nk_color border_color);
void draw_dropdown(struct nk_context *ctx, struct nk_rect container, float row_width, const char *title_str, const char **dropdown_items, int item_count, int *selected);
void draw_title_label(struct nk_context *ctx, const char *title, float row_height);

#endif
