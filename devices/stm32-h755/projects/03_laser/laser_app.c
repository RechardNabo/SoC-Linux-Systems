#include "laser_app.h"
#include "../../drivers/devices/kit/kit.h"

void laser_app_init(laser_app_t *app, uint8_t pin)
{
    dig_out_config_t cfg = kit_dig_out_config(KIT_LASER, pin);
    dig_out_init(&app->device, &cfg);   /* drives INACTIVE at power-on — the relay safety */
    blink_init(&app->cadence, LASER_HALF_PERIOD_TICKS);
}

void laser_app_step(laser_app_t *app)
{
    dig_out_set(&app->device, blink_step(&app->cadence));
}

bool laser_app_output(const laser_app_t *app)
{
    return dig_out_is_on(&app->device);
}
