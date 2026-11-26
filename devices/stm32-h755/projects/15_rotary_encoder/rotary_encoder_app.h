/* rotary_encoder_app.h — encoder as a bounded 0-100 position control.
 * The application contract: rotation moves position within clamp limits,
 * the button re-centers to 0. No unbounded drift into meaningless counts. */
#ifndef ROTARY_ENCODER_APP_H
#define ROTARY_ENCODER_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/quad_enc/quad_enc.h"
#include "../../drivers/devices/dig_in/dig_in.h"

typedef struct {
    quad_enc_t encoder;
    dig_in_t button;
    int32_t position;      /* clamped 0-100 */
    int32_t last_detents;
} rotary_encoder_app_t;

void rotary_encoder_app_init(rotary_encoder_app_t *app, uint8_t pin_a, uint8_t pin_b, uint8_t pin_btn);
void rotary_encoder_app_step(rotary_encoder_app_t *app);
int32_t rotary_encoder_app_position(const rotary_encoder_app_t *app);

#endif
