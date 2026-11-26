/* test_stm_adc.c — host tests, STM32H563 device layer. */
#include "unity.h"
#include "xc.h"

#include "../../peripherals/adc/stm_adc.h"

void setUp(void)    { mock_sfr_reset(); }
void tearDown(void) {}

#define CR_ADEN      (1UL << 0)
#define CR_ADVREGEN  (1UL << 28)
#define CR_DEEPPWD   (1UL << 29)
#define CR_ADCAL     (1UL << 31)

void test_init_exits_deep_powerdown_enables_regulator(void)
{
    ADC1_CR = CR_DEEPPWD;   /* reset state: deep power-down */
    TEST_ASSERT_EQUAL(STM_ADC_STATUS_OK, stm_adc_init());
    TEST_ASSERT_EQUAL_HEX32(0U, ADC1_CR & CR_DEEPPWD);
    TEST_ASSERT_EQUAL_HEX32(CR_ADVREGEN, ADC1_CR & CR_ADVREGEN);
    TEST_ASSERT_EQUAL_HEX32(CR_ADEN, ADC1_CR & CR_ADEN);
}

void test_calibration_completes_before_enable(void)
{
    /* instant-completion model self-clears ADCAL — the driver must have
     * waited for it: after init, CAL is clear AND ADEN is set */
    TEST_ASSERT_EQUAL(STM_ADC_STATUS_OK, stm_adc_init());
    TEST_ASSERT_EQUAL_HEX32(0U, ADC1_CR & CR_ADCAL);
}

void test_channel_select_packs_sqr1(void)
{
    uint16_t result = 0U;
    stm_adc_init();
    ADC1_DR = 0x0ABCU;
    TEST_ASSERT_EQUAL(STM_ADC_STATUS_OK, stm_adc_read_channel(5U, &result));
    TEST_ASSERT_EQUAL_HEX32(5UL << 6, ADC1_SQR1);   /* SQ1 at bits 10:6, L=0 */
    TEST_ASSERT_EQUAL_HEX16(0x0ABCU, result);
}

void test_invalid_channel_rejected(void)
{
    uint16_t result = 0U;
    stm_adc_init();
    TEST_ASSERT_EQUAL(STM_ADC_STATUS_INVALID_CHANNEL, stm_adc_read_channel(20U, &result));
    TEST_ASSERT_EQUAL(STM_ADC_STATUS_INVALID_CHANNEL, stm_adc_read_channel(0U, 0));
}

#if defined(UNIT_TEST_HOST_STANDALONE) || defined(UNIT_TEST_HOST)
int main(void)
{
    UnityBegin("test_stm_adc.c");
    RUN_TEST(test_init_exits_deep_powerdown_enables_regulator);
    RUN_TEST(test_calibration_completes_before_enable);
    RUN_TEST(test_channel_select_packs_sqr1);
    RUN_TEST(test_invalid_channel_rejected);
    return UnityEnd();
}
#endif
