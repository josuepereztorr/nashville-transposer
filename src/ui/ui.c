#include <stdio.h>
#include "../ui/ui.h"

#define UI_MAX_KEYS 24
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

UIElement create_container(int x_offset, int screen_height, int width, double height_ratio);
UINote create_wht_note_with_multiplier(int x_offset, int y_offset, int width, int height, int num);
UINote create_wht_note(UIElement el);
UINote create_blk_note(UIElement el);
void create_octave();

void ui_create_keyboard()
{
    int x_offset = 20;
    double height_ratio = 0.625;
    UIElement container = create_container(x_offset, UI_SCREEN_HEIGHT, UI_SCREEN_WIDTH, height_ratio);
    UINote wht_note = create_wht_note(container);
    UINote blk_note = create_blk_note(wht_note.el);

    // for (int i = 0; i < UI_MAX_KEYS; i++)
    //{
    // UINote wht_note = create_wht_note_with_multiplier(bg_x_offset, bg_y_offset, bg_width, bg_height, 0);
    //}
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
    const float width_ratio = 1.71;
    const float height_ratio = 1.5;
    const float offset_ratio = 0.75;

    UINote blk_note = {};
    blk_note.el = el;
    blk_note.el.x_offset = blk_note.el.x_offset + (blk_note.el.width * offset_ratio);
    blk_note.el.y_offset = blk_note.el.y_offset;
    blk_note.el.width = blk_note.el.width / width_ratio;
    blk_note.el.height = blk_note.el.height / height_ratio;
    blk_note.el.color = border;

    DrawRectangle(blk_note.el.x_offset,
                  blk_note.el.y_offset,
                  blk_note.el.width,
                  blk_note.el.height,
                  blk_note.el.color);

    return blk_note;
}

// height_ratio from 0.000 to 1.000
UIElement create_container(int x_offset, int screen_height, int screen_width, double height_ratio)
{
    UIElement el;
    el.x_offset = x_offset;
    el.y_offset = screen_height * height_ratio;
    el.width = screen_width - (el.x_offset * 2);
    el.height = (screen_height * (1 - height_ratio)) - (el.x_offset * 2);
    DrawRectangle(el.x_offset, el.y_offset, el.width, el.height, success_midi);
    // printf("x_offset: %d\ny_offset: %d\nwidth: %d\nheight: %d\n", el.x_offset, el.y_offset, el.width, el.height);
    // printf("height_ratio: %f\n\n", height_ratio);

    return el;
}

void create_octave()
{
}

UINote create_wht_note_with_multiplier(int parent_x_offset, int parent_y_offset, int parent_width, int parent_height, int multiplier)
{
    // space between keys
    int key_padding = 2;
    int total_key_padding = UI_MAX_KEYS * key_padding;

    int x_offset = parent_x_offset + multiplier;
    int width = (parent_width - total_key_padding) / UI_MAX_KEYS;

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

    // UINote blk_note = create_blk_note(wht_note.el.x_offset, wht_note.el.y_offset, wht_note.el.width, wht_note.el.height);

    return wht_note;
}
