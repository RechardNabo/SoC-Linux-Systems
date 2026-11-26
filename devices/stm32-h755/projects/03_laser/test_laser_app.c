/* test_laser_app.c — 3 tests: power-on safety + cadence contract. */
#include "unity.h"
#include "xc.h"
#include "laser_app.h"
#include "../../drivers/devices/kit/kit.h"

static laser_app_t app;

void setUp(void)
{
    mock_sfr_reset();
    laser_app_init(&app, kit_default_pin(KIT_LASER));
}
void tearDown(void) {}

static void test_output_inactive_at_power_on(void)
{
    TEST_ASSERT_FALSE(laser_app_output(&app));
}

static void test_first_toggle_after_half_period(void)
{
    uint32_t i;
    for (i = 0U; i < LASER_HALF_PERIOD_TICKS - 1U; i++) {
        laser_app_step(&app);
        TEST_ASSERT_FALSE(laser_app_output(&app));
    }
    laser_app_step(&app);
    TEST_ASSERT_TRUE(laser_app_output(&app));
}

static void test_full_period_returns_to_inactive(void)
{
    uint32_t i;
    for (i = 0U; i < LASER_HALF_PERIOD_TICKS; i++) laser_app_step(&app);
    TEST_ASSERT_TRUE(laser_app_output(&app));
    for (i = 0U; i < LASER_HALF_PERIOD_TICKS; i++) laser_app_step(&app);
    TEST_ASSERT_FALSE(laser_app_output(&app));
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_output_inactive_at_power_on);
    RUN_TEST(test_first_toggle_after_half_period);
    RUN_TEST(test_full_period_returns_to_inactive);
    return UNITY_END();
}
#endif
