/* test_dev_kit.c — host tests, STM32H563 device layer. */
#include "unity.h"
#include "xc.h"

#include "../../devices/kit/kit.h"

void setUp(void)    { mock_sfr_reset(); }
void tearDown(void) {}

void test_every_module_id_has_info(void)
{
    int id;
    for (id = 1; id <= 35; id++) {
        TEST_ASSERT_NOT_NULL(kit_info((kit_module_id_t)id));
    }
}

void test_relay_active_low_fact_baked_in(void)
{
    const dig_out_config_t c = kit_dig_out_config(KIT_RELAY, 0x30U);
    TEST_ASSERT_TRUE(kit_info(KIT_RELAY)->module_needs_5v);
    TEST_ASSERT_EQUAL(DIG_OUT_ACTIVE_LOW, c.active);
}

void test_onewire_modules_unsupported_this_pass(void)
{
    TEST_ASSERT_EQUAL(KIT_CLASS_UNSUPPORTED, kit_info(KIT_DHT11)->cls);
    TEST_ASSERT_EQUAL(KIT_CLASS_UNSUPPORTED, kit_info(KIT_DS18B20)->cls);
    TEST_ASSERT_EQUAL(KIT_CLASS_UNSUPPORTED, kit_info(KIT_IR_RECEIVER)->cls);
}

void test_lm35_scaling_uses_12bit_denominator(void)
{
    const analog_in_config_t c = kit_analog_config(KIT_LM35, 0U);
    TEST_ASSERT_EQUAL_UINT32(40950U, c.scale_den);
}

#if defined(UNIT_TEST_HOST_STANDALONE) || defined(UNIT_TEST_HOST)
int main(void)
{
    UnityBegin("test_dev_kit.c");
    RUN_TEST(test_every_module_id_has_info);
    RUN_TEST(test_relay_active_low_fact_baked_in);
    RUN_TEST(test_onewire_modules_unsupported_this_pass);
    RUN_TEST(test_lm35_scaling_uses_12bit_denominator);
    return UnityEnd();
}
#endif
