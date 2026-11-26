/* test_stm_tim.c — PSC/ARR solver + PWM mode encoding, bit-exact. */
#include "unity.h"
#include "xc.h"
#include "../../peripherals/tim/stm_tim.h"

void setUp(void) { mock_sfr_reset(); }
void tearDown(void) {}

static stm_tim_config_t cfg1k(void)
{
    stm_tim_config_t c;
    c.clk_hz = 250000000UL;
    c.frequency = 1000UL;
    return c;
}

static void test_solver_maximizes_resolution(void)
{
    uint32_t psc, arr;
    TEST_ASSERT_TRUE(stm_tim_solve(250000000UL, 1000UL, &psc, &arr));
    /* total 250000: psc3 -> 62500 fits 16-bit; psc 0-2 dont */
    TEST_ASSERT_EQUAL_UINT32(3U, psc);
    TEST_ASSERT_EQUAL_UINT32(62499U, arr);
}

static void test_pwm_init_order_and_mode(void)
{
    stm_tim_config_t c = cfg1k();
    TEST_ASSERT_EQUAL(STM_TIM_STATUS_OK, stm_tim_pwm_init(STM_TIM2, 1U, &c));
    TEST_ASSERT_EQUAL_HEX32(3U, TIM2PSC);
    TEST_ASSERT_EQUAL_HEX32(62499U, TIM2ARR);
    TEST_ASSERT_EQUAL_HEX32(6UL << 4, TIM2CCMR1);   /* PWM mode 1 */
    TEST_ASSERT_EQUAL_HEX32(1U, TIM2CCER);          /* CC1E */
    TEST_ASSERT_EQUAL_HEX32(1U, TIM2EGR);           /* shadow load */
    TEST_ASSERT_EQUAL_HEX32(1U, TIM2CR1);           /* CEN last */
}

static void test_duty_scales_with_arr(void)
{
    stm_tim_config_t c = cfg1k();
    stm_tim_pwm_init(STM_TIM2, 1U, &c);
    TEST_ASSERT_EQUAL(STM_TIM_STATUS_OK, stm_tim_set_duty_permille(STM_TIM2, 1U, 500U));
    TEST_ASSERT_EQUAL_HEX32(31250U, TIM2CCR1);
    stm_tim_set_duty_permille(STM_TIM2, 2U, 250U);
    TEST_ASSERT_EQUAL_HEX32(15625U, TIM2CCR2);
}

static void test_invalid_and_overrange_rejected(void)
{
    stm_tim_config_t c = cfg1k();
    TEST_ASSERT_EQUAL(STM_TIM_STATUS_INVALID_PARAM, stm_tim_pwm_init(STM_TIM3, 0U, &c));
    TEST_ASSERT_EQUAL(STM_TIM_STATUS_INVALID_PARAM, stm_tim_set_duty_permille(STM_TIM3, 1U, 1001U));
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_solver_maximizes_resolution);
    RUN_TEST(test_pwm_init_order_and_mode);
    RUN_TEST(test_duty_scales_with_arr);
    RUN_TEST(test_invalid_and_overrange_rejected);
    return UNITY_END();
}
#endif
