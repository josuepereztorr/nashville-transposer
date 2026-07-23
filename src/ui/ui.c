#include <stdio.h>
#include "../ui/ui.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define UI_NAME "Nashville Transposer"

// LOGIC
#define NUM_OF_OCTAVES 3
#define NOTES_IN_OCTAVE 12
#define WHT_NOTES_IN_OCTAVE 7
#define BLK_NOTES_IN_OCTAVE 5
#define TOTAL_NOTES (NUM_OF_OCTAVES * NOTES_IN_OCTAVE)
#define TOTAL_WHT_NOTES (NUM_OF_OCTAVES * WHT_NOTES_IN_OCTAVE)

// UI
#define TOTAL_NOTE_PADDING (TOTAL_WHT_NOTES * WHT_NOTE_TRAIL_PADDING)
#define X_OFFSET_MARGIN 20.0f
#define Y_OFFSET_MARGIN 20.0f
#define BLK_NOTE_WIDTH_RATIO 0.6f
#define BLK_NOTE_ROUNDNESS 0.03f
#define WHT_NOTE_TRAIL_PADDING 2.0f
#define WHT_NOTE_ROUNDNESS 0.1f
#define CONT_UPPER_HEIGHT_RATIO 0.6f
#define CONT_LOWER_HEIGHT_RATIO 0.4f
#define CONT_ROUNDNESS_SM 0.08f
#define CONT_ROUNDNESS_MD 0.06f
#define CONT_ROUNDNESS_LG 0.04f
#define CONT_LINE_THICK 1.25F
#define CONT_SEGMENTS 16

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

UINote notes[NOTES_IN_OCTAVE * NUM_OF_OCTAVES] = {0};

// Colors - change during runtime
const Color success_midi = {74, 222, 128, 255};
const Color failure_midi = {232, 97, 93, 255};
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

void draw_container(Rectangle rec, float roundness);
int get_wht_note_width(Rectangle rec);
UINote create_wht_note(int note_index, const Rectangle container);
void draw_wht_notes(int note_index, Rectangle container);
UINote create_blk_note(int note_index, const Rectangle container);
void draw_blk_notes(int note_index, Rectangle container);
Vector2 get_center(Rectangle container, Vector2 size);
Vector2 center_container(Rectangle container);

void ui_setup()
{
    InitWindow(1, 1, UI_NAME);

    int monitor = GetCurrentMonitor();
    int screen_width = GetMonitorWidth(monitor);
    int screen_height = GetMonitorHeight(monitor);

    SetWindowSize(screen_width, screen_height);
    ToggleFullscreen();
}

