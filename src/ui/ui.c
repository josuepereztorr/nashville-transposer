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

static const Color wht_note_pressed = {59, 130, 246, 255};
static const Color blk_note_pressed = {30, 58, 138, 255};

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

// void ui_crate_midi_device_container()
// {
//     // margins
//     int x_offset_margin = 20;
//     int y_offset_margin = 20;

//     // width
//     int half_width = (GetScreenWidth() / 2);
//     int quarter_width = (GetScreenWidth() / 4);

//     // height
//     int half_height = (GetScreenHeight() * HEIGHT_RATIO) / 2;
//     int full_height = (GetScreenHeight() * HEIGHT_RATIO) - 40;

//     // left side containers
//     DrawRectangle(x_offset_margin, y_offset_margin, quarter_width - 20, half_height - 40, failure_midi);
//     DrawRectangle(x_offset_margin, half_height, quarter_width - 20, half_height - 20, failure_midi);

//     // center container
//     DrawRectangle(quarter_width + x_offset_margin, y_offset_margin, half_width - 20, full_height, success_midi);

//     // right container
//     DrawRectangle(quarter_width + half_width + x_offset_margin, y_offset_margin, quarter_width - 40, full_height, failure_midi);
// }

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
    float note_padding = 2.0f;
    float total_padding = MAX_UI_NOTES * note_padding;
    int wht_note_width = (int)((container.width - total_padding) / MAX_UI_NOTES);

    int wht_note_index = 0;

    // draw all 74 white notes
    for (int midi_index = 0; midi_index < MAX_MIDI_NOTES; midi_index++)
    {
        // LOGIC FOR ALL WHITE NOTES

        // checks if the current midi note is a black note based on the is_blk_note array.
        if (!is_blk_note[midi_index % 12])
        {
            // calculate the chromatic scale degree based on the midi_index value
            int degree = midi_index % 12;

            if (degree == 0 || degree == 2 ||
                degree == 4 || degree == 5 ||
                degree == 7 || degree == 9 ||
                degree == 11 || degree == 12)
            {
                // create struct
                UINote note = {
                    .color = WHT_NOTE_COLOR};
                note.rec.x = container.x + (wht_note_index * (wht_note_width + note_padding));
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
                    notes[midi_index].color = wht_note_pressed;
                }

                // draw from array
                DrawRectangle(notes[midi_index].rec.x,
                              notes[midi_index].rec.y,
                              notes[midi_index].rec.width,
                              notes[midi_index].rec.height,
                              notes[midi_index].color);
            }

            // increase counter
            wht_note_index++;
        }
    }

    // reset counter
    wht_note_index = 0;

    // Purpose: draw all 53 black notes
    for (int midi_index = 0; midi_index < MAX_MIDI_NOTES; midi_index++)
    {
        // LOGIC FOR ALL BLACK NOTES

        // increase counter
        if (!is_blk_note[midi_index % 12])
        {
            wht_note_index++;
        }

        int degree = midi_index % 12;

        // 4 to 5 and 7-1 is only a half a step, meaning no black notes
        if (degree == 4 || degree == 11)
        {
            // don't add any keys
            continue;
        }

        float wht_note_offset = wht_note_index * (wht_note_width + note_padding);
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
            notes[midi_index].color = blk_note_pressed;
        }

        DrawRectangleRec(notes[midi_index].rec, notes[midi_index].color);
    }
}