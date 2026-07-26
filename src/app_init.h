#ifndef APP_INIT_H
#define APP_INIT_H

// vendor
#include "raylib.h"
#include "ui/vendor/nuklear.h"

struct nk_context *app_init(int font_size);
Vector2 get_monitor_dimensions();

#endif