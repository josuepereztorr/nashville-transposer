#include <stdio.h>
#include "../ui/ui.h"

#define MAX_UI_NOTES 21
#define MAX_MIDI_NOTES 128
#define MAX_WHT_NOTES 74
#define MAX_BLK_NOTES 53
#define UI_SCREEN_WIDTH GetScreenWidth()
#define UI_SCREEN_HEIGHT GetScreenHeight()

const Color background = {18, 20, 28, 255};
const Color foreground = {27, 29, 40, 255};
const Color border = {42, 45, 58, 255};
const Color primary_text = {242, 242, 245, 255};
const Color secondary_text = {148, 251, 166, 255};
const Color success_midi = {74, 222, 128, 255};
const Color failure_midi = {232, 97, 93, 255};

typedef struct
{
    int x_offset;
    int y_offset;
    int width;
    int height;
    Color color;
} UIElement;

typedef struct
{
    UIElement el;
    int is_pressed;
    int id;
} UINote;

UIElement create_el_container(int x_offset, int screen_height, int width, double height_ratio);
UINote create_wht_note(UIElement el);
UINote create_blk_note(UIElement el);

// based on MAX_NUM_OF_NOTES 120
UINote wht_notes[MAX_WHT_NOTES] = {0};

UINote blk_notes[MAX_BLK_NOTES] = {0};

UINote notes[MAX_MIDI_NOTES] = {0};

void ui_create_keyboard()
{
    // padding between white note
    int note_padding = 2;

    int x_offset = 20;
    double height_ratio = 0.6;
    UIElement container = create_el_container(x_offset, UI_SCREEN_HEIGHT, UI_SCREEN_WIDTH, height_ratio);

    /* black notes are: 1, 3, 6, 8, 10
       white notes are: 0, 2, 4, 5, 7, 9, 11 */
    int is_black_note[12] = {0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0};

    // Purpose: wht_note_width multiplier
    int wht_note_counter = 0;

    // padding between white notes
    int total_padding = MAX_UI_NOTES * note_padding;
    int wht_note_width = ((container.width - total_padding) / MAX_UI_NOTES);
    // int wht_note_width = ((container.width - total_padding) / MAX_UI_NOTES) + note_padding;

    // Purpose: draw all 74 white notes
    for (int midi_index = 0; midi_index < MAX_MIDI_NOTES; midi_index++)
    {
        // Purpose: checks if the current midi note is a black note based on the is_black_note array.
        if (!is_black_note[midi_index % 12])
        {
            // LOGIC FOR ALL WHITE NOTES

            // calculate the chromatic scale degree based on the midi_index value
            int degree = midi_index % 12;

            if (degree == 0 || degree == 2 ||
                degree == 4 || degree == 5 ||
                degree == 7 || degree == 9 ||
                degree == 11 || degree == 12)
            {
                /* white note x-offset: starts at the same x-offset as the contianer, then adds the note width plus padding times the note number. */
                int x_offset = container.x_offset + (wht_note_counter * (wht_note_width + note_padding));

                // create struct
                UINote wht_note = {0};
                wht_note.el.x_offset = x_offset;
                wht_note.el.y_offset = container.y_offset;
                wht_note.el.width = wht_note_width;
                wht_note.el.height = container.height;
                wht_note.el.color = primary_text;
                wht_note.id = midi_index;
                wht_note.is_pressed = 0;

                // add to array
                notes[midi_index] = wht_note;

                // TEST DATA
                notes[2].is_pressed = 1;
                notes[7].is_pressed = 1;
                notes[11].is_pressed = 1;

                // check if the current note is pressed
                if (notes[midi_index].is_pressed)
                {
                    notes[midi_index].el.color = success_midi;
                }

                // draw from array
                // PROBLEM - INDEX GOES OUT OF BOUNDS - OUT OF MEMORY
                DrawRectangle(notes[midi_index].el.x_offset,
                              notes[midi_index].el.y_offset,
                              notes[midi_index].el.width,
                              notes[midi_index].el.height,
                              notes[midi_index].el.color);
            }

            // increase counter
            wht_note_counter++;
        }
    }

    // reset counter
    wht_note_counter = 0;

    // Purpose: draw all 53 black notes
    for (int midi_index = 0; midi_index < MAX_MIDI_NOTES; midi_index++)
    {
        // LOGIC FOR ALL BLACK NOTES

        // increase counter
        if (!is_black_note[midi_index % 12])
        {
            wht_note_counter++;
        }

        int degree = midi_index % 12;

        // 4 to 5 and 7-1 is only a half a step, meaning no black notes
        if (degree == 4 || degree == 11)
        {
            // don't add any keys
            continue;
        }

        // TODO - CHECK IF I CAN JUST REMOVE THE MULTIPLE
        /* black note x-offset: starts at the same x-offset as the contianer, then adds the note width plus padding times the note number. */
        int x_offset = (container.x_offset + (wht_note_counter * (wht_note_width + note_padding)) - ((wht_note_width * 0.6) / 2));

        // create struct
        UINote blk_note = {0};
        blk_note.el.x_offset = x_offset;
        blk_note.el.y_offset = container.y_offset;
        blk_note.el.width = wht_note_width;
        blk_note.el.height = container.height;
        blk_note.el.color = border;
        blk_note.id = midi_index;
        blk_note.is_pressed = 0;

        // add to array
        notes[midi_index] = blk_note;

        // midi simulation
        notes[18].is_pressed = 1;
        notes[20].is_pressed = 1;
        notes[22].is_pressed = 1;

        // press note
        if (notes[midi_index].is_pressed)
        {
            notes[midi_index].el.color = failure_midi;
        }

        DrawRectangle(notes[midi_index].el.x_offset,
                      notes[midi_index].el.y_offset,
                      (notes[midi_index].el.width * 0.6),
                      notes[midi_index].el.height * 0.6,
                      notes[midi_index].el.color);
    }
}

UINote create_wht_note(UIElement el)
{
    UINote wht_note = {};
    wht_note.el = el;
    wht_note.el.width = el.width / MAX_UI_NOTES;
    wht_note.el.color = primary_text;
    DrawRectangle(wht_note.el.x_offset,
                  wht_note.el.y_offset,
                  wht_note.el.width,
                  wht_note.el.height,
                  wht_note.el.color);

    return wht_note;
}

UINote create_blk_note(UIElement el)
{
    // white to black note ratios
    const float width_ratio = 1.7;
    const float height_ratio = 1.5;
    const float offset_ratio = 0.75;

    UINote blk_note = {};
    blk_note.el = el;
    blk_note.el.x_offset = blk_note.el.x_offset + (blk_note.el.width * offset_ratio);
    blk_note.el.width /= width_ratio;
    blk_note.el.height /= height_ratio;
    blk_note.el.color = border;

    DrawRectangle(blk_note.el.x_offset,
                  blk_note.el.y_offset,
                  blk_note.el.width,
                  blk_note.el.height,
                  blk_note.el.color);

    return blk_note;
}

// height_ratio from 0.000 to 1.000
UIElement create_el_container(int x_offset, int screen_height, int screen_width, double height_ratio)
{
    UIElement el;
    el.x_offset = x_offset;
    el.y_offset = screen_height * height_ratio;
    el.width = screen_width - (el.x_offset * 2);
    el.height = (screen_height * (1 - height_ratio)) - (el.x_offset * 2);
    DrawRectangle(el.x_offset, el.y_offset, el.width, el.height, background);

    return el;
}
