/* test_rgb_led_app.c — 3 tests: hue progression + colorwheel endpoints. */
#include "unity.h"
#include "xc.h"
#include "rgb_led_app.h"

static rgb_led_app_t app;

void setUp(void)
{
    mock_sfr_reset();
    rgb_led_app_init(&app, 1U, 2U, 3U, 250000000UL, 1000U);
}
void tearDown(void) {}

static void test_hue_advances_one_per_step(void)
{
    TEST_ASSERT_EQUAL_UINT16(0U, rgb_led_app_hue(&app));
    rgb_led_app_step(&app);
    TEST_ASSERT_EQUAL_UINT16(1U, rgb_led_app_hue(&app));
    rgb_led_app_step(&app);
    TEST_ASSERT_EQUAL_UINT16(2U, rgb_led_app_hue(&app));
}

static void test_hue_wraps_at_wheel_end(void)
{
    int i;
    for (i = 0; i < (int)COLORWHEEL_STEPS; i++) rgb_led_app_step(&app);
    TEST_ASSERT_EQUAL_UINT16(0U, rgb_led_app_hue(&app));
}

static void test_colorwheel_endpoints_are_pure_primaries(void)
{
    uint8_t r, g, b;
    colorwheel_rgb(0U, &r, &g, &b);
    TEST_ASSERT_EQUAL_UINT8(255U, r); TEST_ASSERT_EQUAL_UINT8(0U, g); TEST_ASSERT_EQUAL_UINT8(0U, b);
    colorwheel_rgb(256U, &r, &g, &b);
    TEST_ASSERT_EQUAL_UINT8(0U, r); TEST_ASSERT_EQUAL_UINT8(255U, g); TEST_ASSERT_EQUAL_UINT8(0U, b);
    colorwheel_rgb(512U, &r, &g, &b);
    TEST_ASSERT_EQUAL_UINT8(0U, r); TEST_ASSERT_EQUAL_UINT8(0U, g); TEST_ASSERT_EQUAL_UINT8(255U, b);
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_hue_advances_one_per_step);
    RUN_TEST(test_hue_wraps_at_wheel_end);
    RUN_TEST(test_colorwheel_endpoints_are_pure_primaries);
    return UNITY_END();
}
#endif
