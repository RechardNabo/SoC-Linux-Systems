/* test_lm35_app.c — 3 tests: flap-proof hysteresis (STM32).
 * ADC injection: write DR before each step; the mock completes conversion
 * instantly and DR-read clears EOC exactly like silicon. */
#include "unity.h"
#include "xc.h"
#include "lm35_app.h"
#include "../../drivers/devices/kit/kit.h"

static lm35_app_t app;

void setUp(void)
{
    mock_sfr_reset();
    stm_adc_init();
    lm35_app_init(&app, 0U);
}
void tearDown(void) {}

static bool step_with(uint16_t raw)
{
    ADC1_DR = raw;
    return lm35_app_step(&app);
}

static void test_crossing_high_threshold_fires_one_event(void)
{
    (void)step_with(1000U);
    TEST_ASSERT_EQUAL_UINT32(0U, lm35_app_events(&app));
    TEST_ASSERT_TRUE(step_with(3000U));
    TEST_ASSERT_EQUAL_UINT32(1U, lm35_app_events(&app));
    TEST_ASSERT_FALSE(step_with(3000U));
    TEST_ASSERT_EQUAL_UINT32(1U, lm35_app_events(&app));
}

static void test_noise_inside_deadband_does_not_flap(void)
{
    (void)step_with(3000U);
    TEST_ASSERT_EQUAL_UINT32(1U, lm35_app_events(&app));
    int i;
    for (i = 0; i < 10; i++) (void)step_with(2000U);
    TEST_ASSERT_EQUAL_UINT32(1U, lm35_app_events(&app));
    for (i = 0; i < 5; i++) (void)step_with(3000U);
    TEST_ASSERT_EQUAL_UINT32(1U, lm35_app_events(&app));
}

static void test_full_drop_below_low_rearms(void)
{
    (void)step_with(3000U);
    (void)step_with(500U);
    TEST_ASSERT_TRUE(step_with(3000U));
    TEST_ASSERT_EQUAL_UINT32(2U, lm35_app_events(&app));
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_crossing_high_threshold_fires_one_event);
    RUN_TEST(test_noise_inside_deadband_does_not_flap);
    RUN_TEST(test_full_drop_below_low_rearms);
    return UNITY_END();
}
#endif
