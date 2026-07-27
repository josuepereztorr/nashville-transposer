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
    struct nk_rect relative_container_rect = draw_container(ctx, margin_rec);

    // devices - TODO: NEED A FUNCTION CALL TO THE CURRENT ACTIVE DEVICES
    const char *devices[] = {"Device #1", "Device #2", "Device #3"};

    // item count
    int item_count = sizeof(devices) / sizeof(devices[0]);

    nk_layout_space_begin(ctx, NK_STATIC, relative_container_rect.h, 4);

    // NOTE: nk_layout_space_push uses coordinates from the local group, not based on the current screen.
    // the x and y dimensions are relative to margin_rect. We can reuse the card container but we need to convert our coordinates.
    struct nk_rect absolute_rect = nk_layout_space_rect_to_local(ctx, relative_container_rect);

    // row ratios based on the card container's height
    float title_height = absolute_rect.h * CARD_HEIGHT_RATIO_20;
    float dropdown_height = absolute_rect.h * CARD_HEIGHT_RATIO_30;

    // CARD TITLE
    // inner container with padding
    struct nk_rect title_pad_rect = {
        .x = absolute_rect.x + (MARGIN * 2.0f),
        .y = absolute_rect.y + MARGIN,
        .w = absolute_rect.w - (MARGIN * 4.0f),
        .h = title_height + MARGIN};

    nk_layout_space_push(ctx, title_pad_rect);
    if (nk_group_begin(ctx, "midi_device_title", NK_WINDOW_NO_SCROLLBAR))
    {
        // title label
        draw_title_label(ctx, "MIDI DEVICE", title_height);
        nk_group_end(ctx);
    }

    // DEVICE SELECTION DROPBOX
    struct nk_rect device_pad_rect = {
        .x = absolute_rect.x + (MARGIN * 2.0f),
        .y = absolute_rect.y + title_pad_rect.h,
        .w = absolute_rect.w - (MARGIN * 4.0f),
        .h = dropdown_height};

    static int device_selected = 0;

    nk_layout_space_push(ctx, device_pad_rect);

    if (nk_group_begin(ctx, "device", NK_WINDOW_NO_SCROLLBAR))
    {
        draw_dropdown(ctx, absolute_rect, device_pad_rect.w, "Device", devices, item_count, &device_selected);
        nk_group_end(ctx);
    }

    // IS CONNECTED LABEL
    struct nk_rect connected_pad_rect = {
        .x = absolute_rect.x + (MARGIN * 2.0f),
        .y = absolute_rect.y + title_pad_rect.h + device_pad_rect.h,
        .w = absolute_rect.w - (MARGIN * 4.0f),
        .h = absolute_rect.h * 0.15};

    const struct nk_color success_midi = nk_rgba(74, 222, 128, 255);
    const struct nk_color failure_midi = nk_rgba(232, 97, 93, 255);

    nk_layout_space_push(ctx, connected_pad_rect);

    if (nk_group_begin(ctx, "device", NK_WINDOW_NO_SCROLLBAR))
    {
        nk_layout_row_dynamic(ctx, connected_pad_rect.h, 1);
        nk_label_colored(ctx, "Connected", NK_TEXT_LEFT, success_midi);
        nk_group_end(ctx);
    }

    // SCAN DEVICES BUTTON
    struct nk_rect scan_devices_pad_rect = {
        .x = absolute_rect.x + (MARGIN * 2.0f),
        .y = absolute_rect.y + title_pad_rect.h + device_pad_rect.h + connected_pad_rect.h,
        .w = absolute_rect.w - (MARGIN * 4.0f),
        .h = absolute_rect.h * 0.15};

    nk_layout_space_push(ctx, scan_devices_pad_rect);

    if (nk_group_begin(ctx, "device", NK_WINDOW_NO_SCROLLBAR))
    {
        nk_layout_row_dynamic(ctx, scan_devices_pad_rect.h, 1);
        // button that calls the scan midid function
        if (nk_button_label(ctx, "SCAN FOR DEVICES"))
        {
            // function call
        }
        nk_group_end(ctx);
    }
};