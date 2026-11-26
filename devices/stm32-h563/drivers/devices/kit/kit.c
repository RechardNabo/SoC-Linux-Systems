/* kit.c — see kit.h. Facts sourced from 37pcs-sensor-kit-specs.md. */
#include "kit.h"
#include "../pal/devpal.h"

#include <stddef.h>

static const kit_module_info_t modules[] = {
    { KIT_JOYSTICK,      KIT_CLASS_ANALOG_IN,   "PS2 joystick XY",        false },
    { KIT_IR_RECEIVER,   KIT_CLASS_UNSUPPORTED, "VS1838B IR receiver",    false },
    { KIT_LASER,         KIT_CLASS_DIG_OUT,     "650nm laser diode",      true  },
    { KIT_DHT11,         KIT_CLASS_UNSUPPORTED,       "DHT11 temp+humidity",    false },
    { KIT_IR_PROXIMITY,  KIT_CLASS_DIG_IN,      "IR reflective proximity",true  },
    { KIT_RELAY,         KIT_CLASS_DIG_OUT,     "5V relay (ACTIVE LOW)",  true  },
    { KIT_OBSTACLE,      KIT_CLASS_DIG_IN,      "IR obstacle avoidance",  true  },
    { KIT_HEARTBEAT,     KIT_CLASS_ANALOG_IN,   "finger PPG heartbeat",   false },
    { KIT_SOUND_ANALOG,  KIT_CLASS_ANALOG_IN,   "sound envelope",         false },
    { KIT_TOUCH,         KIT_CLASS_DIG_IN,      "capacitive touch",       false },
    { KIT_FLAME,         KIT_CLASS_DIG_IN,      "flame IR 760-1100nm",    false },
    { KIT_RGB_LED,       KIT_CLASS_PWM_RGB,     "RGB LED common-cathode", true  },
    { KIT_LINE,          KIT_CLASS_DIG_IN,      "TCRT5000 line sensor",   true  },
    { KIT_HALL_LINEAR,   KIT_CLASS_ANALOG_IN,   "49E linear hall",        true  },
    { KIT_ROTARY_ENC,    KIT_CLASS_QUAD_ENC,    "KY-040 rotary encoder",  false },
    { KIT_BUZZER_ACTIVE, KIT_CLASS_DIG_OUT,     "active buzzer 2.3kHz",   true  },
    { KIT_MAGIC_CUP,     KIT_CLASS_ANALOG_IN,   "magic cup LED+LDR",      true  },
    { KIT_BUZZER_PASSIVE,KIT_CLASS_PWM_BUZZER,  "passive buzzer",         true  },
    { KIT_DS18B20,       KIT_CLASS_UNSUPPORTED,     "DS18B20 precision temp", false },
    { KIT_BROKEN_LIGHT,  KIT_CLASS_DIG_IN,      "light-break sensor",     true  },
    { KIT_LM35,          KIT_CLASS_ANALOG_IN,   "LM35 analog temp",       false },
    { KIT_DUAL_LED,      KIT_CLASS_DIG_OUT,     "red+green dual LED",     true  },
    { KIT_MERCURY,       KIT_CLASS_DIG_IN,      "mercury tilt",           false },
    { KIT_HALL_SWITCH,   KIT_CLASS_DIG_IN,      "A3144 hall switch",      true  },
    { KIT_REED_RGB,      KIT_CLASS_DIG_IN,      "reed+RGB combo",         true  },
    { KIT_TILT,          KIT_CLASS_DIG_IN,      "SW-200D ball tilt",      false },
    { KIT_FLASH_LED,     KIT_CLASS_DIG_OUT,     "7-color flash LED",      false },
    { KIT_BUTTON,        KIT_CLASS_DIG_IN,      "tactile button",         false },
    { KIT_LDR,           KIT_CLASS_ANALOG_IN,   "GL55xx LDR",             false },
    { KIT_VIBRATION,     KIT_CLASS_DIG_IN,      "SW-18010 vibration",     false },
    { KIT_KNOCK,         KIT_CLASS_DIG_IN,      "piezo knock",            true  },
    { KIT_LM35_B,        KIT_CLASS_ANALOG_IN,   "LM35 (duplicate #32)",   false },
    { KIT_HALL_LINEAR_B, KIT_CLASS_ANALOG_IN,   "linear hall (dup #33)",  true  },
    { KIT_MIC_SOUND,     KIT_CLASS_DIG_IN,      "mic sound threshold D0", false },
    { KIT_REED_BIG,      KIT_CLASS_DIG_IN,      "large reed switch",      false },
};

const kit_module_info_t *kit_info(kit_module_id_t id)
{
    size_t i;
    for (i = 0U; i < sizeof(modules) / sizeof(modules[0]); i++) {
        if (modules[i].id == id) return &modules[i];
    }
    return NULL;
}

