/* test_ir_receiver_app.c — 3 tests pinning the HONEST unsupported contract.
 * When PIO capture lands these get replaced with real decode tests — until
 * then they guarantee the project fails loudly, never silently. */
#include "unity.h"
#include "ir_receiver_app.h"

void setUp(void) {}
void tearDown(void) {}

static void test_reports_unsupported(void)
{
    TEST_ASSERT_FALSE(ir_receiver_supported());
}

static void test_init_status_is_explicit(void)
{
    TEST_ASSERT_EQUAL(IR_STATUS_UNSUPPORTED, ir_receiver_init_status());
}

static void test_decode_never_returns_garbage(void)
{
    TEST_ASSERT_EQUAL_INT(-1, ir_receiver_decode(0));
    TEST_ASSERT_EQUAL_INT(-1, ir_receiver_decode(67));
}

#ifndef UNIT_TEST_NO_MAIN
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_reports_unsupported);
    RUN_TEST(test_init_status_is_explicit);
    RUN_TEST(test_decode_never_returns_garbage);
    return UNITY_END();
}
#endif
