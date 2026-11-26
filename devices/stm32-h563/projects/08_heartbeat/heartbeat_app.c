#include "heartbeat_app.h"
#include "../../drivers/devices/kit/kit.h"

void heartbeat_app_init(heartbeat_app_t *app, uint8_t channel)
{
    analog_in_config_t cfg = kit_analog_config(KIT_HEARTBEAT, channel);
    analog_in_init(&app->sensor, &cfg);
    peak_detect_init(&app->detector, HEARTBEAT_THRESHOLD_COUNT, HEARTBEAT_REFRACTORY_TICKS);
}

bool heartbeat_app_step(heartbeat_app_t *app)
{
    uint16_t raw = 0U;
    if (analog_in_read_raw(&app->sensor, &raw) != ANALOG_IN_STATUS_OK) return false;
    return peak_detect_step(&app->detector, (int32_t)raw);
}

uint32_t heartbeat_app_beats(const heartbeat_app_t *app)
{
    return app->detector.count;
}
