/* climate_station.h — integration app 1 (PIC32 adaptation): dual-LM35
 * cross-validated climate monitor + RGB LED band indicator.
 * Devices: LM35 #21 + LM35 #32 + RGB LED #12. Cross-validation: two
 * independent channels must agree within 3C or SENSOR_FAULT — never
 * trust either alone. (1-wire deferred on PIC32 this pass.) */
#ifndef CLIMATE_STATION_H
#define CLIMATE_STATION_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    CLIMATE_STATE_INIT = 0,
    CLIMATE_STATE_READ_LM35_A,
    CLIMATE_STATE_READ_LM35_B,
    CLIMATE_STATE_EVALUATE,
    CLIMATE_STATE_SENSOR_FAULT
} climate_state_t;

typedef enum {
    CLIMATE_BAND_COLD = 0,
    CLIMATE_BAND_COMFORT,
    CLIMATE_BAND_HOT,
    CLIMATE_BAND_FAULT
} climate_band_t;

typedef struct {
    climate_state_t state;
    int32_t lm35a_centic;
    int32_t lm35b_centic;
    climate_band_t band;
    uint32_t fault_count;
} climate_station_t;

void climate_station_init(climate_station_t *app);
void climate_station_step(climate_station_t *app);
climate_band_t climate_classify(int32_t centic);
bool climate_sensors_agree(int32_t a_centic, int32_t b_centic);

#endif
