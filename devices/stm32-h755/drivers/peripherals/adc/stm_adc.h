/* stm_adc.h — ADC driver for STM32H563: single regular conversion,
 * software trigger, polling. Silicon-truthful startup sequence — the
 * classic STM32 ADC trap list, in mandatory order:
 *   1. clear DEEPPWD   (exit deep power-down)
 *   2. set ADVREGEN    (internal voltage regulator on — needs ~20us)
 *   3. self-calibrate  (ADCAL, wait for completion)
 *   4. set ADEN        (enable — wait for ADRDY)
 * Skipping or reordering these is the #1 cause of "ADC returns garbage"
 * on this family. Resolution fixed at 12-bit (max) — scaling is the
 * caller's business. */
#ifndef STM_ADC_H
#define STM_ADC_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    STM_ADC_STATUS_OK = 0,
    STM_ADC_STATUS_INVALID_CHANNEL,
    STM_ADC_STATUS_INVALID_PARAM,
    STM_ADC_STATUS_TIMEOUT
} stm_adc_status_t;

#define STM_ADC_MAX_CHANNEL   19U   /* H5: channels 0-19 incl. internal */
#define STM_ADC_TIMEOUT       100000U

stm_adc_status_t stm_adc_init(void);
stm_adc_status_t stm_adc_read_channel(uint8_t channel, uint16_t *result_out);

#endif
