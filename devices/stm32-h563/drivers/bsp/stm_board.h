/* stm_board.h — board facts, STM32H563 (Cortex-M33, 250 MHz max).
 * 32-bit registers. GPIO BSRR gives atomic set/reset — the correct idiom.
 * Reference transfer target: the MPT-Firmware-1U-BTS-POPO project runs
 * this exact silicon — this library is the register-level counterpart
 * to its HAL-based feature drivers. */
#ifndef STM_BOARD_H
#define STM_BOARD_H

#include <stdint.h>
#include <stdbool.h>

#define STM_SYSCLK_MAX_HZ  250000000UL

/* ports A-H present on the ZG package (144-pin); pins 0-15 per port */
typedef enum {
    STM_PORTA = 0, STM_PORTB, STM_PORTC, STM_PORTD,
    STM_PORTE, STM_PORTF, STM_PORTG, STM_PORTH, STM_PORT_COUNT
} stm_port_t;

static inline bool stm_gpio_valid(stm_port_t port, uint8_t pin)
{
    return port < STM_PORT_COUNT && pin <= 15U;
}

#define STM_USART_PRESENT_MASK  0x7U   /* USART1/2/3 in scope */
#define STM_SPI_PRESENT_MASK    0x3U   /* SPI1/2 */
#define STM_I2C_PRESENT_MASK    0x3U   /* I2C1/2 */

#endif
