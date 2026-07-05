#include <stdio.h>
#include "../ui/ui.h"

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
} UIElement;

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

    create_white_note(bg_x_offset, bg_y_offset, bg_width, bg_height, primary_text, 0);
    create_white_note(bg_x_offset, bg_y_offset, bg_width, bg_height, secondary_text, 1);
    create_white_note(bg_x_offset, bg_y_offset, bg_width, bg_height, primary_text, 2);
    // create_white_note(bg_x_offset, bg_y_offset, bg_width, bg_height, secondary_text, 3);
    // create_white_note(bg_x_offset, bg_y_offset, bg_width, bg_height, primary_text, 4);
    // create_white_note(bg_x_offset, bg_y_offset, bg_width, bg_height, secondary_text, 5);
    // create_white_note(bg_x_offset, bg_y_offset, bg_width, bg_height, primary_text, 6);

    // UI black key
}

void create_white_note(int x_offset, int y_offset, int width, int height, Color color, int multiplier)
{
    int white_key_width = (width + (num_of_keys * 5)) / num_of_keys;
    int white_key_height = height;

    if (multiplier > 0)
    {
        // x_offset = (x_offset);
        multiplier = (white_key_width * multiplier) + 5;
    }
    x_offset += multiplier;

    printf("x_offset: %i\n", x_offset);
    printf("multiplier: %i\n", multiplier);
    printf("white_key_width: %i\n\n", white_key_width);

    DrawRectangle(x_offset, y_offset, white_key_width, white_key_height, color);
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