#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;

static const char *screen_names[] = { "Main" };
static const char *object_names[] = { "main", "pdm_10", "vcu_state", "inv_state", "obj0", "wheel_fl", "wheel_fl_1", "pdm_11", "apps", "bps", "pdm_12", "obj1" };

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

static void event_handler_cb_main_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            assignIntegerProperty(flowState, 5, 3, value, "Failed to assign Value in Arc widget");
        }
    }
}

//
// Screens
//

void create_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x003ca2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_background);
            lv_img_set_pivot(obj, 0, 0);
            lv_img_set_zoom(obj, 168);
        }
        {
            // pdm_10
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pdm_10 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // vcu_state
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.vcu_state = obj;
            lv_obj_set_pos(obj, -48, -27);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // inv_state
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inv_state = obj;
            lv_obj_set_pos(obj, -48, -11);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 381, 426);
            lv_obj_set_size(obj, 38, 36);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj0, LV_EVENT_ALL, flowState);
            lv_obj_set_style_pad_top(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_left(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 2, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // wheel_fl
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wheel_fl = obj;
            lv_obj_set_pos(obj, -403, -220);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // wheel_fl_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wheel_fl_1 = obj;
            lv_obj_set_pos(obj, 397, 238);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "mph");
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 765, 444);
            lv_obj_set_size(obj, 26, 25);
            lv_led_set_brightness(obj, 255);
        }
        {
            // pdm_11
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pdm_11 = obj;
            lv_obj_set_pos(obj, 0, 16);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // apps
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.apps = obj;
            lv_obj_set_pos(obj, 422, 475);
            lv_obj_set_size(obj, 50, 10);
            lv_obj_set_style_transform_angle(obj, 2700, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x00ff00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // bps
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.bps = obj;
            lv_obj_set_pos(obj, 364, 475);
            lv_obj_set_size(obj, 50, 10);
            lv_obj_set_style_transform_angle(obj, 2700, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // pdm_12
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pdm_12 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.pdm_10);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.pdm_10;
            lv_label_set_text(objects.pdm_10, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 3, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.vcu_state);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.vcu_state;
            lv_label_set_text(objects.vcu_state, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 4, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.inv_state);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.inv_state;
            lv_label_set_text(objects.inv_state, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 5, 3, "Failed to evaluate Value in Arc widget");
        int32_t cur_val = lv_arc_get_value(objects.obj0);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj0;
            lv_arc_set_value(objects.obj0, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 6, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wheel_fl);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wheel_fl;
            lv_label_set_text(objects.wheel_fl, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        uint32_t new_val = evalUnsignedIntegerProperty(flowState, 8, 3, "Failed to evaluate Color in Led widget");
        new_val = lv_color_to32(lv_color_hex(new_val));
        uint32_t cur_val = lv_color_to32(((lv_led_t *)objects.obj1)->color);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj1;
            lv_led_set_color(objects.obj1, lv_color_hex(new_val));
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 9, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.pdm_11);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.pdm_11;
            lv_label_set_text(objects.pdm_11, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 10, 3, "Failed to evaluate Value in Bar widget");
        int32_t cur_val = lv_bar_get_value(objects.apps);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.apps;
            lv_bar_set_value(objects.apps, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 11, 3, "Failed to evaluate Value in Bar widget");
        int32_t cur_val = lv_bar_get_value(objects.bps);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.bps;
            lv_bar_set_value(objects.bps, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 12, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.pdm_12);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.pdm_12;
            lv_label_set_text(objects.pdm_12, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};
void tick_screen(int screen_index) {
    if (screen_index >= 0 && screen_index < 1) {
        tick_screen_funcs[screen_index]();
    }
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen(screenId - 1);
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
//
//

void create_screens() {
    
    eez_flow_init_fonts(fonts, sizeof(fonts) / sizeof(ext_font_desc_t));

// Set default LVGL theme
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    // Initialize screens
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    
    // Create screens
    create_screen_main();
}