/* ds18b20_app.h — temperature classification logic, pure and host-testable.
 * Same bands as the climate_station app: consistency is the contract. */
#ifndef DS18B20_APP_H
#define DS18B20_APP_H

#include <stdint.h>

typedef enum {
    TEMP_BAND_COLD = 0, TEMP_BAND_COMFORT, TEMP_BAND_HOT
} temp_band_t;

static inline temp_band_t ds18b20_classify(int32_t centi_celsius)
{
    if (centi_celsius < 1800) return TEMP_BAND_COLD;
    if (centi_celsius <= 2800) return TEMP_BAND_COMFORT;
    return TEMP_BAND_HOT;
}

#endif
