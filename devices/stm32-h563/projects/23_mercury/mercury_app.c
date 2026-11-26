#include "mercury_app.h"
#include "../../drivers/devices/kit/kit.h"

void mercury_app_init(mercury_app_t *app, uint8_t pin)
{
    dig_in_config_t cfg = kit_dig_in_config(KIT_MERCURY, pin);
    dig_in_init(&app->sensor, &cfg);
    edge_count_init(&app->counter);
    app->events = 0U;
}

bool mercury_app_step(mercury_app_t *app)
{
    dig_in_sample(&app->sensor);
    if (edge_count_step(&app->counter, dig_in_state(&app->sensor))) {
        app->events++;
        return true;
    }
    return false;
}

uint32_t mercury_app_events(const mercury_app_t *app) { return app->events; }
bool mercury_app_active(mercury_app_t *app) { return dig_in_state(&app->sensor); }
