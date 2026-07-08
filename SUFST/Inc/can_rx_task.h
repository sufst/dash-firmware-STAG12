#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void can_rx_task_run(void);

uint16_t can_rx_get_vcu_rolling_counter(void);

const char *can_rx_get_can_status(void);

#ifdef __cplusplus
}
#endif
