/* buzzer_active_app.h — SOS pattern player on the active buzzer.
 * Pattern table is the contract: 3 short, 3 long, 3 short, then silence. */
#ifndef BUZZER_ACTIVE_APP_H
#define BUZZER_ACTIVE_APP_H

#include <stdint.h>
#include <stdbool.h>
#include "../../drivers/devices/dig_out/dig_out.h"
#include "../lib/sequencer.h"

#define SOS_PATTERN_LENGTH  25U

typedef struct {
    dig_out_t buzzer;
    sequencer_t pattern;
    bool sounding;
} buzzer_active_app_t;

void buzzer_active_app_init(buzzer_active_app_t *app, uint8_t pin);
void buzzer_active_app_step(buzzer_active_app_t *app);   /* one call per 100ms tick */
bool buzzer_active_app_sounding(const buzzer_active_app_t *app);
uint8_t buzzer_active_app_position(const buzzer_active_app_t *app);
const uint32_t *buzzer_active_app_pattern(void);   /* exposed for the contract tests */

#endif
