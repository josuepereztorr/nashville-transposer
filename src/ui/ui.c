#include <stdio.h>
#include "../ui/ui.h"

#define UI_MAX_KEYS 25

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
} UINote;

// num off keys
int num_of_keys = 25;

UIElement create_ui_element(int left_margin, double top_margin, int parent_width, int parent_height, Color color);
UINote create_wht_note_with_multiplier(int x_offset, int y_offset, int width, int height, int num);
UINote create_wht_note(int parent_x_offset, int parent_y_offset, int parent_width, int parent_height);
UINote create_blk_note(int parent_x_offset, int parent_y_offset, int parent_width, int parent_height);
void create_octave();

void ui_create_keyboard()
{

    int bg_x_offset = 20;
    int bg_y_offset = GetScreenHeight() * 0.625;
    int bg_width = GetScreenWidth() - (bg_x_offset * 2);
    int bg_height = (GetScreenHeight() * 0.375) - 20;
    DrawRectangle(bg_x_offset, bg_y_offset, bg_width, bg_height, failure_midi);

    // for (int i = 0; i < num_of_keys; i++)
    //{
    // UINote wht_note = create_wht_note_with_multiplier(bg_x_offset, bg_y_offset, bg_width, bg_height, 0);
    //}

    UINote wht_note = create_wht_note(bg_x_offset, bg_y_offset, bg_width, bg_height);
    UINote blk_note = create_blk_note(wht_note.el.x_offset, wht_note.el.y_offset, wht_note.el.width, wht_note.el.height);
}

void create_octave()
{
}

UINote create_wht_note_with_multiplier(int parent_x_offset, int parent_y_offset, int parent_width, int parent_height, int multiplier)
{
    // space between keys
    int key_padding = 2;
    int total_key_padding = num_of_keys * key_padding;

    int x_offset = parent_x_offset + multiplier;
    int width = (parent_width - total_key_padding) / num_of_keys;

    if (multiplier > 0)
    {
        multiplier = (multiplier * width) + (multiplier * key_padding);
    }

    x_offset = parent_x_offset + multiplier;

    UINote wht_note = {};
    wht_note.el.x_offset = x_offset;
    wht_note.el.y_offset = parent_y_offset;
    wht_note.el.width = width;
    wht_note.el.height = parent_height;
    wht_note.el.color = primary_text;

    DrawRectangle(wht_note.el.x_offset,
                  wht_note.el.y_offset,
                  wht_note.el.width,
                  wht_note.el.height,
                  wht_note.el.color);

    // return wht_note;

    UINote blk_note = create_blk_note(wht_note.el.x_offset, wht_note.el.y_offset, wht_note.el.width, wht_note.el.height);

    return wht_note;
}

UINote create_wht_note(int parent_x_offset, int parent_y_offset, int parent_width, int parent_height)
{
    UINote wht_note = {};
    wht_note.el.x_offset = parent_x_offset;
    wht_note.el.y_offset = parent_y_offset;
    wht_note.el.width = parent_width / num_of_keys;
    wht_note.el.height = parent_height;
    wht_note.el.color = primary_text;

    DrawRectangle(wht_note.el.x_offset,
                  wht_note.el.y_offset,
                  wht_note.el.width,
                  wht_note.el.height,
                  wht_note.el.color);

    UINote blk_note = create_blk_note(wht_note.el.x_offset, wht_note.el.y_offset, wht_note.el.width, wht_note.el.height);

    return wht_note;
}

UINote create_blk_note(int parent_x_offset, int parent_y_offset, int parent_width, int parent_height)
{
    // white to black note ratios
    const float width_ratio = 1.71;
    const float height_ratio = 1.5;
    const float offset_ratio = 0.75;

    UINote blk_note = {};
    blk_note.el.x_offset = parent_x_offset + (parent_width * offset_ratio);
    blk_note.el.y_offset = parent_y_offset;
    blk_note.el.width = parent_width / width_ratio;
    blk_note.el.height = parent_height / height_ratio;
    blk_note.el.color = border;

    DrawRectangle(blk_note.el.x_offset,
                  blk_note.el.y_offset,
                  blk_note.el.width,
                  blk_note.el.height,
                  blk_note.el.color);

    return blk_note;
}

// top_margin is a value from 0.00 to 1.00
UIElement create_ui_element(int left_margin, double top_margin, int parent_width, int parent_height, Color color)
{
    // Parent - background
    UIElement el;
    el.x_offset = left_margin;
    el.y_offset = parent_height * top_margin;
    el.width = parent_width - (el.x_offset * 2);
    el.height = (parent_height * (1 - top_margin)) - left_margin;
    DrawRectangle(el.x_offset, el.y_offset, el.width, el.height, color);

    return el;
}