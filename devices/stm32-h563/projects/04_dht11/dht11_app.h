/* dht11_app.h — humidity classification logic, pure and host-testable.
 * The sensor transport is exercised on target; what the firmware DECIDES
 * from a reading is pinned here. */
#ifndef DHT11_APP_H
#define DHT11_APP_H

#include <stdint.h>

typedef enum {
    COMFORT_DRY = 0, COMFORT_IDEAL, COMFORT_HUMID
} comfort_band_t;

static inline comfort_band_t dht11_classify_humidity(int32_t rh_percent)
{
    if (rh_percent < 30) return COMFORT_DRY;
    if (rh_percent <= 60) return COMFORT_IDEAL;
    return COMFORT_HUMID;
}

#endif
