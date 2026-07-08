#include <stdio.h>
#include "../ui/ui.h"

#define UI_MAX_KEYS 21
#define UI_MAX_NUM_OF_NOTES 128
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
UINote create_wht_note_with_multiplier(UIElement el, int num);
UINote create_wht_note(UIElement el);
UINote create_blk_note(UIElement el);

UINote notes[UI_MAX_NUM_OF_NOTES] = {};

void ui_create_keyboard()
{
    int x_offset = 20;
    double height_ratio = 0.6;
    UIElement container = create_el_container(x_offset, UI_SCREEN_HEIGHT, UI_SCREEN_WIDTH, height_ratio);
    // UINote wht_note = create_wht_note(container);
    //  UINote blk_note = create_blk_note(wht_note.el);

    // chromatic scale
    // black keys are: 1, 3, 6, 8, 10
    // white keys are: 0, 2, 4, 5, 7, 9, 11
    int is_black_key[12] = {0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0};
    int wht_key_counter = 0;

    // space between keys
    int key_padding = 2;
    int total_key_padding = UI_MAX_KEYS * key_padding;
    int wht_note_width = (container.width - total_key_padding) / UI_MAX_KEYS;

    for (int i = 0; i < UI_MAX_NUM_OF_NOTES; i++)
    {
        // keeps the index within an octave
        if (!is_black_key[i % 12])
        {
            // create white key
            // need to create a UINote and add it to the array.
            int x_offset = container.x_offset + (wht_key_counter * (wht_note_width + key_padding));
            DrawRectangle(x_offset, container.y_offset, wht_note_width, container.height, primary_text);
            wht_key_counter++;
        }
    }

    wht_key_counter = 0;

    for (int i = 0; i < UI_MAX_NUM_OF_NOTES; i++)
    {
        // keeps the index within an octave
        if (!is_black_key[i % 12])
        {
            wht_key_counter++;
        }

        int x_offset = (container.x_offset + (wht_key_counter * (wht_note_width + key_padding))) - ((wht_note_width * 0.6) / 2);
        DrawRectangle(x_offset, container.y_offset, (wht_note_width * 0.6), container.height * 0.6, border);
    }
}

UINote create_wht_note(UIElement el)
{
    UINote wht_note = {};
    wht_note.el = el;
    wht_note.el.width = el.width / UI_MAX_KEYS;
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
    DrawRectangle(el.x_offset, el.y_offset, el.width, el.height, success_midi);

    return el;
}

UINote create_wht_note_with_multiplier(UIElement el, int multiplier)
{
    // space between keys
    int key_padding = 2;
    int total_key_padding = UI_MAX_KEYS * key_padding;

    UINote note = {};
    note.el = el;
    note.el.x_offset = note.el.x_offset + multiplier;
    note.el.width = (note.el.width - total_key_padding) / UI_MAX_KEYS;

    if (multiplier > 0)
    {
        multiplier = (multiplier * note.el.width) + (multiplier * key_padding);
    }

    note.el.x_offset += multiplier;
    note.el.color = primary_text;

    DrawRectangle(note.el.x_offset,
                  note.el.y_offset,
                  note.el.width,
                  note.el.height,
                  note.el.color);

    // return wht_note;

    // UINote blk_note = create_blk_note(wht_note.el.x_offset, wht_note.el.y_offset, wht_note.el.width, wht_note.el.height);

    return note;
}
