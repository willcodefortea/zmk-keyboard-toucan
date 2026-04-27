#include <zephyr/kernel.h>
#include "modifiers.h"
#include "../assets/custom_fonts.h"

#define MOD_BOX_W   20
#define MOD_BOX_H   14
#define MOD_BOX_GAP 8
#define MOD_ROW_Y   110
#define MOD_ROW_X   20 /* (144 - (4*20 + 3*8)) / 2 */

#define MOD_CTL_MASK 0x11 /* MOD_LCTL | MOD_RCTL */
#define MOD_SFT_MASK 0x22 /* MOD_LSFT | MOD_RSFT */
#define MOD_ALT_MASK 0x44 /* MOD_LALT | MOD_RALT */
#define MOD_GUI_MASK 0x88 /* MOD_LGUI | MOD_RGUI */

static const char *mod_labels[] = {"C", "S", "A", "G"};
static const uint8_t mod_masks[] = {MOD_CTL_MASK, MOD_SFT_MASK, MOD_ALT_MASK, MOD_GUI_MASK};

static void draw_box_outline(lv_obj_t *canvas, int x, int y, int w, int h) {
    lv_draw_rect_dsc_t rect_dsc;
    init_rect_dsc(&rect_dsc, LVGL_FOREGROUND);

    lv_canvas_draw_rect(canvas, x, y, w, 1, &rect_dsc);
    lv_canvas_draw_rect(canvas, x, y + h - 1, w, 1, &rect_dsc);
    lv_canvas_draw_rect(canvas, x, y, 1, h, &rect_dsc);
    lv_canvas_draw_rect(canvas, x + w - 1, y, 1, h, &rect_dsc);
}

void draw_modifiers_status(lv_obj_t *canvas, const struct status_state *state) {
    uint8_t mods = state->modifiers;

    for (int i = 0; i < 4; i++) {
        int box_x = MOD_ROW_X + i * (MOD_BOX_W + MOD_BOX_GAP);
        bool active = (mods & mod_masks[i]) != 0;

        if (active) {
            lv_draw_rect_dsc_t rect_dsc;
            init_rect_dsc(&rect_dsc, LVGL_FOREGROUND);
            lv_canvas_draw_rect(canvas, box_x, MOD_ROW_Y, MOD_BOX_W, MOD_BOX_H, &rect_dsc);

            lv_draw_label_dsc_t label_dsc;
            init_label_dsc(&label_dsc, LVGL_BACKGROUND, &quinquefive_8, LV_TEXT_ALIGN_CENTER);
            lv_canvas_draw_text(canvas, box_x, MOD_ROW_Y + 3, MOD_BOX_W, &label_dsc, mod_labels[i]);
        } else {
            draw_box_outline(canvas, box_x, MOD_ROW_Y, MOD_BOX_W, MOD_BOX_H);

            lv_draw_label_dsc_t label_dsc;
            init_label_dsc(&label_dsc, LVGL_FOREGROUND, &quinquefive_8, LV_TEXT_ALIGN_CENTER);
            lv_canvas_draw_text(canvas, box_x, MOD_ROW_Y + 3, MOD_BOX_W, &label_dsc, mod_labels[i]);
        }
    }
}
