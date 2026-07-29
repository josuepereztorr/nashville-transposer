/*
 * ============================================================
 * File    : midi_device.c
 * Project : Nashville Transposer
 * ============================================================
 * Author   : Josue Perez Torres
 * Created  : 07-28-2026
 * Modified : 07-28-2026
 * Version  : 1.0.0
 * ============================================================
 * Description:
 *     Draws the MIDI device info card, showing the connected
 *     device's name, input/output type, and ID.
 * ============================================================
 * Dependencies:
 *     raylib-nuklear.h (vendor) - Nuklear + Raylib integration.
 * ============================================================
 */

// ------------------------------------------------------------
// INCLUDES
// ------------------------------------------------------------

// file header
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

// ------------------------------------------------------------
// PUBLIC FUNCTIONS
// ------------------------------------------------------------

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
        .y = title_pad_rect.y + title_pad_rect.h,
        .w = absolute_rect.w - w_padding,
        .h = absolute_rect.h};

    nk_layout_space_push(ui_ctx, info_pad_rect);

    if (nk_group_begin(ui_ctx, "device_info", NK_WINDOW_NO_SCROLLBAR))
    {
        // NOTE: have to account for null terminator
        nk_style_push_font(ui_ctx, app_get_title_font());

        // NOTE: library function used to write formatted text into a sized character buffer

        // NAME
        char name[50];
        snprintf(name, sizeof(name), "Name: %s", app_ctx->device.device_info->name);
        nk_layout_row_dynamic(ui_ctx, title_height, 1);
        nk_label_colored(ui_ctx, name, NK_TEXT_LEFT, NK_PRIMARY_TEXT_COLOR);

        // INPUT TYPE
        char type[20];
        snprintf(type, sizeof(type), "Type: %s", app_ctx->device.device_info->input ? "Input" : "Output");
        nk_layout_row_dynamic(ui_ctx, title_height, 1);
        nk_label_colored(ui_ctx, type, NK_TEXT_LEFT, NK_PRIMARY_TEXT_COLOR);

        // DEVICE ID
        char id[20];
        snprintf(id, sizeof(id), "ID: %d", app_ctx->device.id);
        nk_layout_row_dynamic(ui_ctx, title_height, 1);
        nk_label_colored(ui_ctx, id, NK_TEXT_LEFT, NK_PRIMARY_TEXT_COLOR);
        nk_style_pop_font(ui_ctx);

        nk_group_end(ui_ctx);
    }
}