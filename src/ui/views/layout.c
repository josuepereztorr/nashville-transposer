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

// draws the main app containers based on a Nuklear's row/column layout.
void draw_layout(struct nk_context *ctx)
{
    // get the screen size and spit it up into ratio of 60/40
    Vector2 monitor_size = get_monitor_dimensions();
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
        struct nk_rect settings_rec = nk_window_get_content_region(ctx);
        float half_height = settings_rec.h * 0.5f;

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
void draw_container(struct nk_context *ctx, struct nk_rect rec)
{
    // gets the rectangle dimensions of the parent group
    struct nk_rect group_rec = nk_window_get_content_region(ctx);

    // adds the function's caller margin
    struct nk_rect margin = nk_rect(group_rec.x + rec.x,
                                    group_rec.y + rec.y,
                                    group_rec.w - rec.w,
                                    group_rec.h - rec.h);

    // get the draw buffer
    struct nk_command_buffer *canvas = nk_window_get_canvas(ctx);

    // draw the rectangle and border
    nk_fill_rect(canvas, margin, ROUNDNESS, NK_FOREGROUND_COLOR);
    nk_stroke_rect(canvas, margin, ROUNDNESS, LINE_THICK, NK_BORDER_COLOR);
}