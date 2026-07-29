#include "midi_device.h"

// std lib
#include <stdio.h>

// vendor
#include "../vendor/raylib-nuklear.h"

// shared
#include "../theme.h"
#include "../../app.h"
#include "../../midi/midi.h"

// views
#include "layout.h"

void draw_midi_device_container(struct nk_context *ui_ctx, AppContext *app_ctx)
{
    struct nk_rect margin_rec = {.x = MARGIN, .y = MARGIN, .w = MARGIN * 2.0f, .h = MARGIN * 2.0f};
    struct nk_rect relative_container_rect = draw_container(ui_ctx, margin_rec, NK_FOREGROUND_COLOR, NK_BORDER_COLOR);

    nk_layout_space_begin(ui_ctx, NK_STATIC, relative_container_rect.h, 2);

    // NOTE: nk_layout_space_push uses coordinates from the local group, not based on the current screen.
    // the x and y dimensions are relative to margin_rect. We can reuse the card container but we need to convert our coordinates.
    struct nk_rect absolute_rect = nk_layout_space_rect_to_local(ui_ctx, relative_container_rect);

    // row ratios based on the card container's height
    float title_height = absolute_rect.h * CARD_HEIGHT_RATIO_20;
    float x_padding = (MARGIN * 2.0f);
    float w_padding = (MARGIN * 6.0f);

    // CARD TITLE
    // inner container with padding
    struct nk_rect title_pad_rect = {
        .x = absolute_rect.x + x_padding,
        .y = absolute_rect.y + MARGIN,
        .w = absolute_rect.w - w_padding,
        .h = title_height};

    nk_layout_space_push(ui_ctx, title_pad_rect);
    if (nk_group_begin(ui_ctx, "midi_device_title", NK_WINDOW_NO_SCROLLBAR))
    {
        // title label
        draw_title_label(ui_ctx, "MIDI DEVICE", title_height);
        nk_group_end(ui_ctx);
    }

    // CONNECTED LABEL
    struct nk_rect info_pad_rect = {
        .x = absolute_rect.x + x_padding,
        .y = title_pad_rect.y + title_pad_rect.h + MARGIN,
        .w = absolute_rect.w - w_padding,
        .h = absolute_rect.h * 0.30f};

    const struct nk_color success_midi = nk_rgba(74, 222, 128, 255);
    const struct nk_color failure_midi = nk_rgba(232, 97, 93, 255);

    nk_layout_space_push(ui_ctx, info_pad_rect);

    if (nk_group_begin(ui_ctx, "device_info", NK_WINDOW_NO_SCROLLBAR))
    {
        nk_layout_row_dynamic(ui_ctx, 24, 1);

        if (app_ctx->device.device_info != NULL)
        {
            nk_label_colored(ui_ctx, app_ctx->device.device_info->name, NK_TEXT_LEFT, success_midi);
        }
        else
        {
            nk_label_colored(ui_ctx, "Not Connected", NK_TEXT_CENTERED, failure_midi);
        }

        nk_group_end(ui_ctx);
    }
};