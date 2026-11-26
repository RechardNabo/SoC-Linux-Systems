/* test_app_alarm.c — host tests, PIC32 device layer. */
#include "unity.h"
#include "xc.h"

#include "../../apps/security_alarm/security_alarm.h"

void setUp(void)    {}
void tearDown(void) {}

static void tick(security_alarm_t *app, int n)
{
    int i;
    for (i = 0; i < n; i++) security_alarm_step(app);
}

void test_arm_exit_delay_then_armed(void)
{
    security_alarm_t app;
    security_alarm_init(&app);
    security_alarm_inputs(&app, true, false, true);
    security_alarm_step(&app);
    TEST_ASSERT_EQUAL(ALARM_STATE_EXIT_DELAY, app.state);
    security_alarm_inputs(&app, true, false, false);
    tick(&app, ALARM_EXIT_DELAY_TICKS);
    TEST_ASSERT_EQUAL(ALARM_STATE_ARMED, app.state);
}

void test_shock_while_armed_instant_alarm(void)
{
    security_alarm_t app;
    security_alarm_init(&app);
    security_alarm_inputs(&app, true, false, true);
    security_alarm_step(&app);
    security_alarm_inputs(&app, true, true, false);
    tick(&app, ALARM_EXIT_DELAY_TICKS + 1);
    TEST_ASSERT_EQUAL(ALARM_STATE_ALARM, app.state);
    TEST_ASSERT_EQUAL_UINT32(1U, app.alarm_count);
    TEST_ASSERT_TRUE(security_alarm_siren_on(&app));
}

void test_door_open_entry_delay_grace(void)
{
    security_alarm_t app;
    security_alarm_init(&app);
    security_alarm_inputs(&app, true, false, true);
    security_alarm_step(&app);
    security_alarm_inputs(&app, true, false, false);
    tick(&app, ALARM_EXIT_DELAY_TICKS);
    security_alarm_inputs(&app, false, false, false);
    security_alarm_step(&app);
    TEST_ASSERT_EQUAL(ALARM_STATE_ENTRY_DELAY, app.state);
    security_alarm_inputs(&app, true, false, true);
    security_alarm_step(&app);
    security_alarm_inputs(&app, true, false, false);
    security_alarm_step(&app);
    TEST_ASSERT_EQUAL(ALARM_STATE_DISARMED, app.state);
    TEST_ASSERT_EQUAL_UINT32(0U, app.alarm_count);
}

void test_tamper_counted_while_disarmed(void)
{
    security_alarm_t app;
    security_alarm_init(&app);
    security_alarm_inputs(&app, true, true, false);
    security_alarm_step(&app);
    TEST_ASSERT_EQUAL(ALARM_STATE_DISARMED, app.state);
    TEST_ASSERT_EQUAL_UINT32(1U, app.tamper_count);
}

#if defined(UNIT_TEST_HOST_STANDALONE) || defined(UNIT_TEST_HOST)
int main(void)
{
    UnityBegin("test_app_alarm.c");
    RUN_TEST(test_arm_exit_delay_then_armed);
    RUN_TEST(test_shock_while_armed_instant_alarm);
    RUN_TEST(test_door_open_entry_delay_grace);
    RUN_TEST(test_tamper_counted_while_disarmed);
    return UnityEnd();
}
#endif
