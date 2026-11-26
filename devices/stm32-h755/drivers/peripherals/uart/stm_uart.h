/* stm_uart.h — USART driver for STM32H5 (USART1/2/3).
 * BRR is simply clk/baud for oversampling-16 — no fractional divisor
 * table, but the value must be exact enough; error still verified. */
#ifndef STM_UART_H
#define STM_UART_H

#include <stdint.h>
#include <stdbool.h>

typedef enum { STM_USART1 = 0, STM_USART2, STM_USART3, STM_UART_CHANNEL_COUNT } stm_uart_channel_t;

typedef enum {
    STM_UART_STATUS_OK = 0,
    STM_UART_STATUS_INVALID_CHANNEL,
    STM_UART_STATUS_INVALID_PARAM,
    STM_UART_STATUS_INVALID_BAUD
} stm_uart_status_t;

typedef enum { STM_UART_PARITY_NONE = 0, STM_UART_PARITY_EVEN, STM_UART_PARITY_ODD } stm_uart_parity_t;

typedef struct {
    uint32_t clk_hz;
    uint32_t baud;
    stm_uart_parity_t parity;
    uint8_t stop_bits;
} stm_uart_config_t;

#define STM_UART_ERR_LIMIT_X1000  20

stm_uart_status_t stm_uart_init(stm_uart_channel_t ch, const stm_uart_config_t *config);
bool stm_uart_write_byte(stm_uart_channel_t ch, uint8_t byte);
bool stm_uart_read_byte(stm_uart_channel_t ch, uint8_t *byte_out);

#endif
