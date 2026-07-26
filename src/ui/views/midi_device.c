
#include "../vendor/nuklear.h"
#include "layout.h"
#include "../theme.h"

void draw_midi_device_container(struct nk_context *ctx)
{
    struct nk_rect margin_rec = {.x = MARGIN, .y = MARGIN, .w = MARGIN, .h = MARGIN * 2.0f};
    draw_container(ctx, margin_rec);
};