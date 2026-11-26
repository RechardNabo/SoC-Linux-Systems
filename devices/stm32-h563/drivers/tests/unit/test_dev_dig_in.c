/* test_dev_dig_in.c — host tests, STM32H563 device layer. */
#include "unity.h"
#include "xc.h"

#include "../../devices/dig_in/dig_in.h"
#include "../../devices/pal/devpal.h"

#define BTN_PIN  DEVPAL_PIN(STM_PORTC, 0)

void setUp(void)    { mock_sfr_reset(); }
void tearDown(void) {}

void test_active_low_button_debounces(void)
{
    dig_in_t d;
    dig_in_config_t c = { BTN_PIN, DIG_IN_ACTIVE_LOW, 3U };
    TEST_ASSERT_EQUAL(DIG_IN_STATUS_OK, dig_in_init(&d, &c));
    TEST_ASSERT_EQUAL_HEX32(0x0000U, GPIOC_MODER & 0x0003U);   /* input mode 00 */
    GPIOC_IDR |= 0x0001U;
    dig_in_sample(&d);
    TEST_ASSERT_FALSE(dig_in_state(&d));
    GPIOC_IDR &= ~0x0001U;
    dig_in_sample(&d);
    TEST_ASSERT_FALSE(dig_in_state(&d));
    dig_in_sample(&d);
    TEST_ASSERT_FALSE(dig_in_state(&d));
    dig_in_sample(&d);
    TEST_ASSERT_TRUE(dig_in_state(&d));
}

void test_noise_spike_rejected(void)
{
    dig_in_t d;
    dig_in_config_t c = { BTN_PIN, DIG_IN_ACTIVE_LOW, 3U };
    dig_in_init(&d, &c);
    GPIOC_IDR |= 0x0001U;
    dig_in_sample(&d); dig_in_sample(&d); dig_in_sample(&d);
    GPIOC_IDR &= ~0x0001U;
    dig_in_sample(&d);
    GPIOC_IDR |= 0x0001U;
    dig_in_sample(&d);
    TEST_ASSERT_FALSE(dig_in_state(&d));
}

void test_active_high_immediate(void)
{
    dig_in_t d;
    dig_in_config_t c = { DEVPAL_PIN(STM_PORTC, 1), DIG_IN_ACTIVE_HIGH, 0U };
    dig_in_init(&d, &c);
    GPIOC_IDR |= 0x0002U;
    dig_in_sample(&d);
    TEST_ASSERT_TRUE(dig_in_state(&d));
}

#if defined(UNIT_TEST_HOST_STANDALONE) || defined(UNIT_TEST_HOST)
int main(void)
{
    UnityBegin("test_dev_dig_in.c");
    RUN_TEST(test_active_low_button_debounces);
    RUN_TEST(test_noise_spike_rejected);
    RUN_TEST(test_active_high_immediate);
    return UnityEnd();
}
#endif
