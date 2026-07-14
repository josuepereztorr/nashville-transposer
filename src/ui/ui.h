#ifndef UI_H
#define UI_H

#include "raylib.h"

// COLORS
#define FILL_COLOR (Color){18, 20, 28, 255}
#define FORGROUND_COLOR (Color){27, 29, 40, 255}
#define PRIMARY_TEXT_COLOR (Color){242, 242, 245, 255}
#define SECONDARY_TEXT_COLOR (Color){148, 251, 166, 255}
#define BORDER_COLOR (Color){42, 45, 58, 255}
#define WHT_NOTE_COLOR (Color){242, 242, 245, 255}
#define BLK_NOTE_COLOR (Color){42, 45, 58, 255}

extern const Color success_midi;
extern const Color failure_midi;

// void ui_crate_midi_device_container();
void ui_create_keyboard();
// void ui_create_drowndown();

#endif