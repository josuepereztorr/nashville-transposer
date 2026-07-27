#ifndef LAYOUT_H
#define LAYOUT_H

// vendor
#include "../vendor/nuklear.h"

#define CARD_HEIGHT_RATIO_15 0.15f
#define CARD_HEIGHT_RATIO_20 0.20f
#define CARD_HEIGHT_RATIO_30 0.30f

void draw_layout(struct nk_context *ctx);
struct nk_rect draw_container(struct nk_context *ctx, struct nk_rect rec);
void draw_dropdown(struct nk_context *ctx, struct nk_rect container, float row_width, const char *title_str, const char **dropdown_items, int item_count, int *selected);
void draw_title_label(struct nk_context *ctx, const char *title, float row_height);

#endif
