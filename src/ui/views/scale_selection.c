#include "scale_selection.h"

// std lib

// vendor
#include "../vendor/raylib-nuklear.h"

// shared
#include "../theme.h"
#include "../../theory/scales.h"

// views
#include "layout.h"

void draw_scale_selection_container(struct nk_context *ui_ctx, AppContext *app_ctx)
{
    // draw card - x and y offsets are relative to the screen.
    struct nk_rect margin_rect = {.x = MARGIN, .y = 0, .w = MARGIN, .h = MARGIN};
    struct nk_rect relative_container_rect = draw_container(ui_ctx, margin_rect, NK_FOREGROUND_COLOR, NK_BORDER_COLOR);

    // should reflect all 12 major keys
    int chromatic_scale = 12;

    // need to use nk_layout_space to create a custom layout inside of my card component
    // no other nk_layout function allows for custom rect's
    nk_layout_space_begin(ui_ctx, NK_STATIC, relative_container_rect.h, 3);

    // NOTE: nk_layout_space_push uses coordinates from the local group, not based on the current screen.
    // the x and y dimensions are relative to margin_rect. We can reuse the card container but we need to convert our coordinates.
    struct nk_rect absolute_rect = nk_layout_space_rect_to_local(ui_ctx, relative_container_rect);

    // row ratios based on the card container's height
    float title_height = absolute_rect.h * CARD_HEIGHT_RATIO_20;
    float dropdown_height = absolute_rect.h * CARD_HEIGHT_RATIO_30;

    // inner container with padding
    struct nk_rect title_pad_rect = {
        .x = absolute_rect.x + (MARGIN * 2.0f),
        .y = absolute_rect.y + MARGIN,
        .w = absolute_rect.w - (MARGIN * 4.0f),
        .h = title_height + MARGIN};

    // CARD TITLE
    nk_layout_space_push(ui_ctx, title_pad_rect);
    if (nk_group_begin(ui_ctx, "scale_selection_title", NK_WINDOW_NO_SCROLLBAR))
    {
        // title label
        draw_title_label(ui_ctx, "SCALE SELECTION", title_height);
        nk_group_end(ui_ctx);
    }

    // CURRENT KEY DROPBOX
    struct nk_rect current_key_pad_rect = {
        .x = absolute_rect.x + (MARGIN * 2.0f),
        .y = absolute_rect.y + title_pad_rect.h,
        .w = absolute_rect.w - (MARGIN * 4.0f),
        .h = dropdown_height};

    nk_layout_space_push(ui_ctx, current_key_pad_rect);

    if (nk_group_begin(ui_ctx, "current_key", NK_WINDOW_NO_SCROLLBAR))
    {
        draw_dropdown(ui_ctx, absolute_rect, current_key_pad_rect.w, "Current Key", major_scales, chromatic_scale, &app_ctx->current_key_selected);
        nk_group_end(ui_ctx);
    }

    // TARGET KEY DROPBOX
    struct nk_rect target_key_pad_rect = {
        .x = absolute_rect.x + (MARGIN * 2.0f),
        .y = absolute_rect.y + title_pad_rect.h + current_key_pad_rect.h,
        .w = absolute_rect.w - (MARGIN * 4.0f),
        .h = dropdown_height};

    nk_layout_space_push(ui_ctx, target_key_pad_rect);

    if (nk_group_begin(ui_ctx, "target_key", NK_WINDOW_NO_SCROLLBAR))
    {
        // creates a dropbox with title
        draw_dropdown(ui_ctx, absolute_rect, target_key_pad_rect.w, "Target Key", major_scales, chromatic_scale, &app_ctx->target_key_selected);
        nk_group_end(ui_ctx);
    }

    nk_layout_space_end(ui_ctx);
};