#include "touch_app.h"
#include "../../drivers/devices/kit/kit.h"

void touch_app_init(touch_app_t *app, uint8_t pin)
{
    dig_in_config_t cfg = kit_dig_in_config(KIT_TOUCH, pin);
    dig_in_init(&app->sensor, &cfg);
    edge_count_init(&app->counter);
    app->events = 0U;
}

bool touch_app_step(touch_app_t *app)
{
    dig_in_sample(&app->sensor);
    if (edge_count_step(&app->counter, dig_in_state(&app->sensor))) {
        app->events++;
        return true;
    }
    return false;
}

uint32_t touch_app_events(const touch_app_t *app) { return app->events; }
bool touch_app_active(touch_app_t *app) { return dig_in_state(&app->sensor); }