uint8_t kit_default_pin(kit_module_id_t id)
{
    /* the wiring table — banked so simultaneous multi-module apps have
     * no conflicts; see header comment */
    switch (id) {
        case KIT_JOYSTICK:      return DEVPAL_PIN(STM_PORTA, 0);   /* ADC1 ch0 = VRx */
        case KIT_RELAY:         return DEVPAL_PIN(STM_PORTD, 0);
        case KIT_BUZZER_ACTIVE: return DEVPAL_PIN(STM_PORTD, 1);
        case KIT_LASER:         return DEVPAL_PIN(STM_PORTD, 2);
        case KIT_BUTTON:        return DEVPAL_PIN(STM_PORTC, 0);
        case KIT_TOUCH:         return DEVPAL_PIN(STM_PORTC, 1);
        case KIT_TILT:          return DEVPAL_PIN(STM_PORTC, 2);
        case KIT_VIBRATION:     return DEVPAL_PIN(STM_PORTC, 3);
        case KIT_ROTARY_ENC:    return DEVPAL_PIN(STM_PORTB, 8);   /* CLK; DT on PB9 */
        case KIT_LDR:           return DEVPAL_PIN(STM_PORTA, 0);
        case KIT_LM35:          return DEVPAL_PIN(STM_PORTA, 1);
        case KIT_SOUND_ANALOG:  return DEVPAL_PIN(STM_PORTA, 2);
        default:                return DEVPAL_PIN(STM_PORTE, 0);   /* spare bank */
    }
}

/* ---- electrical facts per module ----
 * button/tilt/vibration/mercury/reed: pull-up style modules, active-LOW
 * touch/hall switch/proximity comparators: active-HIGH digital out
 * mechanical contacts need debounce; comparator outputs are already clean */
dig_in_config_t kit_dig_in_config(kit_module_id_t id, uint8_t pin)
{
    dig_in_config_t c = { pin, DIG_IN_ACTIVE_LOW, 5U };
    switch (id) {
        case KIT_BUTTON: case KIT_TILT: case KIT_MERCURY:
        case KIT_VIBRATION: case KIT_REED_BIG: case KIT_BROKEN_LIGHT:
        case KIT_JOYSTICK_BTN:
            c.active = DIG_IN_ACTIVE_LOW;
            c.debounce_samples = (id == KIT_VIBRATION) ? 2U : 5U;
            break;
        case KIT_TOUCH: case KIT_HALL_SWITCH: case KIT_MIC_SOUND:
            c.active = DIG_IN_ACTIVE_HIGH;
            c.debounce_samples = 0U;   /* comparator/IC output is clean */
            break;
        case KIT_IR_PROXIMITY: case KIT_OBSTACLE: case KIT_LINE:
        case KIT_FLAME: case KIT_KNOCK: case KIT_REED_RGB:
            /* LM393 comparator modules: output LOW when triggered */
            c.active = DIG_IN_ACTIVE_LOW;
            c.debounce_samples = 0U;
            break;
        default:
            break;
    }
    return c;
}

analog_in_config_t kit_analog_config(kit_module_id_t id, uint8_t adc_channel)
{
    /* scale to engineering units in integer math, 12-bit ADC, 3.3V ref */
    analog_in_config_t c = { adc_channel, 330000, 40950, 0 };  /* centi-deg C for LM35 */
    switch (id) {
        case KIT_LM35: case KIT_LM35_B:
            c.scale_num = 330000; c.scale_den = 40950; c.offset = 0;
            break;
        case KIT_JOYSTICK:
            /* permille of travel: raw x 1000 / 4095 */
            c.scale_num = 1000; c.scale_den = 4095; c.offset = 0;
            break;
        case KIT_LDR: case KIT_MAGIC_CUP:
            /* permille of full-scale illumination (relative, uncalibrated) */
            c.scale_num = 1000; c.scale_den = 4095; c.offset = 0;
            break;
        case KIT_HALL_LINEAR: case KIT_HALL_LINEAR_B:
            /* millivolts — field conversion needs the specific 49E sensitivity
             * calibration; mV is the honest engineering unit at this layer */
            c.scale_num = 3300; c.scale_den = 4095; c.offset = 0;
            break;
        case KIT_SOUND_ANALOG: case KIT_HEARTBEAT:
            c.scale_num = 3300; c.scale_den = 4095; c.offset = 0;   /* mV envelope */
            break;
        default:
            break;
    }
    return c;
}

dig_out_config_t kit_dig_out_config(kit_module_id_t id, uint8_t pin)
{
    /* THE safety-critical row: relay is active-LOW per the spec sheet */
    dig_out_config_t c = { pin, DIG_OUT_ACTIVE_HIGH };
    if (id == KIT_RELAY) c.active = DIG_OUT_ACTIVE_LOW;
    return c;
}
