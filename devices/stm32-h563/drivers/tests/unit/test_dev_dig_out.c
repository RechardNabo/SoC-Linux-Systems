/* test_dev_dig_out.c — host tests, STM32H563 device layer. */
#include "unity.h"
#include "xc.h"

#include "../../devices/dig_out/dig_out.h"
#include "../../devices/pal/devpal.h"

#define RELAY_PIN  DEVPAL_PIN(STM_PORTD, 0)

void setUp(void)    { mock_sfr_reset(); }
void tearDown(void) {}

void test_active_low_relay_inactive_at_power_on(void)
{
    dig_out_t r;
    dig_out_config_t c = { RELAY_PIN, DIG_OUT_ACTIVE_LOW };
    TEST_ASSERT_EQUAL(DIG_OUT_STATUS_OK, dig_out_init(&r, &c));
    TEST_ASSERT_EQUAL_HEX32(0x0001U, GPIOD_ODR & 0x0001U);   /* inactive = HIGH */
    TEST_ASSERT_FALSE(dig_out_is_on(&r));
    TEST_ASSERT_EQUAL_HEX32(0x0001U, GPIOD_MODER & 0x0003U);  /* output mode 01 */
}

void test_active_low_set_on_drives_low(void)
{
    dig_out_t r;
    dig_out_config_t c = { RELAY_PIN, DIG_OUT_ACTIVE_LOW };
    dig_out_init(&r, &c);
    dig_out_set(&r, true);
    TEST_ASSERT_EQUAL_HEX32(0x0000U, GPIOD_ODR & 0x0001U);
    TEST_ASSERT_TRUE(dig_out_is_on(&r));
}

void test_active_high_laser(void)
{
    dig_out_t l;
    dig_out_config_t c = { DEVPAL_PIN(STM_PORTD, 2), DIG_OUT_ACTIVE_HIGH };
    dig_out_init(&l, &c);
    dig_out_set(&l, true);
    TEST_ASSERT_EQUAL_HEX32(0x0004U, GPIOD_ODR & 0x0004U);
    dig_out_toggle(&l);
    TEST_ASSERT_EQUAL_HEX32(0x0000U, GPIOD_ODR & 0x0004U);
}

#if defined(UNIT_TEST_HOST_STANDALONE) || defined(UNIT_TEST_HOST)
int main(void)
{
    UnityBegin("test_dev_dig_out.c");
    RUN_TEST(test_active_low_relay_inactive_at_power_on);
    RUN_TEST(test_active_low_set_on_drives_low);
    RUN_TEST(test_active_high_laser);
    return UnityEnd();
}
#endif
