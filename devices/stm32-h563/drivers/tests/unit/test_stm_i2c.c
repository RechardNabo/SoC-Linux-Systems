/* test_stm_i2c.c — TIMINGR packing + PE-ordering, bit-exact. */
#include "unity.h"
#include "xc.h"
#include "../../peripherals/i2c/stm_i2c.h"

void setUp(void) { mock_sfr_reset(); }
void tearDown(void) {}

static void test_timing_400k_at_250mhz(void)
{
    stm_i2c_timing_t t;
    TEST_ASSERT_EQUAL(STM_I2C_STATUS_OK, stm_i2c_compute_timing(250000000UL, 400000UL, &t));
    /* presc0 base=625 too big; presc1 base=312 fits: half 156 -> counts 155 */
    TEST_ASSERT_EQUAL_UINT32(1U, t.presc);
    TEST_ASSERT_EQUAL_UINT32(155U, t.sclh);
    TEST_ASSERT_EQUAL_UINT32(155U, t.scll);
    TEST_ASSERT_EQUAL_UINT32(4U, t.scldel);
    TEST_ASSERT_EQUAL_UINT32(2U, t.sdadel);
}

static void test_timingr_field_positions(void)
{
    stm_i2c_timing_t t = { 1U, 4U, 2U, 155U, 155U };
    TEST_ASSERT_EQUAL_HEX32(155U | (155UL << 8) | (2UL << 16) | (4UL << 20) | (1UL << 28),
                            stm_i2c_pack_timingr(&t));
}

static void test_init_writes_timingr_while_disabled_enables_last(void)
{
    stm_i2c_config_t c;
    c.clk_hz = 250000000UL;
    c.clock_hz = 400000UL;
    TEST_ASSERT_EQUAL(STM_I2C_STATUS_OK, stm_i2c_init(STM_I2C1, &c));
    TEST_ASSERT_EQUAL_HEX32(155U | (155UL << 8) | (2UL << 16) | (4UL << 20) | (1UL << 28),
                            I2C1TIMINGR);
    TEST_ASSERT_EQUAL_HEX32(1U, I2C1CR1);
}

static void test_zero_clock_rejected(void)
{
    stm_i2c_config_t c;
    c.clk_hz = 250000000UL;
    c.clock_hz = 0U;
    TEST_ASSERT_EQUAL(STM_I2C_STATUS_INVALID_PARAM, stm_i2c_init(STM_I2C2, &c));
    TEST_ASSERT_EQUAL_HEX32(0U, I2C2CR1);
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_timing_400k_at_250mhz);
    RUN_TEST(test_timingr_field_positions);
    RUN_TEST(test_init_writes_timingr_while_disabled_enables_last);
    RUN_TEST(test_zero_clock_rejected);
    return UNITY_END();
}
#endif
