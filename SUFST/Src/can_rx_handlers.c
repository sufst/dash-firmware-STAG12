/* Auto generated: Do not edit directly, instead add signals in Codegen/signal_mapping.yaml or update Codegen/can_rx_handlers.c.j2 */

#include <stdint.h>
#include <stdbool.h>

/* Include your generated cantools headers */
#include "can_t.h"
#include "can_s.h"

/* ==================================================================== */
/* Global Backing Variables for EEZ Studio                              */
/* ==================================================================== */


static int32_t g_vcu_rolling_counter = 0;
static int32_t g_vcu_ctrl_state = 0;
static double g_bms_pack_inst_voltage = 0.0;
static double g_bms_pack_current = 0.0;
static double g_pdm_input_10_voltage = 0.0;
static int32_t g_pm100_vsm_state = 0;

static double g_wheel_fl_speed = 0.0;
static double g_wheel_fr_speed = 0.0;
static double g_wheel_rl_speed = 0.0;
static double g_wheel_rr_speed = 0.0;


/* ==================================================================== */
/* EEZ Studio Native Variable Interface (Getters & Setters)             */
/* ==================================================================== */


// Getter for vcu_rolling_counter
int32_t get_var_vcu_rolling_counter(void)
{
    return g_vcu_rolling_counter;
}

// Setter for vcu_rolling_counter (No-op for read-only telemetry)
void set_var_vcu_rolling_counter(int32_t value)
{
    (void)value;
}
// Getter for vcu_ctrl_state
const char * get_var_vcu_ctrl_state(void)
{
    switch (g_vcu_ctrl_state)
    {
    case 0: return "TS Button Wait";
    case 1: return "Wait Neg AIR";
    case 2: return "Precharge Wait";
    case 3: return "R2D Wait";
    case 4: return "TS On";
    case 5: return "R2D Off";
    case 6: return "R2D Off Wait";
    case 7: return "TS Activation Failure";
    case 8: return "TS Run Fault";
    case 9: return "Spin";
    case 10: return "APPS SCS Fault";
    case 11: return "APPS BPS Fault";
    case 12: return "Sim Wait TS Off";
    case 13: return "Sim Wait TS On";
    case 14: return "Sim Wait R2D Off";
    case 15: return "Sim Wait R2D On";
    default: return "Unknown";
    }
}

// Setter for vcu_ctrl_state (No-op for read-only telemetry)
void set_var_vcu_ctrl_state(const char * value)
{
    (void)value;
}
// Getter for bms_pack_inst_voltage
double get_var_bms_pack_inst_voltage(void)
{
    return g_bms_pack_inst_voltage;
}

// Setter for bms_pack_inst_voltage (No-op for read-only telemetry)
void set_var_bms_pack_inst_voltage(double value)
{
    (void)value;
}
// Getter for bms_pack_current
double get_var_bms_pack_current(void)
{
    return g_bms_pack_current;
}

// Setter for bms_pack_current (No-op for read-only telemetry)
void set_var_bms_pack_current(double value)
{
    (void)value;
}
// Getter for pdm_input_10_voltage
double get_var_pdm_input_10_voltage(void)
{
    return g_pdm_input_10_voltage;
}

// Setter for pdm_input_10_voltage (No-op for read-only telemetry)
void set_var_pdm_input_10_voltage(double value)
{
    (void)value;
}
// Getter for pm100_vsm_state
const char * get_var_pm100_vsm_state(void)
{
    switch (g_pm100_vsm_state)
    {
    case 0: return "VSM Start State";
    case 1: return "Pre-Charge Init state";
    case 2: return "pre-charge active state";
    case 3: return "pre-charge complete state";
    case 4: return "VSM wait state";
    case 5: return "VSM ready state";
    case 6: return "Motor Running State";
    case 7: return "blink fault code state";
    case 14: return "Shutdown state for Key Switch Mode 1";
    case 15: return "Reset the inverter";
    default: return "Unknown";
    }
}

// Setter for pm100_vsm_state (No-op for read-only telemetry)
void set_var_pm100_vsm_state(const char * value)
{
    (void)value;
}

// Getter for wheel_fl_speed
double get_var_wheel_fl_speed(void)
{
    return g_wheel_fl_speed;
}

