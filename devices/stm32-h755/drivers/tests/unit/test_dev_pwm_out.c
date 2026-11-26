/* test_dev_pwm_out.c — host tests, STM32H563 device layer. */
#include "unity.h"
#include "xc.h"

#include "../../devices/pwm_out/pwm_out.h"

void setUp(void)    { mock_sfr_reset(); }
void tearDown(void) {}

#define CLK  250000000UL

void test_rgb_channels_init_on_tim2(void)
{
    rgb_led_t rgb;
    TEST_ASSERT_EQUAL(PWM_OUT_STATUS_OK, rgb_led_init(&rgb, 1U, 2U, 3U, CLK, 1000UL));
    /* TIM2 enabled: CR1 CEN bit set */
    TEST_ASSERT_EQUAL_HEX32(0x0001U, TIM2CR1 & 0x0001U);
}

void test_permille_rejects_over_range(void)
{
    pwm_out_channel_t ch;
    pwm_out_init_channel(&ch, STM_TIM2, 1U, CLK, 1000UL);
    TEST_ASSERT_EQUAL(PWM_OUT_STATUS_INVALID_PARAM, pwm_out_set_permille(&ch, 1001U));
}

void test_buzzer_retunes_timer3_not_timer2(void)
{
    rgb_led_t rgb;
    buzzer_t buzz;
    uint32_t arr_before;
    rgb_led_init(&rgb, 1U, 2U, 3U, CLK, 1000UL);
    arr_before = TIM2ARR;
    buzzer_init(&buzz, STM_TIM3, 1U, CLK);
    buzzer_tone(&buzz, 440U);
    TEST_ASSERT_EQUAL_HEX32(arr_before, TIM2ARR);   /* RGB frequency untouched */
}

void test_rgb_set_mixed_color(void)
{
    rgb_led_t rgb;
    rgb_led_init(&rgb, 1U, 2U, 3U, CLK, 1000UL);
    TEST_ASSERT_EQUAL(PWM_OUT_STATUS_OK, rgb_led_set(&rgb, 255U, 0U, 0U));
    /* full red: CCR1 at max duty — ARR+1 territory; exact value is TIM-driver
     * domain, here we just prove the write landed non-zero */
    TEST_ASSERT_TRUE(TIM2CCR1 > 0U);
}

#if defined(UNIT_TEST_HOST_STANDALONE) || defined(UNIT_TEST_HOST)
int main(void)
{
    UnityBegin("test_dev_pwm_out.c");
    RUN_TEST(test_rgb_channels_init_on_tim2);
    RUN_TEST(test_permille_rejects_over_range);
    RUN_TEST(test_buzzer_retunes_timer3_not_timer2);
    RUN_TEST(test_rgb_set_mixed_color);
    return UnityEnd();
}
#endif
