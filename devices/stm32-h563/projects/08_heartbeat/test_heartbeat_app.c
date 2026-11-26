/* test_heartbeat_app.c — 3 tests: beat counting with refractory honesty. */
#include "unity.h"
#include "xc.h"
#include "heartbeat_app.h"

static heartbeat_app_t app;

void setUp(void)
{
    mock_sfr_reset();
    stm_adc_init();
    heartbeat_app_init(&app, 0U);
}
void tearDown(void) {}

static bool step_with(uint16_t raw)
{
    ADC1_DR = raw;
    return heartbeat_app_step(&app);
}

static void inject_beat(void)
{
    int i;
    for (i = 0; i < 5; i++) (void)step_with(3000U);
    for (i = 0; i < 5; i++) (void)step_with(1000U);
}

static void test_synthetic_beat_is_counted(void)
{
    inject_beat();
    TEST_ASSERT_EQUAL_UINT32(1U, heartbeat_app_beats(&app));
}

static void test_ringing_within_refractory_not_double_counted(void)
{
    int i;
    inject_beat();
    for (i = 0; i < 3; i++) (void)step_with(3000U);
    for (i = 0; i < 3; i++) (void)step_with(1000U);
    TEST_ASSERT_EQUAL_UINT32(1U, heartbeat_app_beats(&app));
}

static void test_second_beat_after_refractory_counts(void)
{
    int i;
    inject_beat();
    for (i = 0; i < 40; i++) (void)step_with(1000U);
    inject_beat();
    TEST_ASSERT_EQUAL_UINT32(2U, heartbeat_app_beats(&app));
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_synthetic_beat_is_counted);
    RUN_TEST(test_ringing_within_refractory_not_double_counted);
    RUN_TEST(test_second_beat_after_refractory_counts);
    return UNITY_END();
}
#endif
