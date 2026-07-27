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
    struct nk_rect container_rect = draw_container(ctx, margin_rec);

    // devices
    char *devices[] = {"Device #1, Device #2, Device #3"};

    // item count
    int item_count = sizeof(devices) / sizeof(devices[0]);

    nk_layout_space_begin(ctx, NK_STATIC, container_rect.h, 3);

    struct nk_rect local_container_rect = nk_layout_space_rect_to_local(ctx, container_rect);

    // struct nk_rect title_rect =
    // {

    // }
};