#include "vibration_app.h"
#include "../../drivers/devices/kit/kit.h"

void vibration_app_init(vibration_app_t *app, uint8_t pin)
{
    dig_in_config_t cfg = kit_dig_in_config(KIT_VIBRATION, pin);
    dig_in_init(&app->sensor, &cfg);
    edge_count_init(&app->counter);
    app->events = 0U;
}

bool vibration_app_step(vibration_app_t *app)
{
    dig_in_sample(&app->sensor);
    if (edge_count_step(&app->counter, dig_in_state(&app->sensor))) {
        app->events++;
        return true;
    }
    return false;
}

uint32_t vibration_app_events(const vibration_app_t *app) { return app->events; }
bool vibration_app_active(vibration_app_t *app) { return dig_in_state(&app->sensor); }
