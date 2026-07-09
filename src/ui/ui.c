#include <stdio.h>
#include "../ui/ui.h"

#define MAX_NOTES_ON_UI 21
#define MAX_NUM_OF_NOTES 120
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
UINote wht_notes[70] = {};
UINote blk_notes[50] = {};

void ui_create_keyboard()
{
    // padding between white keys
    int key_padding = 2;

    int x_offset = 20;
    double height_ratio = 0.6;
    UIElement container = create_el_container(x_offset, UI_SCREEN_HEIGHT, UI_SCREEN_WIDTH, height_ratio);

    /* black keys are: 1, 3, 6, 8, 10
       white keys are: 0, 2, 4, 5, 7, 9, 11 */
    int is_black_key[12] = {0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0};
    int wht_key_counter = 0;

    // padding between white keys
    int total_key_padding = MAX_NOTES_ON_UI * key_padding;
    int wht_note_width = (container.width - total_key_padding) / MAX_NOTES_ON_UI;

    // draw white keys
    for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
    {
        // keeps the index within an octave
        if (!is_black_key[i % 12])
        {
            /* white key x-offset: starts at the same x-offset as the contianer, then adds the key width plus padding times the key number. */
            int x_offset = container.x_offset + (wht_key_counter * (wht_note_width + key_padding));

            // create
            UINote wht_note = {};
            wht_note.el.x_offset = x_offset;
            wht_note.el.y_offset = container.y_offset;
            wht_note.el.width = wht_note_width;
            wht_note.el.height = container.height;
            wht_note.el.color = primary_text;
            wht_note.id = i;
            wht_note.is_pressed = 0;

            // calcualte the degree based on the i value
            int d = i % 12;
            if (d == 0 || d == 2 || d == 4 || d == 5 || d == 7 || d == 9 || d == 11 || d == 12)
            {
                // add to array
                wht_notes[i] = wht_note;

                // midi simulation
                wht_notes[14].is_pressed = 1;
                wht_notes[16].is_pressed = 1;
                wht_notes[24].is_pressed = 1;

                // press key
                if (wht_notes[i].is_pressed)
                {
                    wht_notes[i].el.color = success_midi;
                }

                // draw from array
                DrawRectangle(wht_notes[i].el.x_offset,
                              wht_notes[i].el.y_offset,
                              wht_notes[i].el.width,
                              wht_notes[i].el.height,
                              wht_notes[i].el.color);
            }
            wht_key_counter++;
        }
    }

    wht_key_counter = 0;

    // draw black keys
    for (int i = 0; i < MAX_NUM_OF_NOTES; i++)
    {
        int x_offset = (container.x_offset + (wht_key_counter * (wht_note_width + key_padding))) - ((wht_note_width * 0.6) / 2);

        // keeps the index within an octave
        if (!is_black_key[i % 12])
        {
            wht_key_counter++;
        }

        // create
        UINote blk_note = {};
        blk_note.el.x_offset = x_offset;
        blk_note.el.y_offset = container.y_offset;
        blk_note.el.width = wht_note_width;
        blk_note.el.height = container.height;
        blk_note.el.color = border;
        blk_note.id = i;
        blk_note.is_pressed = 0;

        // don't create a black key for index 4 or index 11
        int d = i % 12;
        if (d == 4 || d == 11)
        {
            continue;
        }
        else if (d == 1 || d == 3 || d == 6 || d == 8 || d == 10)
        {

            // add to array
            blk_notes[i] = blk_note;

            // midi simulation
            blk_notes[1].is_pressed = 1;
            blk_notes[13].is_pressed = 1;
            blk_notes[18].is_pressed = 1;

            // press key
            if (blk_notes[i].is_pressed)
            {
                blk_notes[i].el.color = failure_midi;
            }

            DrawRectangle(blk_notes[i].el.x_offset,
                          blk_notes[i].el.y_offset,
                          (blk_notes[i].el.width * 0.6),
                          blk_notes[i].el.height * 0.6,
                          blk_notes[i].el.color);
        }
    }
}

UINote create_wht_note(UIElement el)
{
    UINote wht_note = {};
    wht_note.el = el;
    wht_note.el.width = el.width / MAX_NOTES_ON_UI;
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
