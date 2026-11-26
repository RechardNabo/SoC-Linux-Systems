/* test_dual_led_app.c — 3 tests: the never-both-on contract. */
#include "unity.h"
#include "xc.h"
#include "dual_led_app.h"

static dual_led_app_t app;

void setUp(void)
{
    mock_sfr_reset();
    dual_led_app_init(&app, 14U, 15U);
}
void tearDown(void) {}

static void test_both_off_at_init(void)
{
    TEST_ASSERT_FALSE(dual_led_app_red_on(&app));
    TEST_ASSERT_FALSE(dual_led_app_green_on(&app));
}

static void test_never_both_on_across_full_cycles(void)
{
    int i;
    for (i = 0; i < 250; i++) {
        dual_led_app_step(&app);
        TEST_ASSERT_FALSE(dual_led_app_red_on(&app) && dual_led_app_green_on(&app));
    }
}

static void test_strict_alternation_once_running(void)
{
    int i;
    for (i = 0; i < 50; i++) dual_led_app_step(&app);
    for (i = 0; i < 120; i++) {
        dual_led_app_step(&app);
        TEST_ASSERT_TRUE(dual_led_app_red_on(&app) != dual_led_app_green_on(&app));
    }
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_both_off_at_init);
    RUN_TEST(test_never_both_on_across_full_cycles);
    RUN_TEST(test_strict_alternation_once_running);
    return UNITY_END();
}
#endif
