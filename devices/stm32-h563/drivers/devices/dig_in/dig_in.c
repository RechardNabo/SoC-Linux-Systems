/* dig_in.c — see dig_in.h. */
#include "dig_in.h"
#include "../pal/devpal.h"

dig_in_status_t dig_in_init(dig_in_t *dev, const dig_in_config_t *config)
{
    if (dev == 0 || config == 0) return DIG_IN_STATUS_INVALID_CONFIG;
    if (!devpal_pin_input(config->pin))
        return DIG_IN_STATUS_INVALID_CONFIG;
    dev->cfg = *config;
    dev->state = false;
    dev->integrate_count = 0U;
    dev->last_raw = false;
    return DIG_IN_STATUS_OK;
}

dig_in_status_t dig_in_sample(dig_in_t *dev)
{
    bool raw, active;
    if (dev == 0) return DIG_IN_STATUS_INVALID_CONFIG;
    raw = devpal_pin_read(dev->cfg.pin);
    active = (dev->cfg.active == DIG_IN_ACTIVE_LOW) ? !raw : raw;

    if (dev->cfg.debounce_samples == 0U) {
        dev->state = active;
        return DIG_IN_STATUS_OK;
    }
    if (active == dev->state) {
        dev->integrate_count = 0U;
    } else if (++dev->integrate_count >= dev->cfg.debounce_samples) {
        dev->state = active;
        dev->integrate_count = 0U;
    }
    dev->last_raw = raw;
    return DIG_IN_STATUS_OK;
}

bool dig_in_state(const dig_in_t *dev)
{
    return dev != 0 && dev->state;
}
