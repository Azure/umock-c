// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "testrunnerswitcher.h"

#include "umock_c/umock_c_prod.h"  // for MOCKABLE_FUNCTION, MOCKABLE_FUNCTI...

MOCKABLE_FUNCTION(, int, test_generate_signature, int, a, double, b, char*, s);
MOCKABLE_FUNCTION(, void, test_generate_signature_void_return, int, a);
MOCKABLE_FUNCTION(, void, test_generate_signature_no_args);
MOCKABLE_FUNCTION_WITH_RETURNS(, int, test_generate_signature_with_returns, int, a, double, b, char*, s)(42, 43);
MOCKABLE_FUNCTION_WITH_RETURNS(, int, test_generate_signature_no_args_with_returns)(42, 43);
MOCKABLE_FUNCTION_WITH_RETURNS(, void*, test_generate_signature_with_returns_returning_ptr)((void*)0x4243, NULL);

int test_generate_signature(int a, double b, char* s)
{
    (void)a;
    (void)b;
    (void)s;
    return 42;
}

void test_generate_signature_void_return(int a)
{
    (void)a;
}

void test_generate_signature_no_args(void)
{
}

int test_generate_signature_with_returns(int a, double b, char* s)
{
    (void)a;
    (void)b;
    (void)s;
    return 42;
}

int test_generate_signature_no_args_with_returns(void)
{
    return 42;
}

void* test_generate_signature_with_returns_returning_ptr(void)
{
    return (void*)0x4242;
}

BEGIN_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)

TEST_SUITE_INITIALIZE(suite_init)
{
}

TEST_SUITE_CLEANUP(suite_cleanup)
{
}

TEST_FUNCTION_INITIALIZE(test_function_init)
{
}

TEST_FUNCTION_CLEANUP(test_function_cleanup)
{
}

/* Tests_SRS_UMOCK_C_LIB_01_002: [The macro shall generate a function signature in case ENABLE_MOCKS is not defined.] */
/* Tests_SRS_UMOCK_C_LIB_01_005: [**If ENABLE_MOCKS is not defined, MOCKABLE_FUNCTION shall only generate a declaration for the function.] */
TEST_FUNCTION(when_ENABLE_MOCKS_is_not_on_MOCKABLE_FUNCTION_generates_a_standard_function_declaration)
{
    // arrange

    // act
    int result = test_generate_signature(1, 0.42, "42");

    // assert
    ASSERT_ARE_EQUAL(int, 42, result);
}

/* Tests_SRS_UMOCK_C_LIB_01_002: [The macro shall generate a function signature in case ENABLE_MOCKS is not defined.] */
/* Tests_SRS_UMOCK_C_LIB_01_005: [**If ENABLE_MOCKS is not defined, MOCKABLE_FUNCTION shall only generate a declaration for the function.] */
TEST_FUNCTION(when_ENABLE_MOCKS_is_not_on_MOCKABLE_FUNCTION_generates_a_standard_function_declaration_with_void_return)
{
    // arrange

    // act
    test_generate_signature_void_return(1);

    // assert
    // no explicit assert
}

/* Tests_SRS_UMOCK_C_LIB_01_002: [The macro shall generate a function signature in case ENABLE_MOCKS is not defined.] */
/* Tests_SRS_UMOCK_C_LIB_01_005: [**If ENABLE_MOCKS is not defined, MOCKABLE_FUNCTION shall only generate a declaration for the function.] */
TEST_FUNCTION(when_ENABLE_MOCKS_is_not_on_MOCKABLE_FUNCTION_generates_a_standard_function_declaration_with_no_args_and_void_return)
{
    // arrange

    // act
    test_generate_signature_no_args();

    // assert
    // no explicit assert
}

/* Tests_SRS_UMOCK_C_LIB_01_213: [ The macro shall generate a function signature in case ENABLE_MOCKS is not defined. ]*/
TEST_FUNCTION(when_ENABLE_MOCKS_is_not_on_MOCKABLE_FUNCTION_generates_a_standard_function_declaration_for_MOCKABLE_FUNCTION_WITH_RETURNS_with_args)
{
    // arrange

    // act
    int result = test_generate_signature_with_returns(1, 0.42, "42");

    // assert
    ASSERT_ARE_EQUAL(int, 42, result);
}

/* Tests_SRS_UMOCK_C_LIB_01_213: [ The macro shall generate a function signature in case ENABLE_MOCKS is not defined. ]*/
TEST_FUNCTION(when_ENABLE_MOCKS_is_not_on_MOCKABLE_FUNCTION_generates_a_standard_function_declaration_for_MOCKABLE_FUNCTION_WITH_RETURNS_no_args)
{
    // arrange

    // act
    int result = test_generate_signature_no_args_with_returns();

    // assert
    ASSERT_ARE_EQUAL(int, 42, result);
}

/* Tests_SRS_UMOCK_C_LIB_01_213: [ The macro shall generate a function signature in case ENABLE_MOCKS is not defined. ]*/
TEST_FUNCTION(when_ENABLE_MOCKS_is_not_on_MOCKABLE_FUNCTION_generates_a_standard_function_declaration_for_MOCKABLE_FUNCTION_WITH_RETURNS_with_ptr_return)
{
    // arrange

    // act
    void* result = test_generate_signature_with_returns_returning_ptr();

    // assert
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4242, result);
}

END_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)
