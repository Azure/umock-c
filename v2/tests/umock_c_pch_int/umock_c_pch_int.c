// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "testrunnerswitcher.h"

#include "umock_c/umock_c_v2.h"

#include "unit_b.h"

#include "umock_c/no_mocks.h"

#include "unit_a.h"

static void test_on_umock_c_error(UMOCK_C_ERROR_CODE error_code)
{
    (void)error_code;
    ASSERT_FAIL("umock_c reported error");
}

BEGIN_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)

TEST_SUITE_INITIALIZE(suite_init)
{
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
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

TEST_FUNCTION(the_simplest_test)
{
    // arrange
    STRICT_EXPECTED_CALL(unit_b_do_something());

    // act
    unit_a_that_calls_unit_b();

    // assert
    // no leaks expected
}

END_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)
