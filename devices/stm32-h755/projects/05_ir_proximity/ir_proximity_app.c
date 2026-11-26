#include "ir_proximity_app.h"
#include "../../drivers/devices/kit/kit.h"

void ir_proximity_app_init(ir_proximity_app_t *app, uint8_t pin)
{
    dig_in_config_t cfg = kit_dig_in_config(KIT_IR_PROXIMITY, pin);
    dig_in_init(&app->sensor, &cfg);
    edge_count_init(&app->counter);
    app->events = 0U;
}

bool ir_proximity_app_step(ir_proximity_app_t *app)
{
    dig_in_sample(&app->sensor);
    if (edge_count_step(&app->counter, dig_in_state(&app->sensor))) {
        app->events++;
        return true;
    }
    return false;
}

uint32_t ir_proximity_app_events(const ir_proximity_app_t *app) { return app->events; }
bool ir_proximity_app_active(ir_proximity_app_t *app) { return dig_in_state(&app->sensor); }