void ui_create_containers()
{
    // window dimentions
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    // width
    int quarter_width = screen_width / 4;
    int half_width = screen_width / 2;

    // height
    int half_height_ratio = (screen_height * CONT_UPPER_HEIGHT_RATIO) / 2;
    int height_ratio = screen_height * CONT_UPPER_HEIGHT_RATIO;

    // MIDI DEVICE
    Rectangle midi_device_container = {
        .x = X_OFFSET_MARGIN,
        .y = Y_OFFSET_MARGIN,
        .width = quarter_width - X_OFFSET_MARGIN,
        .height = half_height_ratio - (Y_OFFSET_MARGIN * 2)};

    draw_container(midi_device_container, CONT_ROUNDNESS_SM);

    // SCALE SELECTION
    Rectangle scale_selection_container = {
        .x = X_OFFSET_MARGIN,
        .y = half_height_ratio,
        .width = quarter_width - X_OFFSET_MARGIN,
        .height = half_height_ratio - Y_OFFSET_MARGIN};

    draw_container(scale_selection_container, CONT_ROUNDNESS_SM);

    // TRANSPOSER
    Rectangle transposer_container = {
        .x = quarter_width + X_OFFSET_MARGIN,
        .y = Y_OFFSET_MARGIN,
        .width = half_width - X_OFFSET_MARGIN,
        .height = height_ratio - (Y_OFFSET_MARGIN * 2)};

    draw_container(transposer_container, CONT_ROUNDNESS_LG);

    // HORIZONTAL LINE
    Rectangle transposer_upper_container2 = {
        .x = transposer_container.x + (X_OFFSET_MARGIN * 2),
        .y = transposer_container.y + (Y_OFFSET_MARGIN * 2.1f),
        .width = transposer_container.width - (X_OFFSET_MARGIN * 4),
        .height = (transposer_container.height - (Y_OFFSET_MARGIN * 4)) / 2};

    DrawRectangleRounded(transposer_upper_container2, 0, 0, DIVIDER_COLOR);

    Rectangle transposer_upper_container = {
        .x = transposer_container.x + (X_OFFSET_MARGIN * 2),
        .y = transposer_container.y + (Y_OFFSET_MARGIN * 2),
        .width = transposer_container.width - (X_OFFSET_MARGIN * 4),
        .height = (transposer_container.height - (Y_OFFSET_MARGIN * 4)) / 2};

    DrawRectangleRounded(transposer_upper_container, 0, 0, FORGROUND_COLOR);

    // VERTICAL LINE
    Rectangle transposer_lower_l_container = {
        .x = transposer_upper_container.x,
        .y = transposer_upper_container.height + (Y_OFFSET_MARGIN * 5),
        .width = ((transposer_container.width - (X_OFFSET_MARGIN * 4)) / 2) + (Y_OFFSET_MARGIN * 0.1f),
        .height = (transposer_container.height - (Y_OFFSET_MARGIN * 7)) / 2};

    DrawRectangleRounded(transposer_lower_l_container, 0, 0, DIVIDER_COLOR);

    Rectangle transposer_lower_l_container2 = {
        .x = transposer_upper_container.x,
        .y = transposer_upper_container.height + (Y_OFFSET_MARGIN * 5),
        .width = (transposer_container.width - (X_OFFSET_MARGIN * 4)) / 2,
        .height = (transposer_container.height - (Y_OFFSET_MARGIN * 7)) / 2};

    DrawRectangleRounded(transposer_lower_l_container2, 0, 0, FORGROUND_COLOR);

    Rectangle transposer_lower_r_container = {
        .x = transposer_lower_l_container.x + transposer_lower_l_container.width,
        .y = transposer_lower_l_container.y,
        .width = transposer_lower_l_container.width - (X_OFFSET_MARGIN * 2),
        .height = transposer_lower_l_container.height};

    DrawRectangleRounded(transposer_lower_r_container, 0, 0, FORGROUND_COLOR);

    char *five = "5";
    char *nash = "NASHVILLE NUMBER";
    Vector2 five_v = get_center(transposer_upper_container, MeasureTextEx(GetFontDefault(), five, 160, 5.0f));
    Vector2 nash_v = get_center(transposer_upper_container, MeasureTextEx(GetFontDefault(), nash, 30, 5.0f));
    nash_v.y = nash_v.y - five_v.y;
    DrawTextEx(GetFontDefault(), five, five_v, 160, 5.0f, DEGREE_COLOR);
    DrawTextEx(GetFontDefault(), nash, nash_v, 30, 5.0f, HEADER_COLOR);

    char *current_note = "D4";
    char *current_title = "CURRENT NOTE";
    Vector2 current_note_v = get_center(transposer_lower_l_container, MeasureTextEx(GetFontDefault(), current_note, 160, 5.0f));
    Vector2 current_title_v = get_center(transposer_lower_l_container, MeasureTextEx(GetFontDefault(), current_title, 30, 5.0f));
    current_title_v.y = current_note_v.y - (Y_OFFSET_MARGIN * 2.0f);
    DrawTextEx(GetFontDefault(), current_note, current_note_v, 160, 5.0f, WHITE);
    DrawTextEx(GetFontDefault(), current_title, current_title_v, 30, 5.0f, HEADER_COLOR);

    char *target_note = "A4";
    char *target_title = "TARGET NOTE";
    Vector2 target_note_v = get_center(transposer_lower_r_container, MeasureTextEx(GetFontDefault(), target_note, 160, 5.0f));
    Vector2 target_title_v = get_center(transposer_lower_r_container, MeasureTextEx(GetFontDefault(), target_title, 30, 5.0f));
    target_title_v.y = target_note_v.y - (Y_OFFSET_MARGIN * 2.0f);
    DrawTextEx(GetFontDefault(), target_note, target_note_v, 160, 5.0f, TARGET_COLOR);
    DrawTextEx(GetFontDefault(), target_title, target_title_v, 30, 5.0f, HEADER_COLOR);

    // HISTORY
    Rectangle history_container = {
        .x = quarter_width + half_width + X_OFFSET_MARGIN,
        .y = Y_OFFSET_MARGIN,
        .width = quarter_width - (X_OFFSET_MARGIN * 2),
        .height = height_ratio - (Y_OFFSET_MARGIN * 2)};

    draw_container(history_container, CONT_ROUNDNESS_MD);

    // KEYBOARD
    Rectangle keyboard_container = {
        .x = X_OFFSET_MARGIN,
        .y = screen_height * CONT_UPPER_HEIGHT_RATIO,
        .width = screen_width - (X_OFFSET_MARGIN * 2),
        .height = (screen_height * 0.4) - Y_OFFSET_MARGIN};

    draw_container(keyboard_container, CONT_ROUNDNESS_MD);

    // draw notes
    int wht_note_index = 0;

    draw_wht_notes(wht_note_index, keyboard_container);

    // reset counter
    wht_note_index = 0;

    draw_blk_notes(wht_note_index, keyboard_container);
}

