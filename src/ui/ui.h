#ifndef UI_H
#define UI_H

#include "raylib.h"

// COLORS
// #define FILL_COLOR (Color){18, 20, 28, 255}
#define FORGROUND_COLOR (Color){27, 29, 40, 255}
#define PRIMARY_TEXT_COLOR (Color){242, 242, 245, 255}
#define SECONDARY_TEXT_COLOR (Color){148, 251, 166, 255}
#define BORDER_COLOR (Color){42, 45, 58, 255}
#define DIVIDER_COLOR (Color){42, 45, 58, 190}
#define WHT_NOTE_COLOR (Color){242, 242, 245, 255}
#define BLK_NOTE_COLOR (Color){42, 45, 58, 255}
#define HEADER_COLOR (Color){139, 147, 165, 255}
#define DEGREE_COLOR (Color){151, 133, 234, 255}
#define TARGET_COLOR (Color){59, 125, 237, 255}

void ui_create_containers();
void create_key_selection_dropdown(int *is_active, bool *is_editable);

#endif