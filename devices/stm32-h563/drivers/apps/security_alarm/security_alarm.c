/* security_alarm.c — see security_alarm.h. FSM is pure logic: inputs
 * injected, outputs queried — hardware binding lives in the app shell.
 * This is what makes the alarm logic host-testable end to end. */
#include "security_alarm.h"

#include <stddef.h>

void security_alarm_init(security_alarm_t *app)
{
    app->state = ALARM_STATE_DISARMED;
    app->state_ticks = 0U;
    app->door_closed = true;
    app->shock_detected = false;
    app->arm_pressed = false;
    app->alarm_count = 0U;
    app->tamper_count = 0U;
}

void security_alarm_inputs(security_alarm_t *app, bool door_closed, bool shock, bool arm_button)
{
    app->door_closed = door_closed;
    app->shock_detected = shock;
    app->arm_pressed = arm_button;
}

static void enter(security_alarm_t *app, alarm_state_t s)
{
    if (app->state != s) {
        app->state = s;
        app->state_ticks = 0U;
    }
}

void security_alarm_step(security_alarm_t *app)
{
    app->state_ticks++;
    switch (app->state) {
        case ALARM_STATE_DISARMED:
            /* vibration while disarmed = tamper probe: someone testing
             * the installation. Not an alarm — but it is counted. */
            if (app->shock_detected) app->tamper_count++;
            if (app->arm_pressed) enter(app, ALARM_STATE_EXIT_DELAY);
            break;
        case ALARM_STATE_EXIT_DELAY:
            /* grace period to leave; door activity here is normal */
            if (app->state_ticks >= ALARM_EXIT_DELAY_TICKS) enter(app, ALARM_STATE_ARMED);
            break;
        case ALARM_STATE_ARMED:
            if (!app->door_closed) enter(app, ALARM_STATE_ENTRY_DELAY);
            else if (app->shock_detected) {
                /* shock while armed: instant alarm, no grace — a window
                 * break must not wait politely */
                app->alarm_count++;
                enter(app, ALARM_STATE_ALARM);
            } else if (app->arm_pressed) {
                enter(app, ALARM_STATE_DISARMED);
            }
            break;
        case ALARM_STATE_ENTRY_DELAY:
            if (app->arm_pressed) {
                enter(app, ALARM_STATE_DISARMED);
            } else if (app->state_ticks >= ALARM_ENTRY_DELAY_TICKS) {
                app->alarm_count++;
                enter(app, ALARM_STATE_ALARM);
            } else if (app->door_closed && app->state_ticks > 10U) {
                /* door closed again quickly: still count as armed —
                 * real systems stay in entry delay; simplified here */
                enter(app, ALARM_STATE_ARMED);
            }
            break;
        case ALARM_STATE_ALARM:
        case ALARM_STATE_TAMPER:
            /* latched: only the arm button silences — and it must be
             * pressed while the door is closed (can't reset from outside) */
            if (app->arm_pressed && app->door_closed) enter(app, ALARM_STATE_DISARMED);
            break;
        default:
            enter(app, ALARM_STATE_DISARMED);
            break;
    }
}

bool security_alarm_siren_on(const security_alarm_t *app)
{
    return app->state == ALARM_STATE_ALARM;
}

bool security_alarm_status_led_red(const security_alarm_t *app)
{
    return app->state == ALARM_STATE_ARMED || app->state == ALARM_STATE_ALARM
        || app->state == ALARM_STATE_ENTRY_DELAY;
}
