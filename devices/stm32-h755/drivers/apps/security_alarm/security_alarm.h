/* security_alarm.h — integration app 2: multi-sensor burglar alarm.
 * Devices: reed switch (#35 door) + vibration (#30 shock) + button (#28
 * arm/disarm) + relay (#6 siren power) + active buzzer (#17 local alert)
 * + dual LED (#22 status). The ADVANCED part: entry/exit timing and
 * sensor-fault supervision — an alarm that can be triggered while
 * DISARMED is a tamper event, not noise. Non-blocking FSM.
 *
 * States: DISARMED -> EXIT_DELAY (arming grace) -> ARMED -> ENTRY_DELAY
 * (door opened, grace to disarm) -> ALARM (latched) / TAMPER (instant). */
#ifndef SECURITY_ALARM_H
#define SECURITY_ALARM_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    ALARM_STATE_DISARMED = 0,
    ALARM_STATE_EXIT_DELAY,
    ALARM_STATE_ARMED,
    ALARM_STATE_ENTRY_DELAY,
    ALARM_STATE_ALARM,
    ALARM_STATE_TAMPER
} alarm_state_t;

typedef struct {
    alarm_state_t state;
    uint32_t state_ticks;      /* ticks spent in current state */
    bool door_closed;
    bool shock_detected;
    bool arm_pressed;
    uint32_t alarm_count;
    uint32_t tamper_count;
} security_alarm_t;

void security_alarm_init(security_alarm_t *app);
/* inputs sampled by caller each tick — keeps the FSM pure logic */
void security_alarm_inputs(security_alarm_t *app, bool door_closed, bool shock, bool arm_button);
void security_alarm_step(security_alarm_t *app);   /* call per tick */
/* outputs the FSM wants driven — caller applies to devices */
bool security_alarm_siren_on(const security_alarm_t *app);
bool security_alarm_status_led_red(const security_alarm_t *app);

#define ALARM_EXIT_DELAY_TICKS   100U   /* 10s at 10Hz tick */
#define ALARM_ENTRY_DELAY_TICKS  50U    /* 5s to disarm after door opens */

#endif
