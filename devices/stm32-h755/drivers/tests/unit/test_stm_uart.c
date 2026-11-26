/* test_stm_uart.c — BRR direct divisor + config-while-disabled order. */
#include "unity.h"
#include "xc.h"
#include "../../peripherals/uart/stm_uart.h"

void setUp(void) { mock_sfr_reset(); }
void tearDown(void) {}

static stm_uart_config_t cfg115200(void)
{
    stm_uart_config_t c;
    c.clk_hz = 250000000UL;
    c.baud = 115200UL;
    c.parity = STM_UART_PARITY_NONE;
    c.stop_bits = 1U;
    return c;
}

static void test_brr_direct_divisor(void)
{
    stm_uart_config_t c = cfg115200();
    TEST_ASSERT_EQUAL(STM_UART_STATUS_OK, stm_uart_init(STM_USART1, &c));
    /* 250e6/115200 = 2170.1 -> 2170 */
    TEST_ASSERT_EQUAL_HEX32(2170U, U1BRR);
}

static void test_cr1_enable_last_with_te_re(void)
{
    stm_uart_config_t c = cfg115200();
    stm_uart_init(STM_USART1, &c);
    TEST_ASSERT_EQUAL_HEX32(1U | (1UL << 2) | (1UL << 3), U1CR1);
}

static void test_odd_parity_two_stop(void)
{
    stm_uart_config_t c = cfg115200();
    c.parity = STM_UART_PARITY_ODD;
    c.stop_bits = 2U;
    stm_uart_init(STM_USART2, &c);
    TEST_ASSERT_EQUAL_HEX32(1U | (1UL << 2) | (1UL << 3) | (1UL << 10) | (1UL << 9), U2CR1);
    TEST_ASSERT_EQUAL_HEX32(2UL << 12, U2CR2);
}

static void test_write_read_isr_gating(void)
{
    uint8_t out = 0U;
    stm_uart_config_t c = cfg115200();
    stm_uart_init(STM_USART3, &c);
    U3ISR = 0U;
    TEST_ASSERT_FALSE(stm_uart_write_byte(STM_USART3, 0x55U));
    TEST_ASSERT_FALSE(stm_uart_read_byte(STM_USART3, &out));
    U3ISR = (1UL << 7) | (1UL << 5);
    U3RDR = 0xA5U;
    TEST_ASSERT_TRUE(stm_uart_write_byte(STM_USART3, 0x55U));
    TEST_ASSERT_EQUAL_HEX32(0x55U, U3TDR);
    TEST_ASSERT_TRUE(stm_uart_read_byte(STM_USART3, &out));
    TEST_ASSERT_EQUAL_HEX8(0xA5U, out);
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_brr_direct_divisor);
    RUN_TEST(test_cr1_enable_last_with_te_re);
    RUN_TEST(test_odd_parity_two_stop);
    RUN_TEST(test_write_read_isr_gating);
    return UNITY_END();
}
#endif
