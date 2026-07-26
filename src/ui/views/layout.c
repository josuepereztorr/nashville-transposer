#include "layout.h"
#include "../vendor/nuklear.h"
#include "../../app_init.h"
#include "raylib.h"
#include "../theme.h"

#define UPPER_HEIGHT_RATIO 0.6f
#define LOWER_HEIGHT_RATIO 0.4f
#define QUARTER_WIDTH_RATIO 0.25f
#define HALF_WIDTH_RATIO 0.5f

void draw_layout(struct nk_context *ctx)
{
    Vector2 monitor_size = get_monitor_dimensions();

    float upper_height = monitor_size.y * UPPER_HEIGHT_RATIO;
    float lower_height = monitor_size.y * LOWER_HEIGHT_RATIO;

    // upper row
    nk_layout_row_begin(ctx, NK_DYNAMIC, upper_height, 3);

    // column #1
    nk_layout_row_push(ctx, QUARTER_WIDTH_RATIO);
    if (nk_group_begin(ctx, "settings", NK_WINDOW_NO_SCROLLBAR))
    {
        // get the dimensions of the "settings" group
        struct nk_rect settings_rec = nk_window_get_content_region(ctx);
        float half_height = settings_rec.h * 0.5f;

        nk_layout_row_dynamic(ctx, half_height, 1);
        if (nk_group_begin(ctx, "midi_device", NK_WINDOW_NO_SCROLLBAR))
        {
            struct nk_rect midi_rec = nk_window_get_content_region(ctx);
            struct nk_rect margin = nk_rect(midi_rec.x + MARGIN, midi_rec.y + MARGIN, midi_rec.w - MARGIN, midi_rec.h - (MARGIN * 2.0f));

            struct nk_command_buffer *canvas = nk_window_get_canvas(ctx);

            nk_fill_rect(canvas, margin, ROUNDNESS, NK_DEGREE_COLOR);

            // midi device
            nk_group_end(ctx);
        }

        nk_layout_row_dynamic(ctx, half_height, 1);
        if (nk_group_begin(ctx, "scale_selection", NK_WINDOW_NO_SCROLLBAR))
        {
            struct nk_rect midi_rec = nk_window_get_content_region(ctx);
            struct nk_rect margin = nk_rect(midi_rec.x + MARGIN, midi_rec.y, midi_rec.w - MARGIN, midi_rec.h - MARGIN);

            struct nk_command_buffer *canvas = nk_window_get_canvas(ctx);

            nk_fill_rect(canvas, margin, ROUNDNESS, NK_TARGET_COLOR);

            // scale selection
            nk_group_end(ctx);
        }
        nk_group_end(ctx);
    }

    // column #2
    nk_layout_row_push(ctx, HALF_WIDTH_RATIO);
    if (nk_group_begin(ctx, "transposer", NK_WINDOW_NO_SCROLLBAR))
    {
        struct nk_rect midi_rec = nk_window_get_content_region(ctx);
        struct nk_rect margin = nk_rect(midi_rec.x + MARGIN, midi_rec.y + MARGIN, midi_rec.w - MARGIN, midi_rec.h - (MARGIN * 2.0f));

        struct nk_command_buffer *canvas = nk_window_get_canvas(ctx);

        nk_fill_rect(canvas, margin, ROUNDNESS, NK_TARGET_COLOR);

        nk_group_end(ctx);
    }

    // column #3
    nk_layout_row_push(ctx, QUARTER_WIDTH_RATIO);
    if (nk_group_begin(ctx, "history", NK_WINDOW_NO_SCROLLBAR))
    {
        struct nk_rect midi_rec = nk_window_get_content_region(ctx);
        struct nk_rect margin = nk_rect(midi_rec.x + MARGIN, midi_rec.y + MARGIN, midi_rec.w - 40, midi_rec.h - (MARGIN * 2.0f));

        struct nk_command_buffer *canvas = nk_window_get_canvas(ctx);

        nk_fill_rect(canvas, margin, ROUNDNESS, NK_TARGET_COLOR);
        nk_group_end(ctx);
    }

    nk_layout_row_end(ctx);

    // lower row
    nk_layout_row_dynamic(ctx, lower_height, 1);
    if (nk_group_begin(ctx, "keyboard", NK_WINDOW_NO_SCROLLBAR))
    {
        struct nk_rect midi_rec = nk_window_get_content_region(ctx);
        struct nk_rect margin = nk_rect(midi_rec.x + MARGIN, midi_rec.y, midi_rec.w - (MARGIN * 2.0f), midi_rec.h - MARGIN);

        struct nk_command_buffer *canvas = nk_window_get_canvas(ctx);

        nk_fill_rect(canvas, margin, ROUNDNESS, NK_DEGREE_COLOR);

        // keyboard view
        nk_group_end(ctx);
    }
}