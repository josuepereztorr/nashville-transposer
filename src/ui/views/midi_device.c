#include "midi_device.h"

// std lib

// vendor
#include "../vendor/nuklear.h"

// shared
#include "../theme.h"

// views
#include "layout.h"

void draw_midi_device_container(struct nk_context *ctx)
{
    struct nk_rect margin_rec = {.x = MARGIN, .y = MARGIN, .w = MARGIN, .h = MARGIN * 2.0f};
    draw_container(ctx, margin_rec);
};