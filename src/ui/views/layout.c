/*
 * ============================================================
 * File    : layout.c
 * Project : Nashville Transposer
 * ============================================================
 * Author   : Josue Perez Torres
 * Created  : 07-28-2026
 * Modified : 07-28-2026
 * Version  : 1.0.0
 * ============================================================
 * Description:
 *     Builds the main app layout (upper card row + keyboard row)
 *     and provides shared UI drawing helpers used across views.
 * ============================================================
 * Dependencies:
 *     raylib.h (vendor) - windowing/rendering.
 *     raylib-nuklear.h (vendor) - Nuklear + Raylib integration.
 * ============================================================
 */

// ------------------------------------------------------------
// INCLUDES
// ------------------------------------------------------------

// file header
#include "layout.h"

// std lib
#include <stdio.h>

// vendor
#include "../vendor/raylib-nuklear.h"
#include "raylib.h"

// shared
#include "../../app.h"
#include "../theme.h"
#include "../../midi/midi.h"

// views
#include "midi_device.h"
#include "scale_selection.h"
#include "transposer.h"
#include "keyboard.h"

// ------------------------------------------------------------
// CONSTANT & MACROS
// ------------------------------------------------------------

#define UPPER_HEIGHT_RATIO 0.6f
#define LOWER_HEIGHT_RATIO 0.4f
#define QUARTER_WIDTH_RATIO 0.25f
#define HALF_WIDTH_RATIO 0.5f

// ------------------------------------------------------------
// PUBLIC FUNCTIONS
// ------------------------------------------------------------

// draws the main app containers based on Nuklear's row/column layout.
void draw_layout(struct nk_context *ui_ctx, AppContext *app_ctx)
{
    // get the screen size and split it up into a ratio of 60/40
    struct nk_vec2 monitor_size = get_monitor_dimensions();
    float upper_height = monitor_size.y * UPPER_HEIGHT_RATIO;
    float lower_height = monitor_size.y * LOWER_HEIGHT_RATIO;

    // UPPER ROW BEGIN - 3 CARDS
    // 25/50/25 ratios which are allowed by the NK_DYNAMIC flag
    nk_layout_row_begin(ui_ctx, NK_DYNAMIC, upper_height, 3);

    // COLUMN #1 - Left Column
    // creates a column specified by the given ratio + customizes with the provided flags
    nk_layout_row_push(ui_ctx, QUARTER_WIDTH_RATIO);

    // all Nuklear widgets are enclosed in nk_group_begin() and nk_group_end() function calls.
    if (nk_group_begin(ui_ctx, "left_column", NK_WINDOW_NO_SCROLLBAR))
    {
        // get the dimensions of the "left_column" container
        struct nk_rect left_column_rect = nk_window_get_content_region(ui_ctx);
        float half_height = left_column_rect.h * 0.5f;

        // LEFT ROW #1 - PLACEHOLDER
        nk_layout_row_dynamic(ui_ctx, half_height, 1);
        if (nk_group_begin(ui_ctx, "left_placeholder", NK_WINDOW_NO_SCROLLBAR))
        {
            struct nk_rect margin_rec = {.x = MARGIN, .y = MARGIN, .w = MARGIN, .h = MARGIN * 2.0f};
            draw_container(ui_ctx, margin_rec, NK_TRANSPARENT, NK_TRANSPARENT);
            nk_group_end(ui_ctx);
        }

        // LEFT ROW #2 - SCALE SELECTION
        nk_layout_row_dynamic(ui_ctx, half_height, 1);
        if (nk_group_begin(ui_ctx, "scale_selection", NK_WINDOW_NO_SCROLLBAR))
        {
            draw_scale_selection_container(ui_ctx, app_ctx);
            nk_group_end(ui_ctx);
        }
        nk_group_end(ui_ctx);
    }

    // COLUMN #2 - TRANSPOSE CONTAINER
    nk_layout_row_push(ui_ctx, HALF_WIDTH_RATIO);
    if (nk_group_begin(ui_ctx, "transposer", NK_WINDOW_NO_SCROLLBAR))
    {
        draw_transposer_container(ui_ctx, app_ctx);
        nk_group_end(ui_ctx);
    }

    // COLUMN #3 - RIGHT COLUMN
    nk_layout_row_push(ui_ctx, QUARTER_WIDTH_RATIO);
    if (nk_group_begin(ui_ctx, "right_column", NK_WINDOW_NO_SCROLLBAR))
    {
        // get the dimensions of the "right_column" container
        struct nk_rect right_column_rect = nk_window_get_content_region(ui_ctx);
        float half_height = right_column_rect.h * 0.5f;

        // RIGHT ROW #1 - PLACEHOLDER
        nk_layout_row_dynamic(ui_ctx, half_height, 1);
        if (nk_group_begin(ui_ctx, "right_placeholder", NK_WINDOW_NO_SCROLLBAR))
        {
            struct nk_rect margin_rec = {.x = MARGIN, .y = MARGIN, .w = MARGIN * 2.0f, .h = MARGIN * 2.0f};
            draw_container(ui_ctx, margin_rec, NK_TRANSPARENT, NK_TRANSPARENT);
            nk_group_end(ui_ctx);
        }

        // RIGHT ROW #2 - MIDI Device Info
        nk_layout_row_dynamic(ui_ctx, half_height, 1);
        if (nk_group_begin(ui_ctx, "midi_device", NK_WINDOW_NO_SCROLLBAR))
        {
            draw_midi_device_container(ui_ctx, app_ctx);
            nk_group_end(ui_ctx);
        }

        nk_group_end(ui_ctx);
    }

    // UPPER ROW END
    nk_layout_row_end(ui_ctx);

    // OUTER ROW #2 - KEYBOARD CONTAINER
    // creates a row with equal (fixed) width columns (only 1 column), no need for start/end
    nk_layout_row_dynamic(ui_ctx, lower_height, 1);
    if (nk_group_begin(ui_ctx, "keyboard", NK_WINDOW_NO_SCROLLBAR))
    {
        draw_keyboard_container(ui_ctx, app_ctx);
        nk_group_end(ui_ctx);
    }
}

