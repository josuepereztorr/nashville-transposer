#ifndef APP_INIT_H
#define APP_INIT_H

// vendor
#include "raylib.h"
#include "ui/vendor/raylib-nuklear.h"

// shared
#include "midi/midi.h"

typedef struct
{
    MidiDevice device;
    PmEvent event;
    int current_key_selected;
    int target_key_selected;
} AppContext;

int app_init();
void app_terminate();
struct nk_vec2 get_monitor_dimensions(void);
AppContext *app_get_context(void);
struct nk_context *app_get_ui_context(void);
struct nk_user_font *app_get_title_font(void);
struct nk_user_font *app_get_display_font(void);

#endif