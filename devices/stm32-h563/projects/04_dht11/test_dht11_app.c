/* test_dht11_app.c — 3 tests: humidity comfort classification contract. */
#include "unity.h"
#include "dht11_app.h"

void setUp(void) {}
void tearDown(void) {}

static void test_dry_band(void)
{
    TEST_ASSERT_EQUAL(COMFORT_DRY, dht11_classify_humidity(20));
    TEST_ASSERT_EQUAL(COMFORT_DRY, dht11_classify_humidity(29));
}

static void test_ideal_band_includes_boundaries(void)
{
    TEST_ASSERT_EQUAL(COMFORT_IDEAL, dht11_classify_humidity(30));
    TEST_ASSERT_EQUAL(COMFORT_IDEAL, dht11_classify_humidity(45));
    TEST_ASSERT_EQUAL(COMFORT_IDEAL, dht11_classify_humidity(60));
}

static void test_humid_band(void)
{
    TEST_ASSERT_EQUAL(COMFORT_HUMID, dht11_classify_humidity(61));
    TEST_ASSERT_EQUAL(COMFORT_HUMID, dht11_classify_humidity(90));
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_dry_band);
    RUN_TEST(test_ideal_band_includes_boundaries);
    RUN_TEST(test_humid_band);
    return UNITY_END();
}
#endif
