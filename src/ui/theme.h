/*
 * ============================================================
 * File    : theme.h
 * Project : Nashville Transposer
 * ============================================================
 * Author   : Josue Perez Torres
 * Created  : 07-28-2026
 * Modified : 07-28-2026
 * Version  : 1.0.0
 * ============================================================
 * Description:
 *     Centralized color palette and layout constants shared
 *     across Raylib and Nuklear UI rendering.
 * ============================================================
 * Dependencies:
 *     raylib.h (vendor) - windowing/rendering.
 *     raylib-nuklear.h (vendor) - Nuklear + Raylib integration.
 * ============================================================
 */

#ifndef THEME_H
#define THEME_H

// ------------------------------------------------------------
// INCLUDES
// ------------------------------------------------------------

// vendor
#include "raylib.h"
#include "vendor/raylib-nuklear.h"

// ------------------------------------------------------------
// CONSTANT & MACROS
// ------------------------------------------------------------

// Raylib colors
#define RL_FILL_COLOR (Color){18, 20, 28, 255}

// Nuklear colors
#define NK_TRANSPARENT nk_rgba(0, 0, 0, 0)
#define NK_FOREGROUND_COLOR nk_rgba(27, 29, 40, 255)

// text
#define NK_PRIMARY_TEXT_COLOR nk_rgba(242, 242, 245, 255)
#define NK_BORDER_COLOR nk_rgba(42, 45, 58, 255)

// keyboard colors
#define NK_WHT_NOTE_COLOR nk_rgba(242, 242, 245, 255)
#define NK_BLK_NOTE_COLOR nk_rgba(42, 45, 58, 255)
#define NK_WHT_NOTE_PRESSED_COLOR nk_rgba(59, 130, 246, 255)
#define NK_BLK_NOTE_PRESSED_COLOR nk_rgba(30, 58, 138, 255)

// transposer display colors
#define NK_DEGREE_COLOR nk_rgba(151, 133, 234, 255)
#define NK_TARGET_COLOR nk_rgba(59, 125, 237, 255)

// shared
#define MARGIN 20.0f
#define ROUNDNESS 10.0f
#define LINE_THICK 1.25f

#endif