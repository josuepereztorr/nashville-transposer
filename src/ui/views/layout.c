#include "layout.h"

// std lib

// vendor
#include "../vendor/nuklear.h"
#include "raylib.h"

// shared
#include "../../app_init.h"
#include "../theme.h"

// views
#include "midi_device.h"
#include "scale_selection.h"
#include "transposer.h"
#include "history.h"
#include "keyboard.h"

#define UPPER_HEIGHT_RATIO 0.6f
#define LOWER_HEIGHT_RATIO 0.4f
#define QUARTER_WIDTH_RATIO 0.25f
#define HALF_WIDTH_RATIO 0.5f
#define DROPDOWN_ROW_TITLE_HEIGHT_RATIO 0.15f
#define DROPDOWN_ROW_HEIGHT_RATIO 0.15f

// draws the main app containers based on a Nuklear's row/column layout.
void draw_layout(struct nk_context *ctx)
{
    // get the screen size and spit it up into ratio of 60/40
    struct nk_vec2 monitor_size = get_monitor_dimensions();
    float upper_height = monitor_size.y * UPPER_HEIGHT_RATIO;
    float lower_height = monitor_size.y * LOWER_HEIGHT_RATIO;

    // OUTER ROW #1 - START
    // has columns with arbitrary width spaced out in 25/50/25 ratios, allowed by the NK_DYNAMIC flag
    nk_layout_row_begin(ctx, NK_DYNAMIC, upper_height, 3);

    // COLUMN #1 - SETTINGS CONTAINER
    // creates a column specifed by the given ratio + customizes with the provided flags
    nk_layout_row_push(ctx, QUARTER_WIDTH_RATIO);

    // all Nuklear widgets are enclosed in nk_group_begin() and nk_group_end() function calls.
    if (nk_group_begin(ctx, "settings", NK_WINDOW_NO_SCROLLBAR))
    {
        // get the height of the "settings" group an cut it in half
        struct nk_rect settings_rect = nk_window_get_content_region(ctx);
        float half_height = settings_rect.h * 0.5f;

        // INNER ROW #1 - MIDI DEVICE
        nk_layout_row_dynamic(ctx, half_height, 1);
        if (nk_group_begin(ctx, "midi_device", NK_WINDOW_NO_SCROLLBAR))
        {
            draw_midi_device_container(ctx);
            nk_group_end(ctx);
        }

        // INNER ROW #2 - SCALE SELECTION
        nk_layout_row_dynamic(ctx, half_height, 1);
        if (nk_group_begin(ctx, "scale_selection", NK_WINDOW_NO_SCROLLBAR))
        {
            draw_scale_selection_container(ctx);
            nk_group_end(ctx);
        }
        nk_group_end(ctx);
    }

    // COLUMN #2 - TRANSPOSE CONTAINER
    nk_layout_row_push(ctx, HALF_WIDTH_RATIO);
    if (nk_group_begin(ctx, "transposer", NK_WINDOW_NO_SCROLLBAR))
    {
        draw_transposer_container(ctx);
        nk_group_end(ctx);
    }

    // COLUMN #3 - HISTORY CONTAINER
    nk_layout_row_push(ctx, QUARTER_WIDTH_RATIO);
    if (nk_group_begin(ctx, "history", NK_WINDOW_NO_SCROLLBAR))
    {
        draw_history_container(ctx);
        nk_group_end(ctx);
    }

    // ROW #1 - END
    nk_layout_row_end(ctx);

    // OUTER ROW #2 - KEYBOARD CONTAINER
    // creates a row with equal (fixed) width columns (only 1 column), no need for start/end
    nk_layout_row_dynamic(ctx, lower_height, 1);
    if (nk_group_begin(ctx, "keyboard", NK_WINDOW_NO_SCROLLBAR))
    {
        draw_keyboard_container(ctx);
        nk_group_end(ctx);
    }
}

/* draws a container based on the provided margin values. offset_margin adds the specified margin values
   to the x and y offset. size_margin subtracts the specified margin values from the width and height values. */
struct nk_rect draw_container(struct nk_context *ctx, struct nk_rect rect)
{
    // gets the rectangle dimensions of the parent group
    struct nk_rect group_rect = nk_window_get_content_region(ctx);

    // adds the function's caller margin
    struct nk_rect rect_add_margin = nk_rect(group_rect.x + rect.x,
                                             group_rect.y + rect.y,
                                             group_rect.w - rect.w,
                                             group_rect.h - rect.h);

    // get the draw buffer
    struct nk_command_buffer *canvas = nk_window_get_canvas(ctx);

    // draw the rectangle and border
    nk_fill_rect(canvas, rect_add_margin, ROUNDNESS, NK_FOREGROUND_COLOR);
    nk_stroke_rect(canvas, rect_add_margin, ROUNDNESS, LINE_THICK, NK_BORDER_COLOR);

    return rect_add_margin;
}

// creates a dropdown box (nk_combo) with a title (nk_label_colored). padding_container is used to calculate the height based on the usable area.
void draw_dropdown(struct nk_context *ctx, struct nk_rect padding_container, float row_width, const char *title, const char **dropdown_items, int item_count, int *selected)
{
    // height calculations
    float title_height = padding_container.h * DROPDOWN_ROW_TITLE_HEIGHT_RATIO;
    float row_height = padding_container.h * DROPDOWN_ROW_HEIGHT_RATIO;

    // creates a label
    draw_title_label(ctx, title, title_height);

    // the size of each row when the dropbox is expanded
    struct nk_vec2 expanded_row_size = {
        .x = row_width, // this value is based on the dropdown box's padding containers
        .y = row_height * item_count};

    // creates a dropdown box
    nk_layout_row_dynamic(ctx, row_height, 1);
    *selected = nk_combo(ctx, dropdown_items, item_count, *selected, (int)row_height, expanded_row_size);
}

void draw_title_label(struct nk_context *ctx, const char *title, float row_height)
{
    nk_layout_row_dynamic(ctx, row_height, 1);
    nk_label_colored(ctx, title, NK_TEXT_LEFT, NK_PRIMARY_TEXT_COLOR);
}