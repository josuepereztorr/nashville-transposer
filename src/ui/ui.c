#include <stdio.h>
#include "../ui/ui.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

// LOGIC
#define MAX_UI_NOTES 21
#define MAX_MIDI_NOTES 128
#define MAX_WHT_NOTES 74
#define MAX_BLK_NOTES 53

// UI
#define X_OFFSET_MARGIN 20
#define Y_OFFSET_MARGIN 20
#define WIDTH_RATIO 0.6f
#define HEIGHT_RATIO 0.6f
#define NOTE_PADDING 2.0f

typedef struct
{
    Rectangle rec;
    Color color;
} UIRectangle;

typedef struct
{
    Rectangle rec;
    Color color;
    bool is_pressed;
    int id;
} UINote;

static const Color wht_note_pressed_color = {59, 130, 246, 255};
static const Color blk_note_pressed_color = {30, 58, 138, 255};

/* black note indices are: 1, 3, 6, 8, 10
       white note indices are: 0, 2, 4, 5, 7, 9, 11 */
static const bool is_blk_note[12] = {
    false,  // C
    true,   // C#
    false,  // D
    true,   // D#
    false,  // E
    false,  // F
    true,   // F#
    false,  // G
    true,   // G#
    false,  // A
    true,   // A#
    false}; // B

// based on MAX_NUM_OF_NOTES 120
UINote wht_notes[MAX_WHT_NOTES] = {0};

UINote blk_notes[MAX_BLK_NOTES] = {0};

UINote notes[MAX_MIDI_NOTES] = {0};

float total_padding = MAX_UI_NOTES * NOTE_PADDING;

const Color success_midi;
const Color failure_midi;

void create_wht_notes(int note_index, Rectangle container);
void create_blk_notes(int note_index, Rectangle container);

void ui_crate_midi_device_container()
{
    // margins
    int x_offset_margin = 20;
    int y_offset_margin = 20;

    // width
    int half_width = (GetScreenWidth() / 2);
    int quarter_width = (GetScreenWidth() / 4);

    // height
    int half_height = (GetScreenHeight() * HEIGHT_RATIO) / 2;
    int full_height = (GetScreenHeight() * HEIGHT_RATIO) - 40;

    // left side containers
    Rectangle midi_device_container = {
        .x = x_offset_margin,
        .y = y_offset_margin,
        .width = quarter_width - 20,
        .height = half_height - 40};

    DrawRectangleRec(midi_device_container, failure_midi);

    Rectangle scale_selection_container = {
        .x = x_offset_margin,
        .y = half_height,
        .width = quarter_width - 20,
        .height = half_height - 20};

    DrawRectangleRec(scale_selection_container, failure_midi);

    // center container
    Rectangle transposer_container = {
        .x = quarter_width + x_offset_margin,
        .y = y_offset_margin,
        .width = half_width - 20,
        .height = full_height};

    DrawRectangleRec(transposer_container, success_midi);

    // right container
    Rectangle history_container = {
        .x = quarter_width + half_width + x_offset_margin,
        .y = y_offset_margin,
        .width = quarter_width - 40,
        .height = full_height};

    DrawRectangleRec(history_container, failure_midi);
}

// void ui_create_drowndown()
// {
//     const char *text = "; Digital Input; Digital Output; Midi Keyboard";
//     int is_active = 0;
//     int is_editable = 0;

//     Rectangle rec = {0};
//     rec.height = 200;
//     rec.width = 400;
//     rec.x = 20;
//     rec.y = 20;

//     if (GuiDropdownBox(rec, text, &is_active, is_editable))
//     {
//         is_editable = !is_editable;
//     }

//     DrawText(TextFormat("Selected index: %i", is_active), 150, 150, 20, DARKGRAY);
// }

void ui_create_keyboard()
{
    // window dimentions
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    // keyboard container
    Rectangle container = {0};
    container.x = X_OFFSET_MARGIN;
    container.y = screen_height * HEIGHT_RATIO;
    container.width = screen_width - (container.x * 2.0f);
    container.height = ((screen_height * (1.0f - HEIGHT_RATIO)) - (container.x * 2.0f));
    DrawRectangleRec(container, FILL_COLOR);

    // white note padding
    int wht_note_width = (int)((container.width - total_padding) / MAX_UI_NOTES);

    int wht_note_index = 0;

    create_wht_notes(wht_note_index, container);

    // reset counter
    wht_note_index = 0;

    create_blk_notes(wht_note_index, container);
}

void create_wht_notes(int note_index, const Rectangle container)
{
    // draw all 74 white notes
    for (int midi_index = 0; midi_index < MAX_MIDI_NOTES; midi_index++)
    {
        // calculate the chromatic scale degree based on the midi_index value
        int degree = midi_index % 12;

        // checks if the current midi note is a black note based on the is_blk_note array.
        if (!is_blk_note[degree])
        {

            if (degree == 0 || degree == 2 ||
                degree == 4 || degree == 5 ||
                degree == 7 || degree == 9 ||
                degree == 11 || degree == 12)
            {
                int wht_note_width = (int)((container.width - total_padding) / MAX_UI_NOTES);

                // create struct
                UINote note = {
                    .color = WHT_NOTE_COLOR};
                note.rec.x = container.x + (note_index * (wht_note_width + NOTE_PADDING));
                note.rec.y = container.y;
                note.rec.width = wht_note_width;
                note.rec.height = container.height;
                note.is_pressed = false;
                note.id = midi_index;

                // add to array
                notes[midi_index] = note;

                // TEST DATA
                notes[2].is_pressed = 1;
                notes[7].is_pressed = 1;
                notes[11].is_pressed = 1;

                // check if the current note is pressed
                if (notes[midi_index].is_pressed)
                {
                    notes[midi_index].color = wht_note_pressed_color;
                }

                // draw from array
                DrawRectangle(notes[midi_index].rec.x,
                              notes[midi_index].rec.y,
                              notes[midi_index].rec.width,
                              notes[midi_index].rec.height,
                              notes[midi_index].color);
            }

            // increase counter
            note_index++;
        }
    }
}

void create_blk_notes(int note_index, const Rectangle container)
{

    // draws all 53 black notes
    for (int midi_index = 0; midi_index < MAX_MIDI_NOTES; midi_index++)
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

        int wht_note_width = (int)((container.width - total_padding) / MAX_UI_NOTES);

        float wht_note_offset = note_index * (wht_note_width + NOTE_PADDING);
        float blk_note_offset = (wht_note_width * WIDTH_RATIO) / 2.0f;

        UINote note = {
            .color = BLK_NOTE_COLOR};
        note.rec.x = (container.x + wht_note_offset) - blk_note_offset;
        note.rec.y = container.y;
        note.rec.width = wht_note_width * WIDTH_RATIO;
        note.rec.height = container.height * HEIGHT_RATIO;
        note.is_pressed = false;
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
            notes[midi_index].color = blk_note_pressed_color;
        }

        DrawRectangleRec(notes[midi_index].rec, notes[midi_index].color);
    }
}