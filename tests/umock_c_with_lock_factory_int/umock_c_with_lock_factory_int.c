// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stddef.h>

#include "macro_utils/macro_utils.h" // IWYU pragma: keep

// TEST_DEFINE_ENUM_TYPE will use wchar.h, which we technically get from testrunnerswitcher.h
// IWYU pragma: no_include <wchar.h>
#include "testrunnerswitcher.h"

#include "umock_c/umock_lock_factory_default.h"
#include "minipal/umock_threadapi.h"

#define ENABLE_MOCKS

#include "umock_c/umock_c.h"

MOCKABLE_FUNCTION(, void, test_mock_function, int, arg);

#undef ENABLE_MOCKS

MU_DEFINE_ENUM_STRINGS(UMOCK_C_ERROR_CODE, UMOCK_C_ERROR_CODE_VALUES)
TEST_DEFINE_ENUM_TYPE(UMOCK_THREADAPI_RESULT, UMOCK_THREADAPI_RESULT_VALUES);

static void test_on_umock_c_error(UMOCK_C_ERROR_CODE error_code)
{
    ASSERT_FAIL("umock_c reported error :%s", MU_ENUM_TO_STRING(UMOCK_C_ERROR_CODE, error_code));
}

static TEST_MUTEX_HANDLE test_mutex;

BEGIN_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)

TEST_SUITE_INITIALIZE(suite_init)
{
    test_mutex = TEST_MUTEX_CREATE();
    ASSERT_IS_NOT_NULL(test_mutex);

    ASSERT_ARE_EQUAL(int, 0, umock_c_init_with_lock_factory(test_on_umock_c_error, umock_lock_factory_create_lock, NULL));
}

TEST_SUITE_CLEANUP(suite_cleanup)
{
    umock_c_deinit();

    TEST_MUTEX_DESTROY(test_mutex);
}

TEST_FUNCTION_INITIALIZE(test_function_init)
{
    ASSERT_ARE_EQUAL(int, 0, TEST_MUTEX_ACQUIRE(test_mutex));

    umock_c_reset_all_calls();
}

TEST_FUNCTION_CLEANUP(test_function_cleanup)
{
    TEST_MUTEX_RELEASE(test_mutex);
}

#if USE_VALGRIND
#define THREAD_COUNT 8
#define CALLS_PER_THREAD 500
#else
#define THREAD_COUNT 8
#define CALLS_PER_THREAD 5000
#endif

static int actual_calls_thread(void* arg)
{
    size_t i;

    (void)arg;

    for (i = 0; i < CALLS_PER_THREAD; i++)
    {
        test_mock_function(0);
    }

    return 0;
}

TEST_FUNCTION(expected_calls_and_actual_calls_from_multiple_threads_do_not_crash)
{
    // arrange
    UMOCK_THREAD_HANDLE threads[THREAD_COUNT];
    size_t i;

    for (i = 0; i < CALLS_PER_THREAD * THREAD_COUNT; i++)
    {
        STRICT_EXPECTED_CALL(test_mock_function(0));
    }

    for (i = 0; i < THREAD_COUNT; i++)
    {
        ASSERT_ARE_EQUAL(UMOCK_THREADAPI_RESULT, UMOCK_THREADAPI_OK, umock_threadapi_create(&threads[i], actual_calls_thread, NULL));
    }

    // act
    for (i = 0; i < THREAD_COUNT; i++)
    {
        int dont_care;
        ASSERT_ARE_EQUAL(UMOCK_THREADAPI_RESULT, UMOCK_THREADAPI_OK, umock_threadapi_join(threads[i], &dont_care));
    }

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "", umock_c_get_expected_calls());
    ASSERT_ARE_EQUAL(char_ptr, "", umock_c_get_actual_calls());
}

END_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)
