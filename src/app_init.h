#ifndef APP_INIT_H
#define APP_INIT_H

// vendor
#include "raylib.h"
#include "ui/vendor/nuklear.h"

// shared
#include "midi/midi.h"

typedef struct
{
    ConnectedDevices *connected_devices;
} AppContext;

struct nk_context *app_init(int font_size);
struct nk_vec2 get_monitor_dimensions();

#endif