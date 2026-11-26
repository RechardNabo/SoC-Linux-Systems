/* test_stm_spi.c — power-of-two baud quantization honest, bit-exact. */
#include "unity.h"
#include "xc.h"
#include "../../peripherals/spi/stm_spi.h"

void setUp(void) { mock_sfr_reset(); }
void tearDown(void) {}

static stm_spi_config_t cfg10m(void)
{
    stm_spi_config_t c;
    c.clk_hz = 250000000UL;
    c.clock_hz = 10000000UL;
    c.mode = STM_SPI_MODE_0;
    return c;
}

static void test_mbr_power_of_two_never_overclocks(void)
{
    /* 250e6/2^5 = 7.8125MHz <= 10MHz -> mbr 4; /2^4=15.6MHz would overclock */
    TEST_ASSERT_EQUAL_UINT32(4U, stm_spi_mbr(250000000UL, 10000000UL));
    TEST_ASSERT_EQUAL_UINT32(7812500U, stm_spi_actual_clock(250000000UL, 4U));
}

static void test_init_dsize8_mbr_enable_last(void)
{
    stm_spi_config_t c = cfg10m();
    TEST_ASSERT_EQUAL(STM_SPI_STATUS_OK, stm_spi_init(STM_SPI1, &c));
    TEST_ASSERT_EQUAL_HEX32(7U | (4UL << 28), SPI1CFG1);
    TEST_ASSERT_EQUAL_HEX32(1UL << 22, SPI1CFG2);
    TEST_ASSERT_EQUAL_HEX32(1U, SPI1CR1);
}

static void test_mode3_cpol_cpha_bits(void)
{
    stm_spi_config_t c = cfg10m();
    c.mode = STM_SPI_MODE_3;
    stm_spi_init(STM_SPI2, &c);
    TEST_ASSERT_EQUAL_HEX32((1UL << 22) | (1UL << 24) | (1UL << 25), SPI2CFG2);
}

static void test_exchange_and_timeout(void)
{
    stm_spi_config_t c = cfg10m();
    uint8_t rx = 0U;
    stm_spi_init(STM_SPI1, &c);
    SPI1SR = (1UL << 1) | (1UL << 0);   /* TXP + RXP */
    SPI1RXDR = 0x5AU;
    TEST_ASSERT_EQUAL(STM_SPI_STATUS_OK, stm_spi_exchange_byte(STM_SPI1, 0x5AU, &rx));
    TEST_ASSERT_EQUAL_HEX8(0x5AU, rx);
    SPI1SR = 0U;
    TEST_ASSERT_EQUAL(STM_SPI_STATUS_TIMEOUT, stm_spi_exchange_byte(STM_SPI1, 0U, 0));
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_mbr_power_of_two_never_overclocks);
    RUN_TEST(test_init_dsize8_mbr_enable_last);
    RUN_TEST(test_mode3_cpol_cpha_bits);
    RUN_TEST(test_exchange_and_timeout);
    return UNITY_END();
}
#endif
