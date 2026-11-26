/* test_rotary_encoder_app.c — 3 tests: bounded position contract (STM32). */
#include "unity.h"
#include "xc.h"
#include "rotary_encoder_app.h"
#include "../../drivers/devices/pal/devpal.h"

#define ENC_A   DEVPAL_PIN(STM_PORTB, 8)
#define ENC_B   DEVPAL_PIN(STM_PORTB, 9)
#define ENC_BTN DEVPAL_PIN(STM_PORTC, 6)

static rotary_encoder_app_t app;

void setUp(void)
{
    mock_sfr_reset();
    rotary_encoder_app_init(&app, ENC_A, ENC_B, ENC_BTN);
    GPIOC_IDR |= 0x0040UL;   /* button released (active-low) */
}
void tearDown(void) {}

static void test_position_zero_at_init(void)
{
    TEST_ASSERT_EQUAL_INT32(0, rotary_encoder_app_position(&app));
}

static void test_idle_input_never_moves_position(void)
{
    int i;
    for (i = 0; i < 50; i++) rotary_encoder_app_step(&app);
    TEST_ASSERT_EQUAL_INT32(0, rotary_encoder_app_position(&app));
}

static void test_button_reset_returns_position_to_zero(void)
{
    int i;
    app.position = 42;
    GPIOC_IDR &= ~0x0040UL;   /* pressed: pin reads low */
    for (i = 0; i < 10; i++) rotary_encoder_app_step(&app);
    TEST_ASSERT_EQUAL_INT32(0, rotary_encoder_app_position(&app));
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_position_zero_at_init);
    RUN_TEST(test_idle_input_never_moves_position);
    RUN_TEST(test_button_reset_returns_position_to_zero);
    return UNITY_END();
}
#endif
