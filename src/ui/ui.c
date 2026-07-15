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
#define CONTAINER_ROUNDNESS_SM 0.08f
#define CONTAINER_ROUNDNESS_MD 0.06f
#define CONTAINER_ROUNDNESS_LG 0.04f
#define CONTAINER_SEGMENTS 16
#define CONTAINER_LINE_THICK 1.25F

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
UINote notes[MAX_MIDI_NOTES] = {0};

float total_padding = MAX_UI_NOTES * NOTE_PADDING;

const Color success_midi = {74, 222, 128, 255};
const Color failure_midi = {232, 97, 93, 255};

void draw_container(Rectangle rec, float roundness);
void create_wht_notes(int note_index, Rectangle container);
void create_blk_notes(int note_index, Rectangle container);

void ui_create_containers()
{
    // window dimentions
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    // width
    int quarter_width = screen_width / 4;
    int half_width = screen_width / 2;
    int full_width = screen_width - X_OFFSET_MARGIN;

    // height
    int half_height = (screen_height * HEIGHT_RATIO) / 2;
    int full_height = (screen_height * HEIGHT_RATIO) - (Y_OFFSET_MARGIN * 2);

    // left side containers
    Rectangle midi_device_container = {
        .x = X_OFFSET_MARGIN,
        .y = Y_OFFSET_MARGIN,
        .width = quarter_width - X_OFFSET_MARGIN,
        .height = half_height - (Y_OFFSET_MARGIN * 2)};

    draw_container(midi_device_container, CONTAINER_ROUNDNESS_SM);

    Rectangle scale_selection_container = {
        .x = X_OFFSET_MARGIN,
        .y = half_height,
        .width = quarter_width - X_OFFSET_MARGIN,
        .height = half_height - Y_OFFSET_MARGIN};

    draw_container(scale_selection_container, CONTAINER_ROUNDNESS_SM);

    // center container
    Rectangle transposer_container = {
        .x = quarter_width + X_OFFSET_MARGIN,
        .y = Y_OFFSET_MARGIN,
        .width = half_width - X_OFFSET_MARGIN,
        .height = full_height};

    draw_container(transposer_container, CONTAINER_ROUNDNESS_LG);

    // right container
    Rectangle history_container = {
        .x = quarter_width + half_width + X_OFFSET_MARGIN,
        .y = Y_OFFSET_MARGIN,
        .width = quarter_width - (X_OFFSET_MARGIN * 2),
        .height = full_height};

    draw_container(history_container, CONTAINER_ROUNDNESS_MD);

    // bottom container
    Rectangle keyboard_container = {
        .x = X_OFFSET_MARGIN,
        .y = screen_height * HEIGHT_RATIO,
        .width = full_width - X_OFFSET_MARGIN,
        .height = (screen_height * 0.4) - Y_OFFSET_MARGIN};

    // content
    Rectangle content_container = {
        .x = 6849.0f,
        .y = 712.0f,
        .width = 258300.0f,
        .height = 401.0f};

    draw_container(keyboard_container, CONTAINER_ROUNDNESS_MD);

    int wht_note_index = 0;

    create_wht_notes(wht_note_index, keyboard_container);

    // reset counter
    wht_note_index = 0;

    create_blk_notes(wht_note_index, keyboard_container);
}

void draw_container(Rectangle rec, float roundness)
{
    DrawRectangleRounded(rec,
                         roundness,
                         CONTAINER_SEGMENTS,
                         FORGROUND_COLOR);
    DrawRectangleRoundedLinesEx(rec,
                                roundness,
                                CONTAINER_SEGMENTS,
                                CONTAINER_LINE_THICK,
                                BORDER_COLOR);
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

// TODO - SEPARATE MIDI NOTE STRUCT CREATION VS THE UI'S 3 OCTAVE KEYBOARD
void create_wht_notes(int note_index, const Rectangle container)
{
    float content_x_offset = 0.0f;
    float content_y_offset = 0.0f;
    float content_width = 0.0f;
    float content_height = 0.0f;

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
                int wht_note_width = 90;

                // create struct
                UINote note = {
                    .color = WHT_NOTE_COLOR};
                note.rec.x = container.x + (note_index * (wht_note_width + NOTE_PADDING)) + X_OFFSET_MARGIN;
                note.rec.y = container.y + Y_OFFSET_MARGIN;
                note.rec.width = wht_note_width;
                note.rec.height = container.height - (Y_OFFSET_MARGIN * 2);
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

                DrawRectangleRounded(notes[midi_index].rec,
                                     0.1f,
                                     CONTAINER_SEGMENTS,
                                     notes[midi_index].color);

                content_x_offset = note.rec.x;
                content_y_offset = note.rec.y;
                content_width += note.rec.x;
                content_height = container.height - (Y_OFFSET_MARGIN * 2);
            }

            // increase counter
            note_index++;
        }
    }
    printf("X: %lf\nY: %lf\nWidth: %lf\nHeight:%lf\n\n", content_x_offset, content_y_offset, content_width, content_height);
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

        int wht_note_width = 90;

        float wht_note_offset = note_index * (wht_note_width + NOTE_PADDING);
        float blk_note_offset = (wht_note_width * WIDTH_RATIO) / 2.0f;

        UINote note = {
            .color = BLK_NOTE_COLOR};
        note.rec.x = (X_OFFSET_MARGIN + (container.x + wht_note_offset) - blk_note_offset);
        note.rec.y = container.y + Y_OFFSET_MARGIN;
        note.rec.width = wht_note_width * WIDTH_RATIO;
        note.rec.height = (container.height * HEIGHT_RATIO) - (Y_OFFSET_MARGIN * 2);
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

        // DrawRectangleRec(notes[midi_index].rec, notes[midi_index].color);
        DrawRectangleRounded(notes[midi_index].rec,
                             0.03f,
                             CONTAINER_SEGMENTS,
                             notes[midi_index].color);
    }
}