void draw_container(Rectangle rec, float roundness)
{
    DrawRectangleRounded(rec,
                         roundness,
                         CONT_SEGMENTS,
                         FORGROUND_COLOR);
    DrawRectangleRoundedLinesEx(rec,
                                roundness,
                                CONT_SEGMENTS,
                                CONT_LINE_THICK,
                                BORDER_COLOR);
}

int get_wht_note_width(Rectangle rec)
{
    float content_width = rec.width - TOTAL_NOTE_PADDING - X_OFFSET_MARGIN;
    int wht_note_width = (int)(content_width / TOTAL_WHT_NOTES);
    return wht_note_width;
}

UINote create_wht_note(int note_index, const Rectangle container)
{
    int wht_note_width = get_wht_note_width(container);

    // create struct
    UINote note = {
        .color = WHT_NOTE_COLOR};
    note.rec.x = container.x + (note_index * (wht_note_width + WHT_NOTE_TRAIL_PADDING)) + X_OFFSET_MARGIN;
    note.rec.y = container.y + Y_OFFSET_MARGIN;
    note.rec.width = wht_note_width;
    note.rec.height = container.height - (Y_OFFSET_MARGIN * 2);
    note.is_pressed = false;
    note.id = 0;

    return note;
}

void draw_wht_notes(int note_index, const Rectangle container)
{
    for (int midi_index = 0; midi_index < TOTAL_NOTES; midi_index++)
    {
        // calculate the chromatic scale degree based on the midi_index value
        int degree = midi_index % 12;

        // checks if the current midi note is a black note based on the is_blk_note array.
        if (!is_blk_note[degree])
        {
            UINote note = create_wht_note(note_index, container);
            note.id = midi_index;

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
                                 WHT_NOTE_ROUNDNESS,
                                 CONT_SEGMENTS,
                                 notes[midi_index].color);

            note_index++;
        }
    }
}

UINote create_blk_note(int note_index, const Rectangle container)
{
    int wht_note_width = get_wht_note_width(container);

    float wht_note_offset = note_index * (wht_note_width + WHT_NOTE_TRAIL_PADDING);
    float blk_note_offset = (wht_note_width * BLK_NOTE_WIDTH_RATIO) / 2.0f;

    UINote note = {
        .color = BLK_NOTE_COLOR};
    note.rec.x = (X_OFFSET_MARGIN + (container.x + wht_note_offset) - blk_note_offset);
    note.rec.y = container.y + Y_OFFSET_MARGIN;
    note.rec.width = wht_note_width * BLK_NOTE_WIDTH_RATIO;
    note.rec.height = (container.height * CONT_UPPER_HEIGHT_RATIO) - (Y_OFFSET_MARGIN * 2);
    note.is_pressed = false;
    note.id = 0;

    return note;
}

void draw_blk_notes(int note_index, const Rectangle container)
{
    for (int midi_index = 0; midi_index < TOTAL_NOTES; midi_index++)
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

        UINote note = create_blk_note(note_index, container);
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
                             CONT_SEGMENTS,
                             notes[midi_index].color);
    }
}

Vector2 get_center(Rectangle container, Vector2 size)
{
    return (Vector2){
        .x = (container.x + (container.width / 2.0f)) - (size.x / 2.0f),
        .y = (container.y + (container.height / 2.0f)) - (size.y / 2.0f)};
}

Vector2 center_container(Rectangle container)
{
    return (Vector2){
        .x = container.width * 0.20f,
        .y = container.height * 0.20f};
}

void create_key_selection_dropdown(int *is_active, bool *is_editable)
{
    const char *scales_str = "C Major;C# Major;D Major;D# Major;E Major;F Major;F# Major;G Major;G# Major;A Major;A# Major;B Major";

    Rectangle rec = {0};
    rec.height = 50;
    rec.width = 1000;
    rec.x = 20;
    rec.y = 20;

    if (GuiDropdownBox(rec, scales_str, is_active, *is_editable))
    {
        *is_editable = !*is_editable;
    }
}