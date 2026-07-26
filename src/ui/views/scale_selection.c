
#include "../vendor/nuklear.h"
#include "layout.h"
#include "../theme.h"

void draw_scale_selection_container(struct nk_context *ctx)
{
    struct nk_rect margin_rec = {.x = MARGIN, .y = 0, .w = MARGIN, .h = MARGIN};
    draw_container(ctx, margin_rec);
};