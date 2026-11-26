/* test_flash_led_app.c — 3 tests: power-on safety + cadence contract. */
#include "unity.h"
#include "xc.h"
#include "flash_led_app.h"
#include "../../drivers/devices/kit/kit.h"

static flash_led_app_t app;

void setUp(void)
{
    mock_sfr_reset();
    flash_led_app_init(&app, kit_default_pin(KIT_FLASH_LED));
}
void tearDown(void) {}

static void test_output_inactive_at_power_on(void)
{
    TEST_ASSERT_FALSE(flash_led_app_output(&app));
}

static void test_first_toggle_after_half_period(void)
{
    uint32_t i;
    for (i = 0U; i < FLASH_LED_HALF_PERIOD_TICKS - 1U; i++) {
        flash_led_app_step(&app);
        TEST_ASSERT_FALSE(flash_led_app_output(&app));
    }
    flash_led_app_step(&app);
    TEST_ASSERT_TRUE(flash_led_app_output(&app));
}

static void test_full_period_returns_to_inactive(void)
{
    uint32_t i;
    for (i = 0U; i < FLASH_LED_HALF_PERIOD_TICKS; i++) flash_led_app_step(&app);
    TEST_ASSERT_TRUE(flash_led_app_output(&app));
    for (i = 0U; i < FLASH_LED_HALF_PERIOD_TICKS; i++) flash_led_app_step(&app);
    TEST_ASSERT_FALSE(flash_led_app_output(&app));
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
