/* quad_enc.c — see quad_enc.h.
 * Valid single-bit transitions follow the Gray-code cycle 00-01-11-10-00
 * (one direction) or its reverse. Two-bit jumps are physically impossible
 * in one sample — they are noise and rejected without counting. */
#include "quad_enc.h"
#include "../pal/devpal.h"

/* transition table indexed by (last<<2)|current: +1 CW step, -1 CCW, 0 invalid/noop */
static const int8_t transitions[16] = {
    /* last\cur 00  01  10  11  — encoded as (last<<2)|cur index 0..15 */
     0,  1, -1,  0,   /* last 00 */
    -1,  0,  0,  1,   /* last 01 */
     1,  0,  0, -1,   /* last 10 */
     0, -1,  1,  0    /* last 11 */
};

quad_enc_status_t quad_enc_init(quad_enc_t *dev, const quad_enc_config_t *config)
{
    if (dev == 0 || config == 0) return QUAD_ENC_STATUS_INVALID_CONFIG;
    if (!devpal_pin_input(config->pin_a)) return QUAD_ENC_STATUS_INVALID_CONFIG;
    if (!devpal_pin_input(config->pin_b)) return QUAD_ENC_STATUS_INVALID_CONFIG;
    dev->cfg = *config;
    dev->last_state = 0U;
    dev->count = 0;
    dev->detents = 0;
    dev->steps_per_detent = 4U;   /* KY-040: 4 quadrature steps per detent */
    return QUAD_ENC_STATUS_OK;
}

quad_enc_status_t quad_enc_sample(quad_enc_t *dev)
{
    uint8_t cur, idx;
    int8_t step;
    if (dev == 0) return QUAD_ENC_STATUS_INVALID_CONFIG;
    cur = (uint8_t)((devpal_pin_read(dev->cfg.pin_a) ? 2U : 0U)
                  | (devpal_pin_read(dev->cfg.pin_b) ? 1U : 0U));
    idx = (uint8_t)((dev->last_state << 2) | cur);
    step = transitions[idx];
    if (step != 0) {
        const int32_t before = dev->count;
        dev->count += (int32_t)step * dev->cfg.direction;
        /* detent accounting: count full 4-step groups */
        dev->detents = dev->count / 4;
        (void)before;
    }
    dev->last_state = cur;
    return QUAD_ENC_STATUS_OK;
}

int32_t quad_enc_count(const quad_enc_t *dev) { return dev != 0 ? dev->count : 0; }
int32_t quad_enc_detents(const quad_enc_t *dev) { return dev != 0 ? dev->detents : 0; }

void quad_enc_reset(quad_enc_t *dev)
{
    if (dev != 0) {
        dev->count = 0;
        dev->detents = 0;
    }
}
