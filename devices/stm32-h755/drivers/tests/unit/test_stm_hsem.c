/* test_stm_hsem.c — host tests, STM32H755. */
#include "unity.h"
#include "xc.h"

#include "../../peripherals/hsem/stm_hsem.h"

void setUp(void)    { mock_sfr_reset(); }
void tearDown(void) {}

#define LOCK  (1UL << 31)

void test_take_free_semaphore_packs_fields(void)
{
    TEST_ASSERT_EQUAL(STM_HSEM_STATUS_OK, stm_hsem_take(5U, 0x42U, 0x3U));
    /* LOCK bit31, COREID at 11:8, PROCID at 7:0 — bit-exact positions */
    TEST_ASSERT_EQUAL_HEX32(LOCK | (0x3UL << 8) | 0x42U, HSEM_R[5]);
}

void test_verify_reads_back_ownership(void)
{
    stm_hsem_take(5U, 0x42U, 0x3U);
    TEST_ASSERT_TRUE(stm_hsem_is_owner(5U, 0x42U, 0x3U));
    TEST_ASSERT_FALSE(stm_hsem_is_owner(5U, 0x42U, 0x1U));   /* wrong core */
    TEST_ASSERT_FALSE(stm_hsem_is_owner(5U, 0x99U, 0x3U));   /* wrong process */
}

void test_foreign_owner_take_is_busy_without_clobbering(void)
{
    /* the other core (CM4=1) holds it first */
    stm_hsem_take(5U, 0x10U, 0x1U);
    /* CM7 attempt must fail AND leave the foreign ownership intact —
     * the pre-check exists so we never even write */
    TEST_ASSERT_EQUAL(STM_HSEM_STATUS_BUSY, stm_hsem_take(5U, 0x20U, 0x3U));
    TEST_ASSERT_TRUE(stm_hsem_is_owner(5U, 0x10U, 0x1U));
}

void test_same_owner_retake_is_reentrant_ok(void)
{
    stm_hsem_take(5U, 0x10U, 0x3U);
    TEST_ASSERT_EQUAL(STM_HSEM_STATUS_OK, stm_hsem_take(5U, 0x10U, 0x3U));
}

void test_release_clears_lock(void)
{
    stm_hsem_take(5U, 0x42U, 0x3U);
    TEST_ASSERT_EQUAL(STM_HSEM_STATUS_OK, stm_hsem_release(5U, 0x42U, 0x3U));
    TEST_ASSERT_EQUAL_HEX32(0U, HSEM_R[5] & LOCK);
    /* and now the other core CAN take it */
    TEST_ASSERT_EQUAL(STM_HSEM_STATUS_OK, stm_hsem_take(5U, 0x20U, 0x1U));
}

void test_release_without_ownership_rejected(void)
{
    stm_hsem_take(5U, 0x10U, 0x1U);   /* CM4 owns */
    TEST_ASSERT_EQUAL(STM_HSEM_STATUS_NOT_OWNER, stm_hsem_release(5U, 0x10U, 0x3U));
}

void test_invalid_semaphore_rejected(void)
{
    TEST_ASSERT_EQUAL(STM_HSEM_STATUS_INVALID_SEM, stm_hsem_take(32U, 0U, 0x3U));
    TEST_ASSERT_EQUAL(STM_HSEM_STATUS_INVALID_SEM, stm_hsem_release(32U, 0U, 0x3U));
}

void test_owner_inspection_reports_packing(void)
{
    stm_hsem_take(7U, 0x42U, 0x3U);
    TEST_ASSERT_EQUAL_HEX16((0x3U << 8) | 0x42U, stm_hsem_owner(7U));
    TEST_ASSERT_EQUAL_HEX16(0U, stm_hsem_owner(8U));   /* free = 0 */
}

#if defined(UNIT_TEST_HOST_STANDALONE) || defined(UNIT_TEST_HOST)
int main(void)
{
    UnityBegin("test_stm_hsem.c");
    RUN_TEST(test_take_free_semaphore_packs_fields);
    RUN_TEST(test_verify_reads_back_ownership);
    RUN_TEST(test_foreign_owner_take_is_busy_without_clobbering);
    RUN_TEST(test_same_owner_retake_is_reentrant_ok);
    RUN_TEST(test_release_clears_lock);
    RUN_TEST(test_release_without_ownership_rejected);
    RUN_TEST(test_invalid_semaphore_rejected);
    RUN_TEST(test_owner_inspection_reports_packing);
    return UnityEnd();
}
#endif
