// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "testrunnerswitcher.h"

#define ENABLE_MOCKS

#include "umock_c/umock_c.h"
#include "umock_c/umocktypes_charptr.h"

MOCKABLE_FUNCTION(, int, a_char_star_arg_function, char*, x);

static void test_on_umock_c_error(UMOCK_C_ERROR_CODE error_code)
{
    (void)error_code;
    ASSERT_FAIL("umock_c reported error");
}

BEGIN_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)

TEST_SUITE_INITIALIZE(suite_init)
{
    int result;

    result = umock_c_init(test_on_umock_c_error);
    ASSERT_ARE_EQUAL(int, 0, result);
    result = umocktypes_charptr_register_types();
    ASSERT_ARE_EQUAL(int, 0, result);
}

TEST_SUITE_CLEANUP(suite_cleanup)
{
    umock_c_deinit();
}

TEST_FUNCTION_INITIALIZE(test_function_init)
{
    umock_c_reset_all_calls();
}

TEST_FUNCTION_CLEANUP(test_function_cleanup)
{
}

TEST_FUNCTION(a_matched_call_with_pointer_type_argument_does_not_leak)
{
    // arrange
    EXPECTED_CALL(a_char_star_arg_function("a"));
    (void)a_char_star_arg_function("a");

    // act
    umock_c_deinit();

    // assert
    // no leaks expected
}

END_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)
