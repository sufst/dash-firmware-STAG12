#include "can_rx_task.h"

#include <stdatomic.h>
#include <stdio.h>

#include "can.h"
#include "can_t.h"
#include "cmsis_os2.h"
#include "rtcan.h"

extern rtcan_handle_t can_bus_rtcan_t;
extern rtcan_handle_t can_bus_rtcan_s;

#define CAN_RX_QUEUE_CAPACITY 8U

static uint32_t s_queueMem[RTCAN_OS_QUEUE_MEM_SIZE(CAN_RX_QUEUE_CAPACITY, sizeof(rtcan_msg_t *)) / sizeof(uint32_t)];
static rtcan_queue_t s_queue;

static _Atomic uint16_t s_vcuRollingCounter = 0;
char *get_var_vcu_rolling_counter(void) { static char buf[8]; snprintf(buf, sizeof(buf), "%u", s_vcuRollingCounter); return buf; }
void set_var_vcu_rolling_counter(const char *value) { (void) value; }

static char s_canStatus[24] = "CAN Unknown";
const char *get_var_can_state(void) { return s_canStatus; }
void set_var_can_state(const char *value) { (void) value; }

void can_rx_task_run(void)
{
    if (rtcan_os_queue_create(&s_queue, "can_rx_vcu_state", sizeof(rtcan_msg_t *),
                               CAN_RX_QUEUE_CAPACITY, s_queueMem, sizeof(s_queueMem)) != RTCAN_OS_OK)
    {
        return;
    }

    while (rtcan_subscribe(&can_bus_rtcan_t, CAN_T_VCU_STATE_FRAME_ID, s_queue) != RTCAN_OK)
    {
        osDelay(50);
    }

    uint32_t error = can_bus_get_error();
    if (error == 0U)
    {
        snprintf(s_canStatus, sizeof(s_canStatus), "CAN OK");
    }
    else
    {
        snprintf(s_canStatus, sizeof(s_canStatus), "CAN Error 0x%08lX", (unsigned long) error);
    }

    for (;;)
    {
        rtcan_msg_t *msg;
        if (rtcan_os_queue_receive(s_queue, &msg, RTCAN_OS_WAIT_FOREVER) == RTCAN_OS_OK)
        {
            struct can_t_vcu_state_t state;
            if (can_t_vcu_state_unpack(&state, msg->data, msg->length) == 0)
            {
                double value = can_t_vcu_state_vcu_rolling_counter_decode(state.vcu_rolling_counter);
                atomic_store(&s_vcuRollingCounter, (uint16_t) value);
            }
            rtcan_msg_consumed(&can_bus_rtcan_t, msg);
        }
    }
}

