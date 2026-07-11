#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations

// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_NONE
};

// Native global variables

extern int32_t get_var_vcu_rolling_counter();
extern void set_var_vcu_rolling_counter(int32_t value);
extern double get_var_bms_pack_inst_voltage();
extern void set_var_bms_pack_inst_voltage(double value);
extern double get_var_wheel_fl_speed();
extern void set_var_wheel_fl_speed(double value);
extern double get_var_bms_pack_current();
extern void set_var_bms_pack_current(double value);
extern double get_var_pdm_input_10_voltage();
extern void set_var_pdm_input_10_voltage(double value);
extern double get_var_wheel_fr_speed();
extern void set_var_wheel_fr_speed(double value);
extern double get_var_wheel_rl_speed();
extern void set_var_wheel_rl_speed(double value);
extern double get_var_wheel_rr_speed();
extern void set_var_wheel_rr_speed(double value);
extern const char *get_var_vcu_ctrl_state();
extern void set_var_vcu_ctrl_state(const char *value);
extern const char *get_var_pm100_vsm_state();
extern void set_var_pm100_vsm_state(const char *value);
extern double get_var_vcu_sagl();
extern void set_var_vcu_sagl(double value);
extern double get_var_vcu_apps();
extern void set_var_vcu_apps(double value);
extern double get_var_vcu_bps();
extern void set_var_vcu_bps(double value);
extern double get_var_pm100_module_a();
extern void set_var_pm100_module_a(double value);
extern double get_var_pm100_module_b();
extern void set_var_pm100_module_b(double value);
extern double get_var_pm100_module_c();
extern void set_var_pm100_module_c(double value);
extern double get_var_pm100_gate_driver_board();
extern void set_var_pm100_gate_driver_board(double value);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/