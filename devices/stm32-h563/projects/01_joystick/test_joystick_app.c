/* test_joystick_app.c — 3 tests: direction classification contract. */
#include "unity.h"
#include "xc.h"
#include "joystick_app.h"

void setUp(void) { mock_sfr_reset(); }
void tearDown(void) {}

static void test_centered_stick_is_neutral(void)
{
    TEST_ASSERT_EQUAL(JOYSTICK_NEUTRAL, joystick_classify(2048, 2048));
    TEST_ASSERT_EQUAL(JOYSTICK_NEUTRAL, joystick_classify(2200, 1900));
}

static void test_full_deflection_classifies_correctly(void)
{
    TEST_ASSERT_EQUAL(JOYSTICK_RIGHT, joystick_classify(4095, 2048));
    TEST_ASSERT_EQUAL(JOYSTICK_LEFT,  joystick_classify(0, 2048));
    TEST_ASSERT_EQUAL(JOYSTICK_DOWN,  joystick_classify(2048, 4095));
    TEST_ASSERT_EQUAL(JOYSTICK_UP,    joystick_classify(2048, 0));
}

static void test_deadzone_boundary_behavior(void)
{
    TEST_ASSERT_EQUAL(JOYSTICK_NEUTRAL, joystick_classify(2548, 2048));
    TEST_ASSERT_EQUAL(JOYSTICK_RIGHT, joystick_classify(2698, 2048));
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_centered_stick_is_neutral);
    RUN_TEST(test_full_deflection_classifies_correctly);
    RUN_TEST(test_deadzone_boundary_behavior);
    return UNITY_END();
}
#endif
