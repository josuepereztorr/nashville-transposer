#ifndef THEME_H
#define THEME_H

#include "raylib.h"
#include "nuklear_backend/nuklear.h"

// Raylib colors
#define RL_FILL_COLOR (Color){18, 20, 28, 255}

// Nuklear colors
#define NK_FILL_COLOR nk_rgba(18, 20, 28, 255)
#define NK_FOREGROUND_COLOR nk_rgba(27, 29, 40, 255)
#define NK_PRIMARY_TEXT_COLOR nk_rgba(242, 242, 245, 255)
#define NK_SECONDARY_TEXT_COLOR nk_rgba(148, 251, 166, 255)
#define NK_BORDER_COLOR nk_rgba(42, 45, 58, 255)
#define NK_DIVIDER_COLOR nk_rgba(42, 45, 58, 190)
#define NK_WHT_NOTE_COLOR nk_rgba(242, 242, 245, 255)
#define NK_BLK_NOTE_COLOR nk_rgba(42, 45, 58, 255)
#define NK_HEADER_COLOR nk_rgba(139, 147, 165, 255)
#define NK_DEGREE_COLOR nk_rgba(151, 133, 234, 255)
#define NK_TARGET_COLOR nk_rgba(59, 125, 237, 255)

#endif