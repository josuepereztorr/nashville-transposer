#include "keyboard.h"

// std lib

// vendor
#include "../vendor/raylib-nuklear.h"

// shared
#include "../theme.h"

// views
#include "layout.h"

void draw_keyboard_container(struct nk_context *ctx)
{
    struct nk_rect margin_rec = {.x = MARGIN, .y = 0, .w = MARGIN * 2.0f, .h = MARGIN};
    draw_container(ctx, margin_rec, NK_FOREGROUND_COLOR, NK_BORDER_COLOR);
};