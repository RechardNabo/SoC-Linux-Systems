/* dig_out.c — see dig_out.h. Init drives the INACTIVE state immediately:
 * a relay must never sit in whatever state the pin booted into. */
#include "dig_out.h"
#include "../pal/devpal.h"

static void drive(const dig_out_t *dev, bool on)
{
    const bool high = (dev->cfg.active == DIG_OUT_ACTIVE_LOW) ? !on : on;
    devpal_pin_write(dev->cfg.pin, high);
}

dig_out_status_t dig_out_init(dig_out_t *dev, const dig_out_config_t *config)
{
    if (dev == 0 || config == 0) return DIG_OUT_STATUS_INVALID_CONFIG;
    dev->cfg = *config;
    dev->on = false;
    if (!devpal_pin_output(config->pin))
        return DIG_OUT_STATUS_INVALID_CONFIG;
    drive(dev, false);
    return DIG_OUT_STATUS_OK;
}

dig_out_status_t dig_out_set(dig_out_t *dev, bool on)
{
    if (dev == 0) return DIG_OUT_STATUS_INVALID_CONFIG;
    dev->on = on;
    drive(dev, on);
    return DIG_OUT_STATUS_OK;
}

dig_out_status_t dig_out_toggle(dig_out_t *dev)
{
    if (dev == 0) return DIG_OUT_STATUS_INVALID_CONFIG;
    return dig_out_set(dev, !dev->on);
}

bool dig_out_is_on(const dig_out_t *dev)
{
    return dev != 0 && dev->on;
}
