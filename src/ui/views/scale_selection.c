#include "scale_selection.h"

// std lib

// vendor
#include "../vendor/raylib-nuklear.h"

// shared
#include "../theme.h"

// views
#include "layout.h"

void draw_scale_selection_container(struct nk_context *ctx)
{
    // draw card - x and y offsets are relative to the screen.
    struct nk_rect margin_rect = {.x = MARGIN, .y = 0, .w = MARGIN, .h = MARGIN};
    struct nk_rect relative_container_rect = draw_container(ctx, margin_rect, NK_FOREGROUND_COLOR, NK_BORDER_COLOR);

    // major scales
    const char *major_scales[] = {"C Major", "C# Major",
                                  "D Major", "D# Major",
                                  "E Major", "F Major",
                                  "F# Major", "G Major",
                                  "G# Major", "A Major",
                                  "A# Major", "B Major"};

    // item count
    int item_count = sizeof(major_scales) / sizeof(major_scales[0]);

    // need to use nk_layout_space to create a custom layout inside of my card component
    // no other nk_layout function allows for custom rect's
    nk_layout_space_begin(ctx, NK_STATIC, relative_container_rect.h, 3);

    // NOTE: nk_layout_space_push uses coordinates from the local group, not based on the current screen.
    // the x and y dimensions are relative to margin_rect. We can reuse the card container but we need to convert our coordinates.
    struct nk_rect absolute_rect = nk_layout_space_rect_to_local(ctx, relative_container_rect);

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
    nk_layout_space_push(ctx, title_pad_rect);
    if (nk_group_begin(ctx, "scale_selection_title", NK_WINDOW_NO_SCROLLBAR))
    {
        // title label
        draw_title_label(ctx, "SCALE SELECTION", title_height);
        nk_group_end(ctx);
    }

    // CURRENT KEY DROPBOX
    struct nk_rect current_key_pad_rect = {
        .x = absolute_rect.x + (MARGIN * 2.0f),
        .y = absolute_rect.y + title_pad_rect.h,
        .w = absolute_rect.w - (MARGIN * 4.0f),
        .h = dropdown_height};

    static int current_key_selected = 0;

    nk_layout_space_push(ctx, current_key_pad_rect);

    if (nk_group_begin(ctx, "current_key", NK_WINDOW_NO_SCROLLBAR))
    {
        draw_dropdown(ctx, absolute_rect, current_key_pad_rect.w, "Current Key", major_scales, item_count, &current_key_selected);
        nk_group_end(ctx);
    }

    // TARGET KEY DROPBOX
    struct nk_rect target_key_pad_rect = {
        .x = absolute_rect.x + (MARGIN * 2.0f),
        .y = absolute_rect.y + title_pad_rect.h + current_key_pad_rect.h,
        .w = absolute_rect.w - (MARGIN * 4.0f),
        .h = dropdown_height};

    nk_layout_space_push(ctx, target_key_pad_rect);

    static int target_key_selected = 0;

    if (nk_group_begin(ctx, "target_key", NK_WINDOW_NO_SCROLLBAR))
    {
        // creates a dropbox with title
        draw_dropdown(ctx, absolute_rect, target_key_pad_rect.w, "Target Key", major_scales, item_count, &target_key_selected);
        nk_group_end(ctx);
    }

    nk_layout_space_end(ctx);
};