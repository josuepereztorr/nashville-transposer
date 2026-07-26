#include "scale_selection.h"

// std lib

// vendor
#include "../vendor/nuklear.h"

// shared
#include "../theme.h"

// views
#include "layout.h"

void draw_scale_selection_container(struct nk_context *ctx)
{
    struct nk_rect margin_rec = {.x = MARGIN, .y = 0, .w = MARGIN, .h = MARGIN};
    draw_container(ctx, margin_rec);
};