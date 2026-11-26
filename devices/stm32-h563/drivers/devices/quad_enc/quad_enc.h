/* quad_enc.h — quadrature decoder for the KY-040 rotary encoder (#15).
 * 20 detents/rev with AB phase output. Software decode: sampled in the
 * cooperative loop, valid state transitions count steps, invalid ones
 * (impossible bit jumps = bounce/noise) are REJECTED — the state machine
 * is the debounce. The push button (SW) is a plain dig_in, not this
 * driver's concern. */
#ifndef QUAD_ENC_H
#define QUAD_ENC_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    QUAD_ENC_STATUS_OK = 0,
    QUAD_ENC_STATUS_INVALID_CONFIG
} quad_enc_status_t;

typedef struct {
    uint8_t pin_a;
    uint8_t pin_b;
    int8_t direction;   /* +1 or -1: which way increments */
} quad_enc_config_t;

typedef struct {
    quad_enc_config_t cfg;
    uint8_t last_state;   /* 2-bit AB */
    int32_t count;
    int32_t detents;
    uint8_t steps_per_detent;
} quad_enc_t;

quad_enc_status_t quad_enc_init(quad_enc_t *dev, const quad_enc_config_t *config);
quad_enc_status_t quad_enc_sample(quad_enc_t *dev);
int32_t quad_enc_count(const quad_enc_t *dev);
int32_t quad_enc_detents(const quad_enc_t *dev);
void quad_enc_reset(quad_enc_t *dev);

#endif