// Setter for wheel_fl_speed (No-op for read-only telemetry)
void set_var_wheel_fl_speed(double value)
{
    (void)value;
}
// Getter for wheel_fr_speed
double get_var_wheel_fr_speed(void)
{
    return g_wheel_fr_speed;
}

// Setter for wheel_fr_speed (No-op for read-only telemetry)
void set_var_wheel_fr_speed(double value)
{
    (void)value;
}
// Getter for wheel_rl_speed
double get_var_wheel_rl_speed(void)
{
    return g_wheel_rl_speed;
}

// Setter for wheel_rl_speed (No-op for read-only telemetry)
void set_var_wheel_rl_speed(double value)
{
    (void)value;
}
// Getter for wheel_rr_speed
double get_var_wheel_rr_speed(void)
{
    return g_wheel_rr_speed;
}

// Setter for wheel_rr_speed (No-op for read-only telemetry)
void set_var_wheel_rr_speed(double value)
{
    (void)value;
}


/* ==================================================================== */
/* CAN Message Handlers                                                 */
/* ==================================================================== */


/**
 * @brief Decode and map RX messages for CAN_T
 */
void can_t_handle_rx_message(uint32_t id, const uint8_t *data, uint8_t length)
{
    switch (id)
    {
    case CAN_T_VCU_STATE_FRAME_ID:
    {
        struct can_t_vcu_state_t payload;
        if (can_t_vcu_state_unpack(&payload, data, length) == 0)
        {
            g_vcu_rolling_counter = (int32_t)can_t_vcu_state_vcu_rolling_counter_decode(payload.vcu_rolling_counter);
            g_vcu_ctrl_state = (int32_t)can_t_vcu_state_vcu_ctrl_state_decode(payload.vcu_ctrl_state);
        }
        break;
    }
    case CAN_T_BMS_PACK_STATE_FRAME_ID:
    {
        struct can_t_bms_pack_state_t payload;
        if (can_t_bms_pack_state_unpack(&payload, data, length) == 0)
        {
            g_bms_pack_inst_voltage = (double)can_t_bms_pack_state_bms_pack_inst_voltage_decode(payload.bms_pack_inst_voltage);
            g_bms_pack_current = (double)can_t_bms_pack_state_bms_pack_current_decode(payload.bms_pack_current);
        }
        break;
    }
    case CAN_T_PDM_IN_VOLTAGE_FRAME_ID:
    {
        struct can_t_pdm_in_voltage_t payload;
        if (can_t_pdm_in_voltage_unpack(&payload, data, length) == 0)
        {
            if (payload.pdm_in_voltage_compound_id == 1)
            {
                g_pdm_input_10_voltage = (double)can_t_pdm_in_voltage_pdm_input_10_voltage_decode(payload.pdm_input_10_voltage);
            }
        }
        break;
    }
    case CAN_T_PM100_INTERNAL_STATES_FRAME_ID:
    {
        struct can_t_pm100_internal_states_t payload;
        if (can_t_pm100_internal_states_unpack(&payload, data, length) == 0)
        {
            g_pm100_vsm_state = (int32_t)can_t_pm100_internal_states_pm100_vsm_state_decode(payload.pm100_vsm_state);
        }
        break;
    }

    default:
        // Unhandled frame ID on CAN_T
        break;
    }
}

/**
 * @brief Decode and map RX messages for CAN_S
 */
void can_s_handle_rx_message(uint32_t id, const uint8_t *data, uint8_t length)
{
    switch (id)
    {
    case CAN_S_WHEEL_SPEEDS_FRAME_ID:
    {
        struct can_s_wheel_speeds_t payload;
        if (can_s_wheel_speeds_unpack(&payload, data, length) == 0)
        {
            g_wheel_fl_speed = (double)can_s_wheel_speeds_wheel_fl_speed_decode(payload.wheel_fl_speed);
            g_wheel_fr_speed = (double)can_s_wheel_speeds_wheel_fr_speed_decode(payload.wheel_fr_speed);
            g_wheel_rl_speed = (double)can_s_wheel_speeds_wheel_rl_speed_decode(payload.wheel_rl_speed);
            g_wheel_rr_speed = (double)can_s_wheel_speeds_wheel_rr_speed_decode(payload.wheel_rr_speed);
        }
        break;
    }

    default:
        // Unhandled frame ID on CAN_S
        break;
    }
}
