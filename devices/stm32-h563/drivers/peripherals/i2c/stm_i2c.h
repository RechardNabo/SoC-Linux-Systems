/* stm_i2c.h — I2C master for STM32H5 (I2C1/2, v2 peripheral).
 * TIMINGR is the notorious one: PRESC/SCLDEL/SDADEL/SCLH/SCLL all packed
 * in one register and the combinations are non-obvious — the driver
 * computes from clock + target rate with the reference-manual equations
 * and exposes the fields for verification. */
#ifndef STM_I2C_H
#define STM_I2C_H

#include <stdint.h>
#include <stdbool.h>

typedef enum { STM_I2C1 = 0, STM_I2C2, STM_I2C_CHANNEL_COUNT } stm_i2c_channel_t;
typedef enum {
    STM_I2C_STATUS_OK = 0, STM_I2C_STATUS_INVALID_CHANNEL,
    STM_I2C_STATUS_INVALID_PARAM, STM_I2C_STATUS_TIMING_IMPOSSIBLE
} stm_i2c_status_t;

typedef struct { uint32_t clk_hz; uint32_t clock_hz; } stm_i2c_config_t;

typedef struct {
    uint32_t presc, scldel, sdadel, sclh, scll;
} stm_i2c_timing_t;

stm_i2c_status_t stm_i2c_init(stm_i2c_channel_t ch, const stm_i2c_config_t *config);
stm_i2c_status_t stm_i2c_compute_timing(uint32_t clk_hz, uint32_t clock_hz, stm_i2c_timing_t *out);
uint32_t stm_i2c_pack_timingr(const stm_i2c_timing_t *t);

#endif
