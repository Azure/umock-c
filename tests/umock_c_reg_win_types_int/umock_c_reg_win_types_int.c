// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.


#include "macro_utils/macro_utils.h"
#include "testrunnerswitcher.h"

#include "umock_c/umocktypes_charptr.h"
#include "umock_c/umocktypes_wcharptr.h"
#include "umock_c/umocktypes_stdint.h"
#include "umock_c/umocktypes_windows.h"

#include "umock_c/umock_c.h"

static TEST_MUTEX_HANDLE test_mutex;

MU_DEFINE_ENUM_STRINGS(UMOCK_C_ERROR_CODE, UMOCK_C_ERROR_CODE_VALUES);

static void test_on_umock_c_error(UMOCK_C_ERROR_CODE error_code)
{
    ASSERT_FAIL("test_on_umock_c_error called with %" PRI_MU_ENUM "", MU_ENUM_VALUE(UMOCK_C_ERROR_CODE, error_code));
}

BEGIN_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)

TEST_SUITE_INITIALIZE(suite_init)
{
    test_mutex = TEST_MUTEX_CREATE();
    ASSERT_IS_NOT_NULL(test_mutex);

    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error), "umock_c_init");
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
    umock_c_reset_all_calls();

    TEST_MUTEX_RELEASE(test_mutex);
}

TEST_FUNCTION(unmatched_expected_calls_with_windows_args_are_reported)
{
    // arrange
    ASSERT_ARE_EQUAL(int, 0, umocktypes_charptr_register_types(), "umocktypes_charptr_register_types");
    ASSERT_ARE_EQUAL(int, 0, umocktypes_wcharptr_register_types(), "umocktypes_wcharptr_register_types");
    ASSERT_ARE_EQUAL(int, 0, umocktypes_stdint_register_types(), "umocktypes_stdint_register_types");

    // act
    int result = umocktypes_windows_register_types();
    
    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
}

END_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)
