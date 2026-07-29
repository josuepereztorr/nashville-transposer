#include "transposer.h"

// std lib

// vendor
#include "../vendor/raylib-nuklear.h"

// shared
#include "../theme.h"
#include "../../theory/theory.h"

// views
#include "layout.h"

void draw_transposer_container(struct nk_context *ctx)
{
    struct nk_rect margin_rec = {.x = MARGIN, .y = MARGIN, .w = MARGIN, .h = MARGIN * 2.0f};
    struct nk_rect relative_container_rect = draw_container(ctx, margin_rec, NK_FOREGROUND_COLOR, NK_BORDER_COLOR);

    nk_layout_space_begin(ctx, NK_STATIC, relative_container_rect.h, 2);

    // NOTE: nk_layout_space_push uses coordinates from the local group, not based on the current screen.
    // the x and y dimensions are relative to margin_rect. We can reuse the card container but we need to convert our coordinates.
    struct nk_rect absolute_rect = nk_layout_space_rect_to_local(ctx, relative_container_rect);

    // row ratios based on the card container's height
    float title_height = (absolute_rect.h / 2) * CARD_HEIGHT_RATIO_20;
    float item_height = absolute_rect.h * 0.10;

    // CARD TITLE
    // inner container with padding
    struct nk_rect nashville_num_pad_rect = {
        .x = absolute_rect.x + (MARGIN * 2.0f),
        .y = absolute_rect.y + (MARGIN * 5.0f),
        .w = absolute_rect.w - (MARGIN * 4.0f),
        .h = title_height};

    NoteResult result = {0};
    result.current_note = "A5";
    result.target_note = "D5";
    result.nashville_num = "5";

    nk_layout_space_push(ctx, nashville_num_pad_rect);
    if (nk_group_begin(ctx, "nashville_number", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_BORDER))
    {
        // title label
        nk_layout_row_dynamic(ctx, item_height, 1);
        nk_label(ctx, result.nashville_num, NK_TEXT_CENTERED);
        nk_group_end(ctx);
    }

    struct nk_rect key_pad_rect =
        {
            .x = absolute_rect.x + (MARGIN * 2.0f),
            .y = nashville_num_pad_rect.y + nashville_num_pad_rect.h + MARGIN,
            .w = absolute_rect.w - (MARGIN * 4.0f),
            .h = nashville_num_pad_rect.y + nashville_num_pad_rect.h};

    nk_layout_space_push(ctx, key_pad_rect);
    if (nk_group_begin(ctx, "key_pad", NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_BORDER))
    {
        // title label
        nk_layout_row_dynamic(ctx, item_height, 2);
        nk_label(ctx, result.current_note, NK_TEXT_CENTERED);
        nk_label(ctx, result.target_note, NK_TEXT_CENTERED);
        nk_group_end(ctx);
    }
};