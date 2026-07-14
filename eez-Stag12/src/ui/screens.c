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
static const char *object_names[] = { "main", "lvbox_pwr", "vcu_state", "inv_state", "obj0", "wheel_fl", "wheel_fl_1", "pdm_11", "apps", "bps", "inverter_temp", "inverter_temp_1", "inverter_temp_2", "inverter_temp_3", "inverter_temp_4", "inverter_temp_5", "inverter_temp_6", "inverter_temp_8", "inverter_temp_9", "inverter_temp_10", "pdm_12", "pdm_13", "wheel_fl_2", "wheel_fl_3", "wheel_fl_4", "obj1", "inverter_temp_11", "obj2", "inverter_temp_12", "obj3", "inverter_temp_13", "obj4", "inverter_temp_14", "obj5", "obj6" };

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
            assignIntegerProperty(flowState, 4, 3, value, "Failed to assign Value in Arc widget");
        }
    }
}

static void event_handler_cb_main_obj1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 25, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_main_obj2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 27, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_main_obj3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 29, 3, value, "Failed to assign Checked state");
        }
    }
}

static void event_handler_cb_main_obj4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 31, 3, value, "Failed to assign Checked state");
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
    lv_obj_set_style_blend_mode(obj, LV_BLEND_MODE_NORMAL, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // lvbox_pwr
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lvbox_pwr = obj;
            lv_obj_set_pos(obj, -22, 17);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // vcu_state
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.vcu_state = obj;
            lv_obj_set_pos(obj, 0, -16);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // inv_state
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inv_state = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_align(obj, LV_ALIGN_BOTTOM_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 383, 423);
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
            // pdm_11
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pdm_11 = obj;
            lv_obj_set_pos(obj, -22, 54);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // apps
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.apps = obj;
            lv_obj_set_pos(obj, 421, 424);
            lv_obj_set_size(obj, 10, 50);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0x00ff00), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // bps
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.bps = obj;
            lv_obj_set_pos(obj, 370, 423);
            lv_obj_set_size(obj, 10, 50);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // inverter_temp
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp = obj;
            lv_obj_set_pos(obj, 152, 59);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // inverter_temp_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_1 = obj;
            lv_obj_set_pos(obj, 259, 60);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // inverter_temp_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_2 = obj;
            lv_obj_set_pos(obj, 165, 24);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Max");
        }
        {
            // inverter_temp_3
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_3 = obj;
            lv_obj_set_pos(obj, 270, 27);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Avg");
        }
        {
            // inverter_temp_4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_4 = obj;
            lv_obj_set_pos(obj, 17, 60);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Inverter");
        }
        {
            // inverter_temp_5
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_5 = obj;
            lv_obj_set_pos(obj, 17, 106);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Motor");
        }
        {
            // inverter_temp_6
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_6 = obj;
            lv_obj_set_pos(obj, 17, 150);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Battery");
        }
        {
            // inverter_temp_8
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_8 = obj;
            lv_obj_set_pos(obj, 198, 106);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // inverter_temp_9
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_9 = obj;
            lv_obj_set_pos(obj, 153, 150);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // inverter_temp_10
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_10 = obj;
            lv_obj_set_pos(obj, 258, 150);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // pdm_12
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pdm_12 = obj;
            lv_obj_set_pos(obj, 244, -5);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // pdm_13
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.pdm_13 = obj;
            lv_obj_set_pos(obj, 244, 54);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_30, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // wheel_fl_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wheel_fl_2 = obj;
            lv_obj_set_pos(obj, 244, -32);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Current Mode");
        }
        {
            // wheel_fl_3
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wheel_fl_3 = obj;
            lv_obj_set_pos(obj, 244, 27);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // wheel_fl_4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wheel_fl_4 = obj;
            lv_obj_set_pos(obj, -3, 115);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 493, 52);
            lv_obj_set_size(obj, 34, 17);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj1, LV_EVENT_ALL, flowState);
        }
        {
            // inverter_temp_11
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_11 = obj;
            lv_obj_set_pos(obj, 383, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Inverter");
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 493, 74);
            lv_obj_set_size(obj, 34, 17);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj2, LV_EVENT_ALL, flowState);
        }
        {
            // inverter_temp_12
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_12 = obj;
            lv_obj_set_pos(obj, 383, 71);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Brakelight");
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 494, 96);
            lv_obj_set_size(obj, 34, 17);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj3, LV_EVENT_ALL, flowState);
        }
        {
            // inverter_temp_13
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_13 = obj;
            lv_obj_set_pos(obj, 383, 93);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Pumps");
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 494, 118);
            lv_obj_set_size(obj, 34, 17);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj4, LV_EVENT_ALL, flowState);
        }
        {
            // inverter_temp_14
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.inverter_temp_14 = obj;
            lv_obj_set_pos(obj, 383, 115);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_align(obj, LV_ALIGN_TOP_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text_static(obj, "Fans");
        }
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            objects.obj5 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_stag);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_CHECKED);
            lv_obj_set_style_img_recolor_opa(obj, 255, LV_PART_MAIN | LV_STATE_CHECKED);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 17, 412);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    {
        const char *new_val = evalTextProperty(flowState, 0, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.lvbox_pwr);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.lvbox_pwr;
            lv_label_set_text(objects.lvbox_pwr, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 2, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.vcu_state);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.vcu_state;
            lv_label_set_text(objects.vcu_state, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 3, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.inv_state);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.inv_state;
            lv_label_set_text(objects.inv_state, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 4, 3, "Failed to evaluate Value in Arc widget");
        int32_t cur_val = lv_arc_get_value(objects.obj0);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj0;
            lv_arc_set_value(objects.obj0, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 5, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wheel_fl);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wheel_fl;
            lv_label_set_text(objects.wheel_fl, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 7, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.pdm_11);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.pdm_11;
            lv_label_set_text(objects.pdm_11, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 8, 3, "Failed to evaluate Value in Bar widget");
        int32_t cur_val = lv_bar_get_value(objects.apps);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.apps;
            lv_bar_set_value(objects.apps, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 9, 3, "Failed to evaluate Value in Bar widget");
        int32_t cur_val = lv_bar_get_value(objects.bps);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.bps;
            lv_bar_set_value(objects.bps, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 10, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.inverter_temp);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.inverter_temp;
            lv_label_set_text(objects.inverter_temp, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 11, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.inverter_temp_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.inverter_temp_1;
            lv_label_set_text(objects.inverter_temp_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 17, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.inverter_temp_8);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.inverter_temp_8;
            lv_label_set_text(objects.inverter_temp_8, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 18, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.inverter_temp_9);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.inverter_temp_9;
            lv_label_set_text(objects.inverter_temp_9, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 19, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.inverter_temp_10);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.inverter_temp_10;
            lv_label_set_text(objects.inverter_temp_10, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 20, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.pdm_12);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.pdm_12;
            lv_label_set_text(objects.pdm_12, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 21, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.pdm_13);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.pdm_13;
            lv_label_set_text(objects.pdm_13, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 23, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wheel_fl_3);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wheel_fl_3;
            lv_label_set_text(objects.wheel_fl_3, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 24, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.wheel_fl_4);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.wheel_fl_4;
            lv_label_set_text(objects.wheel_fl_4, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 25, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj1, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj1;
            if (new_val) {
                lv_obj_add_state(objects.obj1, LV_STATE_CHECKED);
            } else {
                lv_obj_clear_state(objects.obj1, LV_STATE_CHECKED);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 27, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj2, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj2;
            if (new_val) {
                lv_obj_add_state(objects.obj2, LV_STATE_CHECKED);
            } else {
                lv_obj_clear_state(objects.obj2, LV_STATE_CHECKED);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 29, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj3, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj3;
            if (new_val) {
                lv_obj_add_state(objects.obj3, LV_STATE_CHECKED);
            } else {
                lv_obj_clear_state(objects.obj3, LV_STATE_CHECKED);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = evalBooleanProperty(flowState, 31, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj4, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj4;
            if (new_val) {
                lv_obj_add_state(objects.obj4, LV_STATE_CHECKED);
            } else {
                lv_obj_clear_state(objects.obj4, LV_STATE_CHECKED);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = evalTextProperty(flowState, 34, 3, "Failed to evaluate Text in Label widget");
        const char *cur_val = lv_label_get_text(objects.obj6);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj6;
            lv_label_set_text(objects.obj6, new_val);
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