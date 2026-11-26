/* test_dev_quad_enc.c — host tests, STM32H563 device layer. */
#include "unity.h"
#include "xc.h"

#include "../../devices/quad_enc/quad_enc.h"
#include "../../devices/pal/devpal.h"

void setUp(void)    { mock_sfr_reset(); }
void tearDown(void) {}

static void set_enc(uint8_t ab)
{
    GPIOB_IDR = (GPIOB_IDR & ~0x0300U)
              | ((ab & 0x02U) ? 0x0100U : 0U)
              | ((ab & 0x01U) ? 0x0200U : 0U);
}

void test_full_detent_cycle_counts_four_steps(void)
{
    quad_enc_t q;
    quad_enc_config_t c = { DEVPAL_PIN(STM_PORTB, 8), DEVPAL_PIN(STM_PORTB, 9), 1 };
    const uint8_t cw[5] = { 0x00U, 0x01U, 0x03U, 0x02U, 0x00U };
    int i;
    TEST_ASSERT_EQUAL(QUAD_ENC_STATUS_OK, quad_enc_init(&q, &c));
    set_enc(cw[0]);
    quad_enc_sample(&q);
    for (i = 1; i < 5; i++) {
        set_enc(cw[i]);
        quad_enc_sample(&q);
    }
    TEST_ASSERT_EQUAL_INT32(4, quad_enc_count(&q));
    TEST_ASSERT_EQUAL_INT32(1, quad_enc_detents(&q));
}

void test_two_bit_jump_is_noise_rejected(void)
{
    quad_enc_t q;
    quad_enc_config_t c = { DEVPAL_PIN(STM_PORTB, 8), DEVPAL_PIN(STM_PORTB, 9), 1 };
    quad_enc_init(&q, &c);
    set_enc(0x00U);
    quad_enc_sample(&q);
    set_enc(0x03U);
    quad_enc_sample(&q);
    TEST_ASSERT_EQUAL_INT32(0, quad_enc_count(&q));
}

void test_ccw_counts_negative(void)
{
    quad_enc_t q;
    quad_enc_config_t c = { DEVPAL_PIN(STM_PORTB, 8), DEVPAL_PIN(STM_PORTB, 9), 1 };
    const uint8_t ccw[5] = { 0x00U, 0x02U, 0x03U, 0x01U, 0x00U };
    int i;
    quad_enc_init(&q, &c);
    set_enc(ccw[0]);
    quad_enc_sample(&q);
    for (i = 1; i < 5; i++) {
        set_enc(ccw[i]);
        quad_enc_sample(&q);
    }
    TEST_ASSERT_EQUAL_INT32(-4, quad_enc_count(&q));
}

#if defined(UNIT_TEST_HOST_STANDALONE) || defined(UNIT_TEST_HOST)
int main(void)
{
    UnityBegin("test_dev_quad_enc.c");
    RUN_TEST(test_full_detent_cycle_counts_four_steps);
    RUN_TEST(test_two_bit_jump_is_noise_rejected);
    RUN_TEST(test_ccw_counts_negative);
    return UnityEnd();
}
#endif
