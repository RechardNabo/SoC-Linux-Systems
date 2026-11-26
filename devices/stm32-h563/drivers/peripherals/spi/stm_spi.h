/* stm_spi.h — SPI master for STM32H5 (SPI1/2, the H5-generation SPI).
 * Baud is power-of-two only: MBR selects clk/2^(n+1) — the driver picks
 * the fastest rate that never exceeds the target, and exposes the
 * quantization honestly. */
#ifndef STM_SPI_H
#define STM_SPI_H

#include <stdint.h>
#include <stdbool.h>

typedef enum { STM_SPI1 = 0, STM_SPI2, STM_SPI_CHANNEL_COUNT } stm_spi_channel_t;
typedef enum {
    STM_SPI_STATUS_OK = 0, STM_SPI_STATUS_INVALID_CHANNEL,
    STM_SPI_STATUS_INVALID_PARAM, STM_SPI_STATUS_TIMEOUT
} stm_spi_status_t;
typedef enum { STM_SPI_MODE_0 = 0, STM_SPI_MODE_1, STM_SPI_MODE_2, STM_SPI_MODE_3 } stm_spi_mode_t;

typedef struct { uint32_t clk_hz; uint32_t clock_hz; stm_spi_mode_t mode; } stm_spi_config_t;

stm_spi_status_t stm_spi_init(stm_spi_channel_t ch, const stm_spi_config_t *config);
stm_spi_status_t stm_spi_exchange_byte(stm_spi_channel_t ch, uint8_t tx, uint8_t *rx_out);
uint32_t stm_spi_mbr(uint32_t clk_hz, uint32_t clock_hz);
uint32_t stm_spi_actual_clock(uint32_t clk_hz, uint32_t mbr);

#endif
