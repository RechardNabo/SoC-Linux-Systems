/* dig_in.h — digital-input device class: buttons, reeds, tilt, hall
 * switches, thresholded proximity sensors. One driver, configured per
 * module. Debounce is integrating: N consecutive equal samples flip the
 * state — immune to single-sample noise spikes. */
#ifndef DIG_IN_H
#define DIG_IN_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    DIG_IN_STATUS_OK = 0,
    DIG_IN_STATUS_INVALID_CONFIG
} dig_in_status_t;

typedef enum {
    DIG_IN_ACTIVE_HIGH = 0,
    DIG_IN_ACTIVE_LOW
} dig_in_active_t;

typedef struct {
    uint8_t pin;
    dig_in_active_t active;
    uint8_t debounce_samples;   /* 0 = no debounce, else 1-255 */
} dig_in_config_t;

typedef struct {
    dig_in_config_t cfg;
    bool state;
    uint8_t integrate_count;
    bool last_raw;
} dig_in_t;

dig_in_status_t dig_in_init(dig_in_t *dev, const dig_in_config_t *config);
dig_in_status_t dig_in_sample(dig_in_t *dev);
bool dig_in_state(const dig_in_t *dev);

#endif
