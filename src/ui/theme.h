#ifndef THEME_H
#define THEME_H

// vendor
#include "raylib.h"
#include "vendor/raylib-nuklear.h"

// Raylib colors
#define RL_FILL_COLOR (Color){18, 20, 28, 255}

// Nuklear colors
#define NK_TRANSPARENT nk_rgba(0, 0, 0, 0)
#define NK_FILL_COLOR nk_rgba(18, 20, 28, 255)
#define NK_FOREGROUND_COLOR nk_rgba(27, 29, 40, 255)

#define NK_PRIMARY_TEXT_COLOR nk_rgba(242, 242, 245, 255)

#define NK_BORDER_COLOR nk_rgba(42, 45, 58, 255)
#define NK_DIVIDER_COLOR nk_rgba(42, 45, 58, 190)

#define NK_WHT_NOTE_COLOR nk_rgba(242, 242, 245, 255)
#define NK_BLK_NOTE_COLOR nk_rgba(42, 45, 58, 255)
#define NK_WHT_NOTE_PRESSED_COLOR nk_rgba(59, 130, 246, 255)
#define NK_BLK_NOTE_PRESSED_COLOR nk_rgba(30, 58, 138, 255)

#define NK_HEADER_COLOR nk_rgba(139, 147, 165, 255)
#define NK_DEGREE_COLOR nk_rgba(151, 133, 234, 255)
#define NK_TARGET_COLOR nk_rgba(59, 125, 237, 255)

// Shared
#define MARGIN 20.0f
#define ROUNDNESS 10.0f
#define LINE_THICK 1.25f

#endif