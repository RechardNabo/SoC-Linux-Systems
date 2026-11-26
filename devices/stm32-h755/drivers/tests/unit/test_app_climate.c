/* test_app_climate.c — host tests, STM32H563 device layer. */
#include "unity.h"
#include "xc.h"

#include "../../apps/climate_station/climate_station.h"
#include "../../peripherals/adc/stm_adc.h"

void setUp(void)    { mock_sfr_reset(); }
void tearDown(void) {}

void test_classify_bands(void)
{
    TEST_ASSERT_EQUAL(CLIMATE_BAND_COLD, climate_classify(1500));
    TEST_ASSERT_EQUAL(CLIMATE_BAND_COMFORT, climate_classify(2200));
    TEST_ASSERT_EQUAL(CLIMATE_BAND_HOT, climate_classify(3000));
}

void test_agree_within_tolerance(void)
{
    TEST_ASSERT_TRUE(climate_sensors_agree(2200, 2400));
    TEST_ASSERT_FALSE(climate_sensors_agree(2200, 2600));
}

void test_agreeing_sensors_yield_comfort_band(void)
{
    climate_station_t app;
    int i;
    stm_adc_init();
    climate_station_init(&app);
    ADC1_DR = 273U;   /* 12-bit raw ~= 22.0C comfort */
    for (i = 0; i < 4; i++) {
        ADC1_DR = 273U;
        climate_station_step(&app);
    }
    TEST_ASSERT_EQUAL(CLIMATE_BAND_COMFORT, app.band);
    TEST_ASSERT_EQUAL_UINT32(0U, app.fault_count);
}

#if defined(UNIT_TEST_HOST_STANDALONE) || defined(UNIT_TEST_HOST)
int main(void)
{
    UnityBegin("test_app_climate.c");
    RUN_TEST(test_classify_bands);
    RUN_TEST(test_agree_within_tolerance);
    RUN_TEST(test_agreeing_sensors_yield_comfort_band);
    return UnityEnd();
}
#endif
