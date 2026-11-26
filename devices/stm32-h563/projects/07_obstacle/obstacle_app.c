#include "obstacle_app.h"
#include "../../drivers/devices/kit/kit.h"

void obstacle_app_init(obstacle_app_t *app, uint8_t pin)
{
    dig_in_config_t cfg = kit_dig_in_config(KIT_OBSTACLE, pin);
    dig_in_init(&app->sensor, &cfg);
    edge_count_init(&app->counter);
    app->events = 0U;
}

bool obstacle_app_step(obstacle_app_t *app)
{
    dig_in_sample(&app->sensor);
    if (edge_count_step(&app->counter, dig_in_state(&app->sensor))) {
        app->events++;
        return true;
    }
    return false;
}

uint32_t obstacle_app_events(const obstacle_app_t *app) { return app->events; }
bool obstacle_app_active(obstacle_app_t *app) { return dig_in_state(&app->sensor); }
