#include "button_app.h"
#include "../../drivers/devices/kit/kit.h"

void button_app_init(button_app_t *app, uint8_t pin)
{
    dig_in_config_t cfg = kit_dig_in_config(KIT_BUTTON, pin);
    dig_in_init(&app->sensor, &cfg);
    edge_count_init(&app->counter);
    app->events = 0U;
}

bool button_app_step(button_app_t *app)
{
    dig_in_sample(&app->sensor);
    if (edge_count_step(&app->counter, dig_in_state(&app->sensor))) {
        app->events++;
        return true;
    }
    return false;
}

uint32_t button_app_events(const button_app_t *app) { return app->events; }
bool button_app_active(button_app_t *app) { return dig_in_state(&app->sensor); }