/* draws a container based on the provided margin values. offset_margin adds the specified margin values
   to the x and y offset. size_margin subtracts the specified margin values from the width and height values. */
struct nk_rect draw_container(struct nk_context *ui_ctx, struct nk_rect rect, struct nk_color rect_color, struct nk_color border_color)
{
    // gets the rectangle dimensions of the parent group
    struct nk_rect group_rect = nk_window_get_content_region(ui_ctx);

    // adds the function's caller margin
    struct nk_rect rect_add_margin = nk_rect(group_rect.x + rect.x,
                                             group_rect.y + rect.y,
                                             group_rect.w - rect.w,
                                             group_rect.h - rect.h);

    // get the draw buffer
    struct nk_command_buffer *canvas = nk_window_get_canvas(ui_ctx);

    // draw the rectangle and border
    nk_fill_rect(canvas, rect_add_margin, ROUNDNESS, rect_color);
    nk_stroke_rect(canvas, rect_add_margin, ROUNDNESS, LINE_THICK, border_color);

    return rect_add_margin;
}

// creates a dropdown box (nk_combo) with a title (nk_label_colored). padding_container is used to calculate the height based on the usable area.
void draw_dropdown(struct nk_context *ui_ctx, struct nk_rect padding_container, float row_width, const char *title, const char **dropdown_items, int item_count, int *selected)
{
    // height calculations
    float title_height = padding_container.h * CARD_HEIGHT_RATIO_15;
    float row_height = padding_container.h * CARD_HEIGHT_RATIO_15;

    // creates a label
    draw_title_label(ui_ctx, title, title_height);

    // the size of each row when the dropbox is expanded
    struct nk_vec2 expanded_row_size = {
        .x = row_width, // this value is based on the dropdown box's padding containers
        .y = row_height * item_count};

    // creates a dropdown box
    nk_layout_row_dynamic(ui_ctx, row_height, 1);
    *selected = nk_combo(ui_ctx, dropdown_items, item_count, *selected, (int)row_height, expanded_row_size);
}

void draw_title_label(struct nk_context *ui_ctx, const char *title, float row_height)
{
    nk_style_push_font(ui_ctx, app_get_title_font());
    nk_layout_row_dynamic(ui_ctx, row_height, 1);
    nk_label_colored(ui_ctx, title, NK_TEXT_LEFT, NK_PRIMARY_TEXT_COLOR);
    nk_style_pop_font(ui_ctx);
}