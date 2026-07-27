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
    // draw card - x and y offsets are relative to the screen.
    struct nk_rect margin_rect = {.x = MARGIN, .y = 0, .w = MARGIN, .h = MARGIN};
    struct nk_rect container_rect = draw_container(ctx, margin_rect);

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
    nk_layout_space_begin(ctx, NK_STATIC, container_rect.h, 3);

    // NOTE: nk_layout_space_push uses coordinates from the local group, not based on the current screen.
    // the x and y dimensions are relative to margin_rect. We can reuse the card container but we need to convert our coordinates.
    struct nk_rect local_container_rect = nk_layout_space_rect_to_local(ctx, container_rect);

    // row ratios based on the card container's height
    float title_card_ratio = local_container_rect.h * 0.20f;
    float combo_title_container_ratio = local_container_rect.h * 0.15f;
    float combo_container_ratio = local_container_rect.h * 0.15f;
    float drawbox_container_ratio = local_container_rect.h * 0.30f;

    // inner container with padding
    struct nk_rect title_rect = {
        .x = local_container_rect.x + (MARGIN * 2.0f),
        .y = local_container_rect.y + MARGIN,
        .w = local_container_rect.w - (MARGIN * 4.0f),
        .h = title_card_ratio + MARGIN};

    // CARD TITLE
    nk_layout_space_push(ctx, title_rect);

    // TITLE 1
    if (nk_group_begin(ctx, "scale_selection_title", NK_WINDOW_NO_SCROLLBAR))
    {
        // title label
        nk_layout_row_dynamic(ctx, title_card_ratio, 1);
        nk_label_colored(ctx, "SCALE SELECTION", NK_TEXT_LEFT, NK_PRIMARY_TEXT_COLOR);

        nk_group_end(ctx);
    }

    // CURRENT KEY DROPBOX
    struct nk_rect current_key_rect = {
        .x = local_container_rect.x + (MARGIN * 2.0f),
        .y = local_container_rect.y + title_rect.h,
        .w = local_container_rect.w - (MARGIN * 4.0f),
        .h = drawbox_container_ratio};

    static int current_key_selected = 0;

    nk_layout_space_push(ctx, current_key_rect);

    if (nk_group_begin(ctx, "current_key", NK_WINDOW_NO_SCROLLBAR))
    {
        draw_dropdown(ctx, local_container_rect, "Current Key", major_scales, item_count, &current_key_selected);
        nk_group_end(ctx);
    }

    // TARGET KEY DROPBOX
    struct nk_rect target_key_rect = {
        .x = local_container_rect.x + (MARGIN * 2.0f),
        .y = local_container_rect.y + title_rect.h + current_key_rect.h,
        .w = local_container_rect.w - (MARGIN * 4.0f),
        .h = drawbox_container_ratio};

    nk_layout_space_push(ctx, target_key_rect);

    static int target_key_selected = 0;

    if (nk_group_begin(ctx, "target_key", NK_WINDOW_NO_SCROLLBAR))
    {
        // creates a dropbox with title
        draw_dropdown(ctx, local_container_rect, "Target Key", major_scales, item_count, &target_key_selected);
        nk_group_end(ctx);
    }

    nk_layout_space_end(ctx);
};