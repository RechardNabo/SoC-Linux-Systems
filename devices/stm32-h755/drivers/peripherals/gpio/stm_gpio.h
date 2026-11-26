/* stm_gpio.h — GPIO driver for STM32H5.
 * MODER 2-bit mode field per pin; BSRR atomic set/reset for outputs —
 * no RMW anywhere in the write path. */
#ifndef STM_GPIO_H
#define STM_GPIO_H

#include <stdint.h>
#include <stdbool.h>
#include "../../bsp/stm_board.h"

typedef enum {
    STM_GPIO_STATUS_OK = 0,
    STM_GPIO_STATUS_INVALID_PIN
} stm_gpio_status_t;

stm_gpio_status_t stm_gpio_set_output(stm_port_t port, uint8_t pin);
stm_gpio_status_t stm_gpio_set_input(stm_port_t port, uint8_t pin);
stm_gpio_status_t stm_gpio_write(stm_port_t port, uint8_t pin, bool high);
stm_gpio_status_t stm_gpio_toggle(stm_port_t port, uint8_t pin);
bool stm_gpio_read(stm_port_t port, uint8_t pin);

#endif
