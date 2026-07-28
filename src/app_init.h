#ifndef APP_INIT_H
#define APP_INIT_H

// vendor
#include "raylib.h"
#include "ui/vendor/raylib-nuklear.h"

// shared
#include "midi/midi.h"

typedef struct
{
    ConnectedDevices *connected_devices;
} AppContext;

int app_init(void);
struct nk_vec2 get_monitor_dimensions(void);
AppContext *app_get_context(void);
struct nk_context *app_get_ui_context(void);

#endif