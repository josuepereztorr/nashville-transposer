#include "keyboard.h"

// std lib
#include <stdio.h>

// vendor
#include "../vendor/raylib-nuklear.h"
#include "raylib.h"

// shared
#include "../theme.h"
#include "../../app.h"

// views
#include "layout.h"

// LOGIC
#define NUM_OF_OCTAVES 3
#define NOTES_IN_OCTAVE 12
#define WHT_NOTES_IN_OCTAVE 7
#define TOTAL_NOTES (NUM_OF_OCTAVES * NOTES_IN_OCTAVE)
#define TOTAL_WHT_NOTES (NUM_OF_OCTAVES * WHT_NOTES_IN_OCTAVE)

// UI
#define TOTAL_NOTE_PADDING (TOTAL_WHT_NOTES * WHT_NOTE_TRAIL_PADDING)
#define X_OFFSET_MARGIN 20.0f
#define Y_OFFSET_MARGIN 20.0f
#define BLK_NOTE_WIDTH_RATIO 0.6f
#define BLK_NOTE_ROUNDNESS 3.0f
#define WHT_NOTE_TRAIL_PADDING 2.0f
#define WHT_NOTE_ROUNDNESS 6.0f
#define CONT_UPPER_HEIGHT_RATIO 0.6f

typedef struct
{
    struct nk_rect rec;
    struct nk_color color;
} UIRectangle;

typedef struct
{
    struct nk_rect rec;
    struct nk_color color;
    int is_pressed;
    int id;
} UINote;

static UINote notes[NOTES_IN_OCTAVE * NUM_OF_OCTAVES] = {0};

/* black note indices are: 1, 3, 6, 8, 10
   white note indices are: 0, 2, 4, 5, 7, 9, 11 */
static const int is_blk_note[12] = {
    0,  // C
    1,  // C#
    0,  // D
    1,  // D#
    0,  // E
    0,  // F
    1,  // F#
    0,  // G
    1,  // G#
    0,  // A
    1,  // A#
    0}; // B

static int get_wht_note_width(struct nk_rect rec);
static UINote create_wht_note(int note_index, const struct nk_rect container);
static void draw_wht_notes(struct nk_context *ui_ctx, AppContext *app_ctx, int note_index, struct nk_rect container);
static UINote create_blk_note(int note_index, const struct nk_rect container);
static void draw_blk_notes(struct nk_context *ui_ctx, AppContext *app_ctx, int note_index, const struct nk_rect container);

void draw_keyboard_container(struct nk_context *ui_ctx, AppContext *app_ctx)
{
    struct nk_rect margin_rec = {.x = MARGIN, .y = 0, .w = MARGIN * 2.0f, .h = MARGIN};
    struct nk_rect keyboard_rect = draw_container(ui_ctx, margin_rec, NK_FOREGROUND_COLOR, NK_BORDER_COLOR);

    int wht_note_index = 0;
    draw_wht_notes(ui_ctx, app_ctx, wht_note_index, keyboard_rect);

    wht_note_index = 0;
    draw_blk_notes(ui_ctx, app_ctx, wht_note_index, keyboard_rect);
};

static int get_wht_note_width(struct nk_rect rec)
{
    float content_width = rec.w - TOTAL_NOTE_PADDING - X_OFFSET_MARGIN;
    int wht_note_width = (int)(content_width / TOTAL_WHT_NOTES);
    return wht_note_width;
}

static UINote create_wht_note(int note_index, const struct nk_rect container)
{
    int wht_note_width = get_wht_note_width(container);

    // create struct
    UINote note = {
        .color = NK_WHT_NOTE_COLOR};
    note.rec.x = container.x + (note_index * (wht_note_width + WHT_NOTE_TRAIL_PADDING)) + X_OFFSET_MARGIN;
    note.rec.y = container.y + Y_OFFSET_MARGIN;
    note.rec.w = wht_note_width;
    note.rec.h = container.h - (Y_OFFSET_MARGIN * 2);
    note.is_pressed = false;
    note.id = 0;

    return note;
}
static UINote create_blk_note(int note_index, const struct nk_rect container)
{
    int wht_note_width = get_wht_note_width(container);

    float wht_note_offset = note_index * (wht_note_width + WHT_NOTE_TRAIL_PADDING);
    float blk_note_offset = (wht_note_width * BLK_NOTE_WIDTH_RATIO) / 2.0f;

    UINote note = {
        .color = NK_BLK_NOTE_COLOR};
    note.rec.x = (X_OFFSET_MARGIN + (container.x + wht_note_offset) - blk_note_offset);
    note.rec.y = container.y + Y_OFFSET_MARGIN;
    note.rec.w = wht_note_width * BLK_NOTE_WIDTH_RATIO;
    note.rec.h = (container.h * CONT_UPPER_HEIGHT_RATIO) - (Y_OFFSET_MARGIN * 2);
    note.is_pressed = false;
    note.id = 0;

    return note;
}

static void draw_wht_notes(struct nk_context *ui_ctx, AppContext *app_ctx, int note_index, struct nk_rect container)
{
    struct nk_command_buffer *canvas = nk_window_get_canvas(ui_ctx);

    for (int midi_index = 0; midi_index < TOTAL_NOTES; midi_index++)
    {
        // calculate the chromatic scale degree based on the midi_index value
        int degree = midi_index % 12;

        // checks if the current midi note is a black note based on the is_blk_note array.
        if (!is_blk_note[degree])
        {
            UINote note = create_wht_note(note_index, container);
            note.id = midi_index;

            notes[midi_index] = note;

            // TEST DATA
            notes[2].is_pressed = 1;
            notes[7].is_pressed = 1;
            notes[11].is_pressed = 1;

            // check if the current note is pressed
            if (notes[midi_index].is_pressed)
            {
                notes[midi_index].color = NK_WHT_NOTE_PRESSED_COLOR;
            }

            nk_fill_rect(canvas,
                         notes[midi_index].rec,
                         WHT_NOTE_ROUNDNESS,
                         notes[midi_index].color);

            note_index++;
        }
    }
}

static void draw_blk_notes(struct nk_context *ui_ctx, AppContext *app_ctx, int note_index, const struct nk_rect container)
{
    struct nk_command_buffer *canvas = nk_window_get_canvas(ui_ctx);

    for (int midi_index = 0; midi_index < TOTAL_NOTES; midi_index++)
    {
        int degree = midi_index % 12;

        if (!is_blk_note[degree % 12])
        {
            note_index++;
        }

        // 4 to 5 and 7-1 is only a half a step
        if (degree == 4 || degree == 11)
        {
            continue;
        }

        UINote note = create_blk_note(note_index, container);
        note.id = midi_index;

        // add to array
        notes[midi_index] = note;

        // midi simulation
        notes[3].is_pressed = 1;
        notes[8].is_pressed = 1;
        notes[10].is_pressed = 1;

        // press note
        if (notes[midi_index].is_pressed)
        {
            notes[midi_index].color = NK_BLK_NOTE_PRESSED_COLOR;
        }

        nk_fill_rect(canvas,
                     notes[midi_index].rec,
                     BLK_NOTE_ROUNDNESS,
                     notes[midi_index].color);
    }
}