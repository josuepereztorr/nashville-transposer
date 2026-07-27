#ifndef LAYOUT_H
#define LAYOUT_H

// vendor
#include "../vendor/nuklear.h"

void draw_layout(struct nk_context *ctx);
struct nk_rect draw_container(struct nk_context *ctx, struct nk_rect rec);
void draw_dropdown(struct nk_context *ctx, struct nk_rect container, const char *title_str, const char **dropdown_items, int item_count, int *selected);

#endif
