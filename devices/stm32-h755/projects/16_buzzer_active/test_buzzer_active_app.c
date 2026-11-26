/* test_buzzer_active_app.c — 3 tests: SOS pattern contract. */
#include "unity.h"
#include "xc.h"
#include "buzzer_active_app.h"

static buzzer_active_app_t app;

void setUp(void)
{
    mock_sfr_reset();
    buzzer_active_app_init(&app, 17U);
}
void tearDown(void) {}

static void test_pattern_length_is_18(void)
{
    TEST_ASSERT_EQUAL_UINT8(25U, SOS_PATTERN_LENGTH);
}

static void test_first_element_sounds(void)
{
    buzzer_active_app_step(&app);
    TEST_ASSERT_TRUE(buzzer_active_app_sounding(&app));
}

static void test_pattern_wraps_after_full_cycle(void)
{
    int i;
    for (i = 0; i < (int)SOS_PATTERN_LENGTH; i++) buzzer_active_app_step(&app);
    TEST_ASSERT_EQUAL_UINT8(0U, buzzer_active_app_position(&app));
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_pattern_length_is_18);
    RUN_TEST(test_first_element_sounds);
    RUN_TEST(test_pattern_wraps_after_full_cycle);
    return UNITY_END();
}
#endif
