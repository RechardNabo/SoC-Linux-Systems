/* analog_in.h — analog-input device class: joystick axes, LDR, LM35,
 * linear hall, sound envelope, PPG. Integer scaling per module config. */
#ifndef ANALOG_IN_H
#define ANALOG_IN_H

#include <stdint.h>
#include <stdbool.h>
#include "../../peripherals/adc/stm_adc.h"

typedef enum {
    ANALOG_IN_STATUS_OK = 0,
    ANALOG_IN_STATUS_INVALID_CONFIG,
    ANALOG_IN_STATUS_READ_FAULT
} analog_in_status_t;

/* scale: eng = raw x num / den + offset — LM35 centiC example in README */
typedef struct {
    uint8_t adc_channel;
    int32_t scale_num;
    int32_t scale_den;
    int32_t offset;
} analog_in_config_t;

typedef struct {
    analog_in_config_t cfg;
} analog_in_t;

analog_in_status_t analog_in_init(analog_in_t *dev, const analog_in_config_t *config);
analog_in_status_t analog_in_read_raw(analog_in_t *dev, uint16_t *raw_out);
analog_in_status_t analog_in_read_scaled(analog_in_t *dev, int32_t *eng_out);
int32_t analog_in_scale(uint16_t raw, const analog_in_config_t *cfg);

#endif
