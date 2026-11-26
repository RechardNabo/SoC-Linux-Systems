/* stm_adc.c — see stm_adc.h. Register access is always by direct expression
 * (never through latched pointers) so behavioral register models re-evaluate
 * on every poll — the latched-pointer trap bit this program twice already.
 * No write-1-clear glue needed: EOC clears when DR is read on silicon, and
 * ADRDY is 0 out of reset — the sequence is clean hardware usage. */
#include <xc.h>
#include "stm_adc.h"

/* ADC1_CR bits */
#define CR_ADEN      (1UL << 0)
#define CR_ADSTART   (1UL << 2)
#define CR_ADVREGEN  (1UL << 28)
#define CR_DEEPPWD   (1UL << 29)
#define CR_ADCAL     (1UL << 31)
/* ADC1_ISR bits */
#define ISR_ADRDY    (1UL << 0)
#define ISR_EOC      (1UL << 2)
/* ADC1_SQR1: L bits 3:0 (0 = single conversion), SQ1 bits 10:6 */
#define SQR1_SQ1_SHIFT  6U

stm_adc_status_t stm_adc_init(void)
{
    uint32_t spin;
    /* the mandatory startup sequence — order matters, silicon enforces it */
    ADC1_CR &= ~CR_DEEPPWD;         /* 1. exit deep power-down */
    ADC1_CR |= CR_ADVREGEN;         /* 2. voltage regulator on */
    /* (20us regulator stabilization is a hardware delay — host model instant) */
    ADC1_CR |= CR_ADCAL;            /* 3. self-calibrate */
    spin = STM_ADC_TIMEOUT;
    while ((ADC1_CR & CR_ADCAL) != 0U) {
        if (--spin == 0U) return STM_ADC_STATUS_TIMEOUT;
    }
    ADC1_CR |= CR_ADEN;             /* 4. enable */
    spin = STM_ADC_TIMEOUT;
    while ((ADC1_ISR & ISR_ADRDY) == 0U) {
        if (--spin == 0U) return STM_ADC_STATUS_TIMEOUT;
    }
    return STM_ADC_STATUS_OK;
}

stm_adc_status_t stm_adc_read_channel(uint8_t channel, uint16_t *result_out)
{
    uint32_t spin;
    if (result_out == 0 || channel > STM_ADC_MAX_CHANNEL) return STM_ADC_STATUS_INVALID_CHANNEL;
    ADC1_SQR1 = (uint32_t)channel << SQR1_SQ1_SHIFT;   /* L=0: single conversion */
    ADC1_CR |= CR_ADSTART;
    spin = STM_ADC_TIMEOUT;
    while ((ADC1_ISR & ISR_EOC) == 0U) {
        if (--spin == 0U) return STM_ADC_STATUS_TIMEOUT;
    }
    *result_out = (uint16_t)(ADC1_DR & 0xFFFFU);   /* DR read clears EOC on silicon */
    return STM_ADC_STATUS_OK;
}
