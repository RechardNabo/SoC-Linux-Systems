/* test_dev_analog_in.c — host tests, STM32H563 device layer. */
#include "unity.h"
#include "xc.h"

#include "../../devices/analog_in/analog_in.h"
#include "../../devices/kit/kit.h"

void setUp(void)    { mock_sfr_reset(); }
void tearDown(void) {}

void test_lm35_scaling_exact_12bit(void)
{
    analog_in_t s;
    analog_in_config_t c = kit_analog_config(KIT_LM35, 0U);
    int32_t centic = 0;
    TEST_ASSERT_EQUAL(STM_ADC_STATUS_OK, stm_adc_init());
    TEST_ASSERT_EQUAL(ANALOG_IN_STATUS_OK, analog_in_init(&s, &c));
    ADC1_DR = 124U;   /* 12-bit: 124*330000/40950 = 999 centi */
    TEST_ASSERT_EQUAL(ANALOG_IN_STATUS_OK, analog_in_read_scaled(&s, &centic));
    TEST_ASSERT_EQUAL_INT32(999, centic);
}

void test_joystick_permille_full_scale(void)
{
    analog_in_t s;
    analog_in_config_t c = kit_analog_config(KIT_JOYSTICK, 0U);
    int32_t permille = 0;
    stm_adc_init();
    analog_in_init(&s, &c);
    ADC1_DR = 4095U;
    analog_in_read_scaled(&s, &permille);
    TEST_ASSERT_EQUAL_INT32(1000, permille);
}

void test_invalid_channel_rejected(void)
{
    analog_in_t s;
    analog_in_config_t c = { 20U, 1, 1, 0 };   /* H5: channels 0-19 */
    TEST_ASSERT_EQUAL(ANALOG_IN_STATUS_INVALID_CONFIG, analog_in_init(&s, &c));
}

#if defined(UNIT_TEST_HOST_STANDALONE) || defined(UNIT_TEST_HOST)
int main(void)
{
    UnityBegin("test_dev_analog_in.c");
    RUN_TEST(test_lm35_scaling_exact_12bit);
    RUN_TEST(test_joystick_permille_full_scale);
    RUN_TEST(test_invalid_channel_rejected);
    return UnityEnd();
}
#endif
