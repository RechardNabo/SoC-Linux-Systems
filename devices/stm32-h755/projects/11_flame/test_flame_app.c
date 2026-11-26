/* test_flame_app.c — 3 tests pinning the event-counting contract (STM32).
 * Input injection is per-port IDR; direction check reads the MODER 2-bit field. */
#include "unity.h"
#include "xc.h"
#include "flame_app.h"
#include "../../drivers/devices/kit/kit.h"

static flame_app_t app;
static dig_in_config_t cfg;
static uint8_t pin;

void setUp(void)
{
    mock_sfr_reset();
    pin = kit_default_pin(KIT_FLAME);
    cfg = kit_dig_in_config(KIT_FLAME, pin);
    flame_app_init(&app, pin);
}
void tearDown(void) {}

static volatile uint32_t *idr_reg(unsigned port)
{
    switch (port) {
        case 0: return &GPIOA_IDR;
        case 1: return &GPIOB_IDR;
        case 2: return &GPIOC_IDR;
        case 3: return &GPIOD_IDR;
        case 4: return &GPIOE_IDR;
        case 5: return &GPIOF_IDR;
        case 6: return &GPIOG_IDR;
        default: return &GPIOH_IDR;
    }
}

static volatile uint32_t *moder_reg(unsigned port)
{
    switch (port) {
        case 0: return &GPIOA_MODER;
        case 1: return &GPIOB_MODER;
        case 2: return &GPIOC_MODER;
        case 3: return &GPIOD_MODER;
        case 4: return &GPIOE_MODER;
        case 5: return &GPIOF_MODER;
        case 6: return &GPIOG_MODER;
        default: return &GPIOH_MODER;
    }
}

static void drive_active(bool on)
{
    volatile uint32_t *reg = idr_reg((unsigned)(pin >> 4));
    const uint32_t mask = 1UL << (pin & 0x0FU);
    const bool high = (cfg.active == DIG_IN_ACTIVE_HIGH) ? on : !on;
    if (high) *reg |= mask; else *reg &= ~mask;
}

static void settle(int ticks)
{
    int i;
    for (i = 0; i < ticks; i++) (void)flame_app_step(&app);
}

static void test_init_is_clean(void)
{
    const unsigned shift = (unsigned)(pin & 0x0FU) * 2U;
    TEST_ASSERT_EQUAL_UINT32(0U, flame_app_events(&app));
    /* MODER 2-bit field 00 = input */
    TEST_ASSERT_EQUAL_HEX32(0U, (*moder_reg((unsigned)(pin >> 4)) >> shift) & 0x3U);
}

static void test_one_activation_counts_once_even_when_held(void)
{
    drive_active(true);
    settle(12);
    TEST_ASSERT_EQUAL_UINT32(1U, flame_app_events(&app));
    settle(20);
    TEST_ASSERT_EQUAL_UINT32(1U, flame_app_events(&app));
}

static void test_release_and_reactivation_counts_again(void)
{
    drive_active(true);
    settle(12);
    drive_active(false);
    settle(12);
    drive_active(true);
    settle(12);
    TEST_ASSERT_EQUAL_UINT32(2U, flame_app_events(&app));
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_init_is_clean);
    RUN_TEST(test_one_activation_counts_once_even_when_held);
    RUN_TEST(test_release_and_reactivation_counts_again);
    return UNITY_END();
}
#endif
