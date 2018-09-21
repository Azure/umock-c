// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifdef __cplusplus
#include <cstdint>
#include <cstdlib>
#else
#include <stdint.h>
#include <stdlib.h>
#endif

#include "testrunnerswitcher.h"
#include "umock_c.h"
#include "umock_c_negative_tests.h"

#define ENABLE_MOCKS
#include "test_dependency.h"

static TEST_MUTEX_HANDLE test_mutex;
static TEST_MUTEX_HANDLE global_mutex;

static void test_on_umock_c_error(UMOCK_C_ERROR_CODE error_code)
{
    (void)error_code;
    ASSERT_FAIL("umock error");
}

BEGIN_TEST_SUITE(umock_c_negative_tests_call_count_int_tests)

TEST_SUITE_INITIALIZE(suite_init)
{
    int result;

    TEST_INITIALIZE_MEMORY_DEBUG(global_mutex);

    test_mutex = TEST_MUTEX_CREATE();
    ASSERT_IS_NOT_NULL(test_mutex);

    result = umock_c_init(test_on_umock_c_error);
    ASSERT_ARE_EQUAL(int, 0, result);
}

TEST_SUITE_CLEANUP(suite_cleanup)
{
    TEST_MUTEX_DESTROY(test_mutex);
    TEST_DEINITIALIZE_MEMORY_DEBUG(global_mutex);
}

TEST_FUNCTION_INITIALIZE(test_function_init)
{
    int mutex_acquire_result = TEST_MUTEX_ACQUIRE(test_mutex);
    ASSERT_ARE_EQUAL(int, 0, mutex_acquire_result);
}

TEST_FUNCTION_CLEANUP(test_function_cleanup)
{
    umock_c_negative_tests_deinit();
    umock_c_reset_all_calls();
    TEST_MUTEX_RELEASE(test_mutex);
}

TEST_FUNCTION(set_cannot_fail)
{
    // arrange
    int negativeTestsInitResult = umock_c_negative_tests_init();
    ASSERT_ARE_EQUAL(int, 0, negativeTestsInitResult);
    
    STRICT_EXPECTED_CALL(void_function_no_args());
    STRICT_EXPECTED_CALL(function_mark_cannot_fail_no_args()).CallCannotFail();
    STRICT_EXPECTED_CALL(void_function_with_args(12));
    STRICT_EXPECTED_CALL(function_default_no_args());
    STRICT_EXPECTED_CALL(function_default_with_args(34));
    STRICT_EXPECTED_CALL(function_mark_cannot_fail_with_args(78)).CallCannotFail();

    umock_c_negative_tests_snapshot();

    ASSERT_ARE_EQUAL_WITH_MSG(int, 0, umock_c_negative_tests_can_call_fail(0), "void_function_no_args indicated it can fail");
    ASSERT_ARE_EQUAL_WITH_MSG(int, 0, umock_c_negative_tests_can_call_fail(1), "function_mark_cannot_fail_no_args indicated it can fail");

    ASSERT_ARE_EQUAL_WITH_MSG(int, 0, umock_c_negative_tests_can_call_fail(2), "void_function_with_args indicated it can fail");
    ASSERT_ARE_EQUAL_WITH_MSG(int, 1, umock_c_negative_tests_can_call_fail(3), "function_default_no_args wrongly indicated it cannot fail");
    ASSERT_ARE_EQUAL_WITH_MSG(int, 1, umock_c_negative_tests_can_call_fail(4), "function_default_with_args wrongly indicated it cannot fail");
    ASSERT_ARE_EQUAL_WITH_MSG(int, 0, umock_c_negative_tests_can_call_fail(5), "function_mark_cannot_fail_with_args indicated it can fail");
}

END_TEST_SUITE(umock_c_negative_tests_call_count_int_tests)
