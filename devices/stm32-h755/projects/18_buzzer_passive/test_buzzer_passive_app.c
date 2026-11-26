/* test_buzzer_passive_app.c — 3 tests: the scale contract. */
#include "unity.h"
#include "xc.h"
#include "buzzer_passive_app.h"

static buzzer_passive_app_t app;

void setUp(void)
{
    mock_sfr_reset();
    buzzer_passive_app_init(&app, 1U, 250000000UL);
}
void tearDown(void) {}

static void test_scale_is_ascending_first_octave(void)
{
    const uint32_t *s = buzzer_passive_app_scale();
    int i;
    for (i = 0; i < 7; i++) TEST_ASSERT_TRUE(s[i] < s[i + 1]);
    TEST_ASSERT_EQUAL_UINT32(262U, s[0]);
}

static void test_position_wraps_after_all_notes(void)
{
    int i;
    for (i = 0; i < (int)SCALE_NOTE_COUNT; i++) buzzer_passive_app_step(&app);
    TEST_ASSERT_EQUAL_UINT8(0U, buzzer_passive_app_position(&app));
}

static void test_first_step_consumes_first_note(void)
{
    buzzer_passive_app_step(&app);
    TEST_ASSERT_EQUAL_UINT8(1U, buzzer_passive_app_position(&app));
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_scale_is_ascending_first_octave);
    RUN_TEST(test_position_wraps_after_all_notes);
    RUN_TEST(test_first_step_consumes_first_note);
    return UNITY_END();
}
#endif
