// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "testrunnerswitcher.h"
#include "umock_c/umock_c.h"

#define ENABLE_MOCKS

// this enables mock filtering whicle being backward compatible
#define ENABLE_MOCK_FILTERING

// you have to be nice to the framework, so you have to say "please_mock_{function_name}"
#define please_mock_the_mocked_one MOCK_ENABLED

#include "test_dependency.h"

static TEST_MUTEX_HANDLE test_mutex;

static void test_on_umock_c_error(UMOCK_C_ERROR_CODE error_code)
{
    (void)error_code;
    ASSERT_FAIL("umock error");
}

int do_not_actually_mock(void)
{
    return 0x42;
}

int do_not_actually_mock_with_returns(void)
{
    return 0x42;
}

BEGIN_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)

TEST_SUITE_INITIALIZE(suite_init)
{
    test_mutex = TEST_MUTEX_CREATE();
    ASSERT_IS_NOT_NULL(test_mutex);

    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
}

TEST_SUITE_CLEANUP(suite_cleanup)
{
    umock_c_deinit();

    TEST_MUTEX_DESTROY(test_mutex);
}

TEST_FUNCTION_INITIALIZE(test_function_init)
{
    int mutex_acquire_result = TEST_MUTEX_ACQUIRE(test_mutex);
    ASSERT_ARE_EQUAL(int, 0, mutex_acquire_result);
}

TEST_FUNCTION_CLEANUP(test_function_cleanup)
{
    TEST_MUTEX_RELEASE(test_mutex);
}

TEST_FUNCTION(call_the_not_mocked_function)
{
    // arrange
    int result;

    // act
    result = do_not_actually_mock();

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "", umock_c_get_actual_calls());
    ASSERT_ARE_EQUAL(int, 0x42, result);
}

TEST_FUNCTION(call_the_not_mocked_function_with_returns)
{
    // arrange
    int result;

    // act
    result = do_not_actually_mock_with_returns();

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "", umock_c_get_actual_calls());
    ASSERT_ARE_EQUAL(int, 0x42, result);
}

END_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)
