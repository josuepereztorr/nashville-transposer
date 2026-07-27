#include "history.h"

// std lib

// vendor
#include "../vendor/nuklear.h"

// shared
#include "../theme.h"
#include "../../theory/theory.h"

// views
#include "layout.h"

void draw_history_container(struct nk_context *ctx)
{
    struct nk_rect margin_rec = {.x = MARGIN, .y = MARGIN, .w = MARGIN * 2.0f, .h = MARGIN * 2.0f};
    struct nk_rect relative_container_rect = draw_container(ctx, margin_rec);

    // devices - TODO: NEED A FUNCTION CALL TO THE CURRENT ACTIVE DEVICES
    NoteResult history[50] = {0};

    // item count
    int item_count = sizeof(history) / sizeof(history[0]);

    for (int i = 0; i < item_count; i++)
    {
        NoteResult result = {0};
        result.current_note = "A5";
        result.target_note = "D5";
        result.nashville_num = "5";
        history[i] = result;
    }

    nk_layout_space_begin(ctx, NK_STATIC, relative_container_rect.h, 2);

    // NOTE: nk_layout_space_push uses coordinates from the local group, not based on the current screen.
    // the x and y dimensions are relative to margin_rect. We can reuse the card container but we need to convert our coordinates.
    struct nk_rect absolute_rect = nk_layout_space_rect_to_local(ctx, relative_container_rect);

    // row ratios based on the card container's height
    float title_height = (absolute_rect.h / 2) * CARD_HEIGHT_RATIO_20;
    float item_height = absolute_rect.h * 0.10;

    // CARD TITLE
    // inner container with padding
    struct nk_rect title_pad_rect = {
        .x = absolute_rect.x + (MARGIN * 2.0f),
        .y = absolute_rect.y + MARGIN,
        .w = absolute_rect.w - (MARGIN * 4.0f),
        .h = title_height};

    nk_layout_space_push(ctx, title_pad_rect);
    if (nk_group_begin(ctx, "history_title", NK_WINDOW_NO_SCROLLBAR))
    {
        // title label
        draw_title_label(ctx, "HISTORY", title_height);
        nk_group_end(ctx);
    }

    // ITEM
    // inner container with padding
    struct nk_rect item_pad_rect = {
        .x = absolute_rect.x + (MARGIN * 2.0f),
        .y = title_pad_rect.y + title_pad_rect.h,
        .w = absolute_rect.w - (MARGIN * 4.0f),
        .h = absolute_rect.h - title_pad_rect.h - (MARGIN * 2.0f)};

    nk_layout_space_push(ctx, item_pad_rect);
    if (nk_group_begin(ctx, "history_list", 0))
    {
        // add space_begin to create my custom rect and add padding
        for (int i = 0; i < item_count; i++)
        {
            nk_layout_row_dynamic(ctx, item_height, 3);
            nk_label(ctx, history[i].current_note, NK_TEXT_LEFT);
            nk_label(ctx, history[i].target_note, NK_TEXT_LEFT);
            nk_label(ctx, history[i].nashville_num, NK_TEXT_LEFT);
        }

        nk_group_end(ctx);
    }
};