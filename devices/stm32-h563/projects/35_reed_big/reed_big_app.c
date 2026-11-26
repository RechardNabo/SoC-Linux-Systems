#include "reed_big_app.h"
#include "../../drivers/devices/kit/kit.h"

void reed_big_app_init(reed_big_app_t *app, uint8_t pin)
{
    dig_in_config_t cfg = kit_dig_in_config(KIT_REED_BIG, pin);
    dig_in_init(&app->sensor, &cfg);
    edge_count_init(&app->counter);
    app->events = 0U;
}

bool reed_big_app_step(reed_big_app_t *app)
{
    dig_in_sample(&app->sensor);
    if (edge_count_step(&app->counter, dig_in_state(&app->sensor))) {
        app->events++;
        return true;
    }
    return false;
}

uint32_t reed_big_app_events(const reed_big_app_t *app) { return app->events; }
bool reed_big_app_active(reed_big_app_t *app) { return dig_in_state(&app->sensor); }
