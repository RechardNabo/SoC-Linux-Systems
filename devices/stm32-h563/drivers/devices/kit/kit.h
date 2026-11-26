/* kit.h — the 37-in-1 sensor kit as configured device instances on RP2040.
 * Each module is DATA: class + pins + electrical parameters. Adding or
 * rewiring a module means editing a table row, not writing a driver.
 *
 * Default NUCLEO-H563ZI wiring map — pins as DEVPAL_PIN(port,pin) ids:
  PA0-2   analog inputs (ADC1 ch0-2)   PD0  relay IN (active LOW!)
  PA5/6/7 RGB LED R/G/B (TIM2 ch1/2/3) PD1  active buzzer
  PB0     passive buzzer (TIM3 ch1)    PD2  laser
  PC0-3   digital inputs bank 1        PE0-3 digital inputs bank 2
  PB8/9   rotary encoder CLK/DT
  H5 ADC is 12-bit — scaling uses 4095 denominators. 1-wire modules
  (DHT11/DS18B20) UNSUPPORTED this pass — needs the time engine.
 */
#ifndef KIT_H
#define KIT_H

#include <stdint.h>
#include <stdbool.h>

#include "../dig_in/dig_in.h"
#include "../analog_in/analog_in.h"
#include "../dig_out/dig_out.h"
#include "../pwm_out/pwm_out.h"
#include "../quad_enc/quad_enc.h"
/* onewire deferred on STM32H563: needs the pin-schedule time engine */

typedef enum {
    KIT_JOYSTICK = 1, KIT_IR_RECEIVER, KIT_LASER, KIT_DHT11, KIT_IR_PROXIMITY,
    KIT_RELAY, KIT_OBSTACLE, KIT_HEARTBEAT, KIT_SOUND_ANALOG, KIT_TOUCH,
    KIT_FLAME, KIT_RGB_LED, KIT_LINE, KIT_HALL_LINEAR, KIT_ROTARY_ENC,
    KIT_BUZZER_ACTIVE, KIT_MAGIC_CUP, KIT_BUZZER_PASSIVE, KIT_DS18B20,
    KIT_BROKEN_LIGHT, KIT_LM35, KIT_DUAL_LED, KIT_MERCURY, KIT_HALL_SWITCH,
    KIT_REED_RGB, KIT_TILT, KIT_FLASH_LED, KIT_BUTTON, KIT_LDR,
    KIT_VIBRATION, KIT_KNOCK, KIT_LM35_B, KIT_HALL_LINEAR_B, KIT_MIC_SOUND,
    KIT_REED_BIG, KIT_JOYSTICK_BTN = 40  /* joystick button as its own instance */
} kit_module_id_t;

typedef enum {
    KIT_CLASS_DIG_IN,
    KIT_CLASS_ANALOG_IN,
    KIT_CLASS_DIG_OUT,
    KIT_CLASS_PWM_RGB,
    KIT_CLASS_PWM_BUZZER,
    KIT_CLASS_QUAD_ENC,
    KIT_CLASS_DHT11,
    KIT_CLASS_DS18B20,
    KIT_CLASS_UNSUPPORTED   /* IR receiver: needs capture infrastructure */
} kit_class_t;

/* static descriptor — the dataheet facts per module */
typedef struct {
    kit_module_id_t id;
    kit_class_t cls;
    const char *name;
    bool module_needs_5v;   /* true: run digital-only or level-shift */
} kit_module_info_t;

const kit_module_info_t *kit_info(kit_module_id_t id);

/* default pin bindings — the wiring table from the header comment */
uint8_t kit_default_pin(kit_module_id_t id);

/* typed config constructors — correct electrical facts baked in */
dig_in_config_t    kit_dig_in_config(kit_module_id_t id, uint8_t pin);
analog_in_config_t kit_analog_config(kit_module_id_t id, uint8_t adc_channel);
dig_out_config_t   kit_dig_out_config(kit_module_id_t id, uint8_t pin);

#endif
