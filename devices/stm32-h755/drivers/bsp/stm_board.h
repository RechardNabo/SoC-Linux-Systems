/* stm_board.h — STM32H755ZI board/silicon facts.
 * THE defining fact of this part: TWO cores share the peripheral bus.
 * Cortex-M7 (CPU1, HSEM coreid 3) and Cortex-M4 (CPU2, HSEM coreid 1) can
 * both reach every peripheral — nothing in silicon stops both from
 * driving the same UART. Ownership is therefore a SOFTWARE contract,
 * enforced by HSEM mutual exclusion, and it must be explicit in the BSP.
 *
 * Ownership convention for the kit projects:
 *   M7 owns: application peripherals — USART console, I2C, SPI, ADC, TIM-PWM
 *   M4 owns: real-time capture paths (input capture, future IR decoder)
 * GPIO pins are owned per-pin by whichever core's project uses them —
 * documented in the project READMEs, one owner per pin, no sharing. */
#ifndef STM_BOARD_H
#define STM_BOARD_H

#include <stdint.h>
#include <stdbool.h>

#define STM_SYSCLK_MAX_HZ  480000000UL   /* M7 max — H755 is 480MHz-grade */

typedef enum {
    STM_PORTA = 0, STM_PORTB, STM_PORTC, STM_PORTD,
    STM_PORTE, STM_PORTF, STM_PORTG, STM_PORTH, STM_PORT_COUNT
} stm_port_t;

static inline bool stm_gpio_valid(stm_port_t port, uint8_t pin)
{
    return port < STM_PORT_COUNT && pin <= 15U;
}

/* ---- dual-core facts ---- */
typedef enum {
    STM_CORE_CM7 = 0,
    STM_CORE_CM4
} stm_core_t;

/* HSEM hardware core IDs — silicon constants, not conventions */
#define STM_HSEM_COREID_CM7  0x3U
#define STM_HSEM_COREID_CM4  0x1U

/* unit-test builds compile single-core images; the core is a build-time
 * fact on target (CPUID/ROM table), a compile-time selection here */
#ifndef STM_CORE_BUILD
#define STM_CORE_BUILD  STM_CORE_CM7
#endif

static inline stm_core_t stm_core_self(void)
{
    return (stm_core_t)STM_CORE_BUILD;
}

static inline uint8_t stm_core_hsem_id(stm_core_t core)
{
    return core == STM_CORE_CM7 ? STM_HSEM_COREID_CM7 : STM_HSEM_COREID_CM4;
}

/* semaphore allocation contract — which HSEM index guards what.
 * 0-15: peripheral ownership. 16-31: shared-memory/mailbox protocol. */
#define STM_HSEM_USART3_OWNER   0U
#define STM_HSEM_SPI1_OWNER     1U
#define STM_HSEM_I2C1_OWNER     2U
#define STM_HSEM_ADC1_OWNER     3U
#define STM_HSEM_TIM2_OWNER     4U
#define STM_HSEM_MAILBOX_TX     16U
#define STM_HSEM_MAILBOX_RX     17U

#endif
