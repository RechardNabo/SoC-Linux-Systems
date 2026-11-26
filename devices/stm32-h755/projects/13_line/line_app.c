#include "line_app.h"
#include "../../drivers/devices/kit/kit.h"

void line_app_init(line_app_t *app, uint8_t pin)
{
    dig_in_config_t cfg = kit_dig_in_config(KIT_LINE, pin);
    dig_in_init(&app->sensor, &cfg);
    edge_count_init(&app->counter);
    app->events = 0U;
}

bool line_app_step(line_app_t *app)
{
    dig_in_sample(&app->sensor);
    if (edge_count_step(&app->counter, dig_in_state(&app->sensor))) {
        app->events++;
        return true;
    }
    return false;
}

uint32_t line_app_events(const line_app_t *app) { return app->events; }
bool line_app_active(line_app_t *app) { return dig_in_state(&app->sensor); }
