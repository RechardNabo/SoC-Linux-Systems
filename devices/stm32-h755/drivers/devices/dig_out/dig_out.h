/* dig_out.h — digital-output device class: relay, active buzzer, laser,
 * dual/flash LEDs. Active level explicit — the kit relay is active-LOW
 * and getting this wrong energizes the coil at power-on. */
#ifndef DIG_OUT_H
#define DIG_OUT_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    DIG_OUT_STATUS_OK = 0,
    DIG_OUT_STATUS_INVALID_CONFIG
} dig_out_status_t;

typedef enum {
    DIG_OUT_ACTIVE_HIGH = 0,
    DIG_OUT_ACTIVE_LOW
} dig_out_active_t;

typedef struct {
    uint8_t pin;
    dig_out_active_t active;
} dig_out_config_t;

typedef struct {
    dig_out_config_t cfg;
    bool on;
} dig_out_t;

dig_out_status_t dig_out_init(dig_out_t *dev, const dig_out_config_t *config);
dig_out_status_t dig_out_set(dig_out_t *dev, bool on);
dig_out_status_t dig_out_toggle(dig_out_t *dev);
bool dig_out_is_on(const dig_out_t *dev);

#endif
