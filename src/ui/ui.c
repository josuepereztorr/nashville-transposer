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
    UIElement element;
    int is_pressed;
} UINote;

// num off keys
int num_of_keys = 25;

UIElement create_ui_element(int left_margin, double top_margin, int parent_width, int parent_height, Color color);
void create_white_note(int x_offset, int y_offset, int width, int height, Color color, int num);

void ui_create_keyboard()
{

    // Parent - background
    // UIElement ui1 = create_ui_element(20, 0.025, GetScreenWidth() * 0.25, (GetScreenHeight() * 0.625), WHITE);
    // UIElement ui2 = create_ui_element(ui1.width + 20, 0.025, ui1.width * 2, (GetScreenHeight() * 0.625), BLUE);
    // UIElement ui3 = create_ui_element(ui2.width + 20, 0.025, GetScreenWidth() * 0.25, (GetScreenHeight() * 0.625), GREEN);

    int bg_x_offset = 20;
    int bg_y_offset = GetScreenHeight() * 0.625;
    int bg_width = GetScreenWidth() - (bg_x_offset * 2);
    int bg_height = (GetScreenHeight() * 0.375) - 20;
    DrawRectangle(bg_x_offset, bg_y_offset, bg_width, bg_height, foreground);

    for (int i = 0; i < num_of_keys; i++)
    {
        create_white_note(bg_x_offset, bg_y_offset, bg_width, bg_height, primary_text, i);
    }

    // UI black key
}

void create_white_note(int parent_x_offset, int parent_y_offset, int parent_width, int parent_height, Color color, int multiplier)
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

    DrawRectangle(x_offset, parent_y_offset, width, parent_height, color);
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