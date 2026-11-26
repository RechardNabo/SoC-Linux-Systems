/* devpal.h — device-pin abstraction for STM32H563.
 * Pin IDs encode port+pin: (port << 4) | pin. stm_gpio is already
 * port+pin shaped, so the shim is thin — it exists so the device classes
 * stay byte-identical across MCU families. */
#ifndef DEVPAL_H
#define DEVPAL_H

#include <stdint.h>
#include <stdbool.h>
#include "../../peripherals/gpio/stm_gpio.h"

#define DEVPAL_PIN(port, pin)   ((uint8_t)(((uint8_t)(port) << 4) | ((pin) & 0x0FU)))
#define DEVPAL_PORT_OF(pinid)   ((stm_port_t)((pinid) >> 4))
#define DEVPAL_PINNO_OF(pinid)  ((uint8_t)((pinid) & 0x0FU))

bool devpal_pin_input(uint8_t pinid);
bool devpal_pin_output(uint8_t pinid);
void devpal_pin_write(uint8_t pinid, bool high);
bool devpal_pin_read(uint8_t pinid);

#endif
