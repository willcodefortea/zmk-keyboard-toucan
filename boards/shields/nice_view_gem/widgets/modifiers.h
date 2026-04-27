#pragma once

#include <lvgl.h>
#include "util.h"

struct modifiers_status_state {
    uint8_t modifiers;
};

void draw_modifiers_status(lv_obj_t *canvas, const struct status_state *state);
