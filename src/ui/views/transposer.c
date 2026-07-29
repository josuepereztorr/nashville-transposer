#include "transposer.h"

// std lib
#include <stdio.h>

// vendor
#include "../vendor/raylib-nuklear.h"

// shared
#include "../theme.h"
#include "../../theory/scales.h"
#include "../../app.h"

// views
#include "layout.h"

typedef struct
{
    char current_note_display[10];
    char target_note_display[10];
    char nashville_display[10];
} TransposerDisplay;

static void update_note_display(AppContext *app_ctx, TransposerDisplay *display);

void draw_transposer_container(struct nk_context *ui_ctx, AppContext *app_ctx)
{
    struct nk_rect margin_rec = {.x = MARGIN, .y = MARGIN, .w = MARGIN, .h = MARGIN * 2.0f};
    struct nk_rect relative_container_rect = draw_container(ui_ctx, margin_rec, NK_FOREGROUND_COLOR, NK_BORDER_COLOR);

    nk_layout_space_begin(ui_ctx, NK_STATIC, relative_container_rect.h, 2);

    // NOTE: nk_layout_space_push uses coordinates from the local group, not based on the current screen.
    // the x and y dimensions are relative to margin_rect. We can reuse the card container but we need to convert our coordinates.
    struct nk_rect absolute_rect = nk_layout_space_rect_to_local(ui_ctx, relative_container_rect);

    // row ratios based on the card container's height
    float title_height = 24.0f;
    float item_height = absolute_rect.h * 0.35f;

    // makes the initial characters dashes
    static TransposerDisplay display = {"-", "-", "-"};

    // get all the values before doing any ui work
    update_note_display(app_ctx, &display);

    // CARD TITLE
    // inner container with padding
    struct nk_rect nashville_num_pad_rect = {
        .x = absolute_rect.x + (MARGIN * 2.0f),
        .y = absolute_rect.y + (MARGIN * 2.0f),
        .w = absolute_rect.w - (MARGIN * 4.0f),
        .h = title_height + item_height};

    // TOP ROW
    nk_layout_space_push(ui_ctx, nashville_num_pad_rect);
    if (nk_group_begin(ui_ctx, "nashville_number", NK_WINDOW_NO_SCROLLBAR))
    {
        // title label
        nk_style_push_font(ui_ctx, app_get_title_font());
        nk_layout_row_dynamic(ui_ctx, title_height, 1);
        nk_label_colored(ui_ctx, "NASHVILLE NUMBER", NK_TEXT_CENTERED, NK_PRIMARY_TEXT_COLOR);
        nk_style_pop_font(ui_ctx);

        // Note
        nk_style_push_font(ui_ctx, app_get_display_font());
        nk_layout_row_dynamic(ui_ctx, item_height, 1);
        nk_label_colored(ui_ctx, display.nashville_display, NK_TEXT_CENTERED, NK_PRIMARY_TEXT_COLOR);
        nk_style_pop_font(ui_ctx);
        nk_group_end(ui_ctx);
    }

    // BOTTOM ROW WITH 2 COLUMNS
    struct nk_rect key_pad_rect =
        {
            .x = absolute_rect.x + (MARGIN * 2.0f),
            .y = nashville_num_pad_rect.y + nashville_num_pad_rect.h + MARGIN,
            .w = absolute_rect.w - (MARGIN * 4.0f),
            .h = title_height + item_height};

    nk_layout_space_push(ui_ctx, key_pad_rect);
    if (nk_group_begin(ui_ctx, "notes_transposer", NK_WINDOW_NO_SCROLLBAR))
    {
        // title label
        nk_style_push_font(ui_ctx, app_get_title_font());
        nk_layout_row_dynamic(ui_ctx, title_height, 2);
        nk_label_colored(ui_ctx, "CURRENT NOTE", NK_TEXT_CENTERED, NK_PRIMARY_TEXT_COLOR);
        nk_label_colored(ui_ctx, "TARGET NOTE", NK_TEXT_CENTERED, NK_PRIMARY_TEXT_COLOR);
        nk_style_pop_font(ui_ctx);

        nk_style_push_font(ui_ctx, app_get_display_font());
        nk_layout_row_dynamic(ui_ctx, item_height, 2);
        nk_label_colored(ui_ctx, display.current_note_display, NK_TEXT_CENTERED, NK_DEGREE_COLOR);
        nk_label_colored(ui_ctx, display.target_note_display, NK_TEXT_CENTERED, NK_TARGET_COLOR);
        nk_style_pop_font(ui_ctx);

        nk_group_end(ui_ctx);
    }
};

static void update_note_display(AppContext *app_ctx, TransposerDisplay *display)
{
    // get the decoded message
    int status = Pm_MessageStatus(app_ctx->event.message);

    //
    int type = status & 0xF0;

    // CASE #1 - NOTE DEPRESSED
    if (type != 0x90 || Pm_MessageData2(app_ctx->event.message) <= 0)
    {
        return;
    }

    // CURRENT NOTE
    int played_note = Pm_MessageData1(app_ctx->event.message);
    int chromatic_position = played_note % 12;

    snprintf(display->current_note_display, sizeof(display->current_note_display), "%s", note_names[chromatic_position]);

    // get the scale degree passing in the midi_note
    int degree = get_scale_degree(played_note, app_ctx->current_key_selected);

    // note is not in scale, don't do any ui changes
    if (degree == -1)
    {
        snprintf(display->nashville_display, sizeof(display->nashville_display), "-");
        snprintf(display->target_note_display, sizeof(display->target_note_display), "-");
        return;
    }

    snprintf(display->nashville_display, sizeof(display->nashville_display), "%d", degree);

    int transposed_semitone = get_transposed_note(degree, app_ctx->target_key_selected);

    if (transposed_semitone == -1)
    {
        return;
    }

    snprintf(display->target_note_display, sizeof(display->target_note_display), "%s", note_names[transposed_semitone]);
}