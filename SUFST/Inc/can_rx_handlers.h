/* Auto generated: Do not edit directly, instead add signals in Codegen/signal_mapping.yaml or update Codegen/can_rx_handlers.h.j2 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void can_t_handle_rx_message(uint32_t id, const uint8_t *data, uint8_t length);
void can_s_handle_rx_message(uint32_t id, const uint8_t *data, uint8_t length);

#ifdef __cplusplus
}
#endif