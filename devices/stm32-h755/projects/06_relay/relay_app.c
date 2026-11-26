#include "relay_app.h"
#include "../../drivers/devices/kit/kit.h"

void relay_app_init(relay_app_t *app, uint8_t pin)
{
    dig_out_config_t cfg = kit_dig_out_config(KIT_RELAY, pin);
    dig_out_init(&app->device, &cfg);   /* drives INACTIVE at power-on — the relay safety */
    blink_init(&app->cadence, RELAY_HALF_PERIOD_TICKS);
}

void relay_app_step(relay_app_t *app)
{
    dig_out_set(&app->device, blink_step(&app->cadence));
}

bool relay_app_output(const relay_app_t *app)
{
    return dig_out_is_on(&app->device);
}
