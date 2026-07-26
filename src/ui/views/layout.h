#ifndef LAYOUT_H
#define LAYOUT_H

#include "../vendor/nuklear.h"

void draw_layout(struct nk_context *ctx);
void draw_container(struct nk_context *ctx, struct nk_rect rec);

#endif
