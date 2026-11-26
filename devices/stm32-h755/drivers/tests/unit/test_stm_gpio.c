/* test_stm_gpio.c — MODER 2-bit fields + BSRR atomic semantics, bit-exact. */
#include "unity.h"
#include "xc.h"
#include "../../peripherals/gpio/stm_gpio.h"

void setUp(void) { mock_sfr_reset(); }
void tearDown(void) {}

static void test_output_mode_two_bit_field(void)
{
    TEST_ASSERT_EQUAL(STM_GPIO_STATUS_OK, stm_gpio_set_output(STM_PORTA, 5U));
    TEST_ASSERT_EQUAL_HEX32(1UL << 10, GPIOA_MODER);
}

static void test_mode_change_preserves_other_pins(void)
{
    GPIOA_MODER = 1UL << 0;   /* pin 0 already output */
    stm_gpio_set_output(STM_PORTA, 5U);
    TEST_ASSERT_EQUAL_HEX32((1UL << 0) | (1UL << 10), GPIOA_MODER);
}

static void test_write_high_low_via_bsrr(void)
{
    stm_gpio_write(STM_PORTA, 5U, true);
    TEST_ASSERT_EQUAL_HEX32(1UL << 5, GPIOA_ODR);
    stm_gpio_write(STM_PORTA, 5U, false);
    TEST_ASSERT_EQUAL_HEX32(0U, GPIOA_ODR);
}

static void test_toggle_roundtrip(void)
{
    stm_gpio_write(STM_PORTB, 3U, true);
    stm_gpio_toggle(STM_PORTB, 3U);
    TEST_ASSERT_EQUAL_HEX32(0U, GPIOB_ODR);
    stm_gpio_toggle(STM_PORTB, 3U);
    TEST_ASSERT_EQUAL_HEX32(1UL << 3, GPIOB_ODR);
}

static void test_read_reflects_idr(void)
{
    GPIOC_IDR = 1UL << 13;
    TEST_ASSERT_TRUE(stm_gpio_read(STM_PORTC, 13U));
    TEST_ASSERT_FALSE(stm_gpio_read(STM_PORTC, 12U));
    TEST_ASSERT_EQUAL(STM_GPIO_STATUS_INVALID_PIN, stm_gpio_set_output(STM_PORTA, 16U));
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_output_mode_two_bit_field);
    RUN_TEST(test_mode_change_preserves_other_pins);
    RUN_TEST(test_write_high_low_via_bsrr);
    RUN_TEST(test_toggle_roundtrip);
    RUN_TEST(test_read_reflects_idr);
    return UNITY_END();
}
#endif
