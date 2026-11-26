/* climate_station.c — see climate_station.h. */
#include "climate_station.h"

#include "../../devices/kit/kit.h"

#define CROSSCHECK_TOLERANCE_CENTIC  300
#define BAND_COLD_LIMIT_CENTIC       1800
#define BAND_HOT_LIMIT_CENTIC        2600
#define STM_TIM_CLK_HZ               250000000UL

static analog_in_t lm35a, lm35b;
static rgb_led_t rgb;

climate_band_t climate_classify(int32_t centic)
{
    if (centic < BAND_COLD_LIMIT_CENTIC) return CLIMATE_BAND_COLD;
    if (centic > BAND_HOT_LIMIT_CENTIC) return CLIMATE_BAND_HOT;
    return CLIMATE_BAND_COMFORT;
}

bool climate_sensors_agree(int32_t a_centic, int32_t b_centic)
{
    const int32_t diff = (a_centic > b_centic) ? a_centic - b_centic : b_centic - a_centic;
    return diff <= CROSSCHECK_TOLERANCE_CENTIC;
}

void climate_station_init(climate_station_t *app)
{
    analog_in_config_t acfg_a = kit_analog_config(KIT_LM35, 0U);    /* AN0 */
    analog_in_config_t acfg_b = kit_analog_config(KIT_LM35_B, 1U);  /* AN1 */
    app->state = CLIMATE_STATE_INIT;
    app->fault_count = 0U;
    app->band = CLIMATE_BAND_COMFORT;
    analog_in_init(&lm35a, &acfg_a);
    analog_in_init(&lm35b, &acfg_b);
    rgb_led_init(&rgb, 1U, 2U, 3U, STM_TIM_CLK_HZ, 1000UL);   /* TIM2 ch1/2/3 on PA5/6/7 */
}

static void apply_band_led(climate_band_t band)
{
    switch (band) {
        case CLIMATE_BAND_COLD:    rgb_led_set(&rgb, 0U, 0U, 255U);   break;
        case CLIMATE_BAND_COMFORT: rgb_led_set(&rgb, 0U, 255U, 0U);   break;
        case CLIMATE_BAND_HOT:     rgb_led_set(&rgb, 255U, 0U, 0U);   break;
        default:                   rgb_led_set(&rgb, 128U, 0U, 128U); break;
    }
}

void climate_station_step(climate_station_t *app)
{
    switch (app->state) {
        case CLIMATE_STATE_INIT:
            app->state = CLIMATE_STATE_READ_LM35_A;
            break;
        case CLIMATE_STATE_READ_LM35_A:
            if (analog_in_read_scaled(&lm35a, &app->lm35a_centic) == ANALOG_IN_STATUS_OK)
                app->state = CLIMATE_STATE_READ_LM35_B;
            else
                app->state = CLIMATE_STATE_SENSOR_FAULT;
            break;
        case CLIMATE_STATE_READ_LM35_B:
            if (analog_in_read_scaled(&lm35b, &app->lm35b_centic) == ANALOG_IN_STATUS_OK)
                app->state = CLIMATE_STATE_EVALUATE;
            else
                app->state = CLIMATE_STATE_SENSOR_FAULT;
            break;
        case CLIMATE_STATE_EVALUATE:
            if (climate_sensors_agree(app->lm35a_centic, app->lm35b_centic)) {
                app->band = climate_classify(app->lm35a_centic);
            } else {
                app->band = CLIMATE_BAND_FAULT;
                app->fault_count++;
            }
            apply_band_led(app->band);
            app->state = CLIMATE_STATE_READ_LM35_A;
            break;
        case CLIMATE_STATE_SENSOR_FAULT:
        default:
            app->band = CLIMATE_BAND_FAULT;
            apply_band_led(CLIMATE_BAND_FAULT);
            app->fault_count++;
            app->state = CLIMATE_STATE_READ_LM35_A;
            break;
    }
}
