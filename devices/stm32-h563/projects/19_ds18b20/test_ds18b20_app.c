/* test_ds18b20_app.c — 3 tests: temperature band classification contract. */
#include "unity.h"
#include "ds18b20_app.h"

void setUp(void) {}
void tearDown(void) {}

static void test_cold_band(void)
{
    TEST_ASSERT_EQUAL(TEMP_BAND_COLD, ds18b20_classify(1500));
    TEST_ASSERT_EQUAL(TEMP_BAND_COLD, ds18b20_classify(1799));
}

static void test_comfort_band_includes_boundaries(void)
{
    TEST_ASSERT_EQUAL(TEMP_BAND_COMFORT, ds18b20_classify(1800));
    TEST_ASSERT_EQUAL(TEMP_BAND_COMFORT, ds18b20_classify(2300));
    TEST_ASSERT_EQUAL(TEMP_BAND_COMFORT, ds18b20_classify(2800));
}

static void test_hot_band(void)
{
    TEST_ASSERT_EQUAL(TEMP_BAND_HOT, ds18b20_classify(2801));
    TEST_ASSERT_EQUAL(TEMP_BAND_HOT, ds18b20_classify(8500));
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_cold_band);
    RUN_TEST(test_comfort_band_includes_boundaries);
    RUN_TEST(test_hot_band);
    return UNITY_END();
}
#endif
