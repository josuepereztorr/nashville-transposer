#ifndef KEYBOARD_H
#define KEYBOARD_H

// vendors
#include "../vendor/raylib-nuklear.h"

// shared
#include "../../app.h"

void draw_keyboard_container(struct nk_context *ui_ctx, AppContext *app_ctx);

#endif