#include "tilt_app.h"
#include "../../drivers/devices/kit/kit.h"

void tilt_app_init(tilt_app_t *app, uint8_t pin)
{
    dig_in_config_t cfg = kit_dig_in_config(KIT_TILT, pin);
    dig_in_init(&app->sensor, &cfg);
    edge_count_init(&app->counter);
    app->events = 0U;
}

bool tilt_app_step(tilt_app_t *app)
{
    dig_in_sample(&app->sensor);
    if (edge_count_step(&app->counter, dig_in_state(&app->sensor))) {
        app->events++;
        return true;
    }
    return false;
}

uint32_t tilt_app_events(const tilt_app_t *app) { return app->events; }
bool tilt_app_active(tilt_app_t *app) { return dig_in_state(&app->sensor); }
