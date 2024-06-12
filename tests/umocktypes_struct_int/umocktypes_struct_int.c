// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>                      // for printf, vprintf
#include <stdlib.h>

#include "macro_utils/macro_utils.h" // IWYU pragma: keep

#include "testrunnerswitcher.h"

#include "umock_c/umock_c.h"
#include "umock_c/umock_log.h"          // for UMOCK_LOG
#include "umock_c/umocktypes.h"         // for REGISTER_TYPE
#include "umock_c/umocktypes_c.h"
#include "umock_c/umocktypes_struct.h"

// Typedefs for the fields so we can use our own stringify/are_equal/copy/free functions and instrument the calls
typedef int my_int;
typedef char my_char;
typedef const int* my_const_int_ptr;
typedef const int* const volatile my_const_int_const_volatile_ptr;

static void my_const_int_const_volatile_ptr_assign(my_const_int_const_volatile_ptr* lhs, my_const_int_const_volatile_ptr rhs)
{
    *(int const**)lhs = rhs;
}

#define MY_STRUCT_FIELDS \
    my_int, foo, \
    my_char, bar

MU_DEFINE_STRUCT(MY_STRUCT, MY_STRUCT_FIELDS)
UMOCK_DEFINE_TYPE_STRUCT(MY_STRUCT, MY_STRUCT_FIELDS)

#define MY_NESTED_STRUCT_FIELDS \
    my_int, i, \
    MY_STRUCT, inner

MU_DEFINE_STRUCT(MY_NESTED_STRUCT, MY_NESTED_STRUCT_FIELDS)
UMOCK_DEFINE_TYPE_STRUCT(MY_NESTED_STRUCT, MY_NESTED_STRUCT_FIELDS)

// This should work with const fields
#define MY_STRUCT_WITH_CONST_FIELDS \
    my_const_int_ptr, i

MU_DEFINE_STRUCT(MY_STRUCT_WITH_CONST, MY_STRUCT_WITH_CONST_FIELDS)
UMOCK_DEFINE_TYPE_STRUCT(MY_STRUCT_WITH_CONST, MY_STRUCT_WITH_CONST_FIELDS)

// This should work with volatile const fields, such as THANDLE
// THANDLE is not known by umock directly because it is in a higher module layer, but we should verify that something like it works
#define MY_STRUCT_WITH_VOLATILE_CONST_FIELDS \
    my_const_int_const_volatile_ptr, i

MU_DEFINE_STRUCT(MY_STRUCT_WITH_VOLATILE_CONST, MY_STRUCT_WITH_VOLATILE_CONST_FIELDS)
UMOCK_DEFINE_TYPE_STRUCT(MY_STRUCT_WITH_VOLATILE_CONST, MY_STRUCT_WITH_VOLATILE_CONST_FIELDS)

uint32_t mock_stringify_my_int_was_called;
uint32_t mock_stringify_my_int_fail_next;
uint32_t mock_are_equal_my_int_was_called;
uint32_t mock_copy_my_int_was_called;
uint32_t mock_copy_my_int_fail_next;
uint32_t mock_free_my_int_was_called;

// The typedefed types will just track the number of calls and call the real versions
// Support fault injection for negative tests

char* umocktypes_stringify_my_int(my_int* value)
{
    mock_stringify_my_int_was_called++;

    if (mock_stringify_my_int_fail_next > 0)
    {
        mock_stringify_my_int_fail_next--;
        return NULL;
    }
    else
    {
        return umocktypes_stringify_int(value);
    }
}

int umocktypes_are_equal_my_int(my_int* left, my_int* right)
{
    mock_are_equal_my_int_was_called++;
    return umocktypes_are_equal_int(left, right);
}

int umocktypes_copy_my_int(my_int* destination, my_int* source)
{
    mock_copy_my_int_was_called++;

    if (mock_copy_my_int_fail_next > 0)
    {
        mock_copy_my_int_fail_next--;
        return 42;
    }
    else
    {
        return umocktypes_copy_int(destination, source);
    }
}

void umocktypes_free_my_int(my_int* value)
{
    mock_free_my_int_was_called++;
    umocktypes_free_int(value);
}

void reset_mock_my_int(void)
{
    mock_stringify_my_int_was_called = 0;
    mock_stringify_my_int_fail_next = 0;
    mock_are_equal_my_int_was_called = 0;
    mock_copy_my_int_was_called = 0;
    mock_copy_my_int_fail_next = 0;
    mock_free_my_int_was_called = 0;
}

uint32_t mock_stringify_my_char_was_called;
uint32_t mock_stringify_my_char_fail_next;
uint32_t mock_are_equal_my_char_was_called;
uint32_t mock_copy_my_char_was_called;
uint32_t mock_copy_my_char_fail_next;
uint32_t mock_free_my_char_was_called;

char* umocktypes_stringify_my_char(my_char* value)
{
    mock_stringify_my_char_was_called++;

    if (mock_stringify_my_char_fail_next > 0)
    {
        mock_stringify_my_char_fail_next--;
        return NULL;
    }
    else
    {
        return umocktypes_stringify_char(value);
    }
}

int umocktypes_are_equal_my_char(my_char* left, my_char* right)
{
    mock_are_equal_my_char_was_called++;
    return umocktypes_are_equal_char(left, right);
}

int umocktypes_copy_my_char(my_char* destination, my_char* source)
{
    mock_copy_my_char_was_called++;

    if (mock_copy_my_char_fail_next > 0)
    {
        mock_copy_my_char_fail_next--;
        return 42;
    }
    else
    {
        return umocktypes_copy_char(destination, source);
    }
}

void umocktypes_free_my_char(my_char* value)
{
    mock_free_my_char_was_called++;
    umocktypes_free_char(value);
}

void reset_mock_my_char(void)
{
    mock_stringify_my_char_was_called = 0;
    mock_stringify_my_char_fail_next = 0;
    mock_are_equal_my_char_was_called = 0;
    mock_copy_my_char_was_called = 0;
    mock_copy_my_char_fail_next = 0;
    mock_free_my_char_was_called = 0;
}

uint32_t mock_stringify_my_const_int_ptr_was_called;
uint32_t mock_stringify_my_const_int_ptr_fail_next;
uint32_t mock_are_equal_my_const_int_ptr_was_called;
uint32_t mock_copy_my_const_int_ptr_was_called;
uint32_t mock_copy_my_const_int_ptr_fail_next;
uint32_t mock_free_my_const_int_ptr_was_called;

char* umocktypes_stringify_my_const_int_ptr(my_const_int_ptr* value)
{
    mock_stringify_my_const_int_ptr_was_called++;

    if (mock_stringify_my_const_int_ptr_fail_next > 0)
    {
        mock_stringify_my_const_int_ptr_fail_next--;
        return NULL;
    }
    else
    {
        return umocktypes_stringify_void_ptr((void**)value);
    }
}

int umocktypes_are_equal_my_const_int_ptr(my_const_int_ptr* left, my_const_int_ptr* right)
{
    mock_are_equal_my_const_int_ptr_was_called++;
    return umocktypes_are_equal_void_ptr((void**)left, (void**)right);
}

int umocktypes_copy_my_const_int_ptr(my_const_int_ptr* destination, my_const_int_ptr* source)
{
    mock_copy_my_const_int_ptr_was_called++;

    if (mock_copy_my_const_int_ptr_fail_next > 0)
    {
        mock_copy_my_const_int_ptr_fail_next--;
        return 42;
    }
    else
    {
        return umocktypes_copy_void_ptr((void**)destination, (void**)source);
    }
}

void umocktypes_free_my_const_int_ptr(my_const_int_ptr* value)
{
    mock_free_my_const_int_ptr_was_called++;
    umocktypes_free_void_ptr((void**)value);
}

void reset_mock_my_const_int_ptr(void)
{
    mock_stringify_my_const_int_ptr_was_called = 0;
    mock_stringify_my_const_int_ptr_fail_next = 0;
    mock_are_equal_my_const_int_ptr_was_called = 0;
    mock_copy_my_const_int_ptr_was_called = 0;
    mock_copy_my_const_int_ptr_fail_next = 0;
    mock_free_my_const_int_ptr_was_called = 0;
}

uint32_t mock_stringify_my_const_int_const_volatile_ptr_was_called;
uint32_t mock_stringify_my_const_int_const_volatile_ptr_fail_next;
uint32_t mock_are_equal_my_const_int_const_volatile_ptr_was_called;
uint32_t mock_copy_my_const_int_const_volatile_ptr_was_called;
uint32_t mock_copy_my_const_int_const_volatile_ptr_fail_next;
uint32_t mock_free_my_const_int_const_volatile_ptr_was_called;

char* umocktypes_stringify_my_const_int_const_volatile_ptr(my_const_int_const_volatile_ptr* value)
{
    mock_stringify_my_const_int_const_volatile_ptr_was_called++;

    if (mock_stringify_my_const_int_const_volatile_ptr_fail_next > 0)
    {
        mock_stringify_my_const_int_const_volatile_ptr_fail_next--;
        return NULL;
    }
    else
    {
        return umocktypes_stringify_void_ptr((void**)value);
    }
}

int umocktypes_are_equal_my_const_int_const_volatile_ptr(my_const_int_const_volatile_ptr* left, my_const_int_const_volatile_ptr* right)
{
    mock_are_equal_my_const_int_const_volatile_ptr_was_called++;
    return umocktypes_are_equal_void_ptr((void**)left, (void**)right);
}

int umocktypes_copy_my_const_int_const_volatile_ptr(my_const_int_const_volatile_ptr* destination, my_const_int_const_volatile_ptr* source)
{
    mock_copy_my_const_int_const_volatile_ptr_was_called++;

    if (mock_copy_my_const_int_const_volatile_ptr_fail_next > 0)
    {
        mock_copy_my_const_int_const_volatile_ptr_fail_next--;
        return 42;
    }
    else
    {
        return umocktypes_copy_void_ptr((void**)destination, (void**)source);
    }
}

void umocktypes_free_my_const_int_const_volatile_ptr(my_const_int_const_volatile_ptr* value)
{
    mock_free_my_const_int_const_volatile_ptr_was_called++;
    umocktypes_free_void_ptr((void**)value);
}

void reset_mock_my_const_int_const_volatile_ptr(void)
{
    mock_stringify_my_const_int_const_volatile_ptr_was_called = 0;
    mock_stringify_my_const_int_const_volatile_ptr_fail_next = 0;
    mock_are_equal_my_const_int_const_volatile_ptr_was_called = 0;
    mock_copy_my_const_int_const_volatile_ptr_was_called = 0;
    mock_copy_my_const_int_const_volatile_ptr_fail_next = 0;
    mock_free_my_const_int_const_volatile_ptr_was_called = 0;
}

MU_DEFINE_ENUM_STRINGS(UMOCK_C_ERROR_CODE, UMOCK_C_ERROR_CODE_VALUES)

static void on_umock_c_error(UMOCK_C_ERROR_CODE error_code)
{
    ASSERT_FAIL("umock_c reported error :%s", MU_ENUM_TO_STRING(UMOCK_C_ERROR_CODE, error_code));
}

BEGIN_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)

TEST_SUITE_INITIALIZE(suite_init)
{
    int result;

    result = umock_c_init(on_umock_c_error);
    ASSERT_ARE_EQUAL(int, 0, result, "umock_c_init");

    REGISTER_TYPE(MY_STRUCT, MY_STRUCT);
    REGISTER_TYPE(my_int, my_int);
    REGISTER_TYPE(my_char, my_char);
    REGISTER_TYPE(my_const_int_ptr, my_const_int_ptr);
    REGISTER_TYPE(my_const_int_const_volatile_ptr, my_const_int_const_volatile_ptr);
}

TEST_SUITE_CLEANUP(suite_cleanup)
{
    umock_c_deinit();
}

TEST_FUNCTION_INITIALIZE(test_function_init)
{
    reset_mock_my_int();
    reset_mock_my_char();
    reset_mock_my_const_int_ptr();
    reset_mock_my_const_int_const_volatile_ptr();
}

TEST_FUNCTION_CLEANUP(test_function_cleanup)
{
}

//
// umocktypes_stringify_MY_STRUCT
//

/*Tests_SRS_UMOCKTYPES_STRUCT_42_001: [ umocktypes_stringify_<type> shall call umocktypes_stringify for each field in type. ]*/
/*Tests_SRS_UMOCKTYPES_STRUCT_42_002: [ umocktypes_stringify_<type> shall generate a string containing all stringified fields in type and return it. ]*/
/*Tests_SRS_UMOCKTYPES_STRUCT_42_003: [ umocktypes_stringify_<type> shall free all of the stringified fields. ]*/
TEST_FUNCTION(umocktypes_stringify_MY_STRUCT_stringifies_all_fields)
{
    // arrange
    MY_STRUCT my_struct;
    my_struct.foo = 42;
    my_struct.bar = 100;

    // act
    char* result = umocktypes_stringify_MY_STRUCT(&my_struct);

    // assert
    ASSERT_IS_NOT_NULL(result);

    ASSERT_ARE_EQUAL(uint32_t, 1, mock_stringify_my_int_was_called, "int should have been stringified");
    ASSERT_ARE_EQUAL(uint32_t, 1, mock_stringify_my_char_was_called, "char should have been stringified");

    ASSERT_ARE_EQUAL(char_ptr, "{MY_STRUCT:foo=42,bar=100}", result);

    // cleanup
    free(result);
}

/*Tests_SRS_UMOCKTYPES_STRUCT_42_004: [ If there are any errors then umocktypes_stringify_<type> shall fail and return NULL. ]*/
TEST_FUNCTION(umocktypes_stringify_MY_STRUCT_fails_if_int_field_fails_to_stringify)
{
    // arrange
    MY_STRUCT my_struct;
    my_struct.foo = 42;
    my_struct.bar = 100;

    mock_stringify_my_int_fail_next = 1;

    // act
    char* result = umocktypes_stringify_MY_STRUCT(&my_struct);

    // assert
    ASSERT_IS_NULL(result);
}

/*Tests_SRS_UMOCKTYPES_STRUCT_42_004: [ If there are any errors then umocktypes_stringify_<type> shall fail and return NULL. ]*/
TEST_FUNCTION(umocktypes_stringify_MY_STRUCT_fails_if_char_field_fails_to_stringify)
{
    // arrange
    MY_STRUCT my_struct;
    my_struct.foo = 42;
    my_struct.bar = 100;

    mock_stringify_my_char_fail_next = 1;

    // act
    char* result = umocktypes_stringify_MY_STRUCT(&my_struct);

    // assert
    ASSERT_IS_NULL(result);
}

/*Tests_SRS_UMOCKTYPES_STRUCT_42_001: [ umocktypes_stringify_<type> shall call umocktypes_stringify for each field in type. ]*/
/*Tests_SRS_UMOCKTYPES_STRUCT_42_002: [ umocktypes_stringify_<type> shall generate a string containing all stringified fields in type and return it. ]*/
/*Tests_SRS_UMOCKTYPES_STRUCT_42_003: [ umocktypes_stringify_<type> shall free all of the stringified fields. ]*/
TEST_FUNCTION(umocktypes_stringify_MY_NESTED_STRUCT_stringifies_all_fields)
{
    // arrange
    MY_NESTED_STRUCT my_struct;
    my_struct.i = -7;
    my_struct.inner.foo = 42;
    my_struct.inner.bar = 100;

    // act
    char* result = umocktypes_stringify_MY_NESTED_STRUCT(&my_struct);

    // assert
    ASSERT_IS_NOT_NULL(result);

    ASSERT_ARE_EQUAL(uint32_t, 2, mock_stringify_my_int_was_called, "int should have been stringified");
    ASSERT_ARE_EQUAL(uint32_t, 1, mock_stringify_my_char_was_called, "char should have been stringified");

    ASSERT_ARE_EQUAL(char_ptr, "{MY_NESTED_STRUCT:i=-7,inner={MY_STRUCT:foo=42,bar=100}}", result);

    // cleanup
    free(result);
}

TEST_FUNCTION(umocktypes_stringify_MY_STRUCT_WITH_CONST_stringifies_all_fields)
{
    // arrange
    MY_STRUCT_WITH_CONST my_struct;
    my_struct.i = NULL;

    // act
    char* result = umocktypes_stringify_MY_STRUCT_WITH_CONST(&my_struct);

    // assert
    ASSERT_IS_NOT_NULL(result);

    ASSERT_ARE_EQUAL(uint32_t, 1, mock_stringify_my_const_int_ptr_was_called, "my_const_int_ptr should have been stringified");

    // cleanup
    free(result);
}

TEST_FUNCTION(umocktypes_stringify_MY_STRUCT_WITH_VOLATILE_CONST_stringifies_all_fields)
{
    // arrange
    MY_STRUCT_WITH_VOLATILE_CONST my_struct = {0};
    my_const_int_const_volatile_ptr_assign(&my_struct.i, NULL);

    // act
    char* result = umocktypes_stringify_MY_STRUCT_WITH_VOLATILE_CONST(&my_struct);

    // assert
    ASSERT_IS_NOT_NULL(result);

    ASSERT_ARE_EQUAL(uint32_t, 1, mock_stringify_my_const_int_const_volatile_ptr_was_called, "my_const_int_const_volatile_ptr should have been stringified");

    // cleanup
    free(result);
}

//
// umocktypes_are_equal_MY_STRUCT
//

/*Tests_SRS_UMOCKTYPES_STRUCT_42_005: [ If left is NULL then umocktypes_are_equal_<type> shall fail and return -1. ]*/
TEST_FUNCTION(umocktypes_are_equal_MY_STRUCT_with_NULL_left_fails)
{
    // arrange
    MY_STRUCT my_struct;
    my_struct.foo = 42;
    my_struct.bar = 100;

    // act
    int result = umocktypes_are_equal_MY_STRUCT(NULL, &my_struct);

    // assert
    ASSERT_ARE_EQUAL(int, -1, result);
}

/*Tests_SRS_UMOCKTYPES_STRUCT_42_006: [ If right is NULL then umocktypes_are_equal_<type> shall fail and return -1. ]*/
TEST_FUNCTION(umocktypes_are_equal_MY_STRUCT_with_NULL_right_fails)
{
    // arrange
    MY_STRUCT my_struct;
    my_struct.foo = 42;
    my_struct.bar = 100;

    // act
    int result = umocktypes_are_equal_MY_STRUCT(&my_struct, NULL);

    // assert
    ASSERT_ARE_EQUAL(int, -1, result);
}

/*Tests_SRS_UMOCKTYPES_STRUCT_42_007: [ umocktypes_are_equal_<type> shall call umocktypes_are_equal for each field in type. ]*/
/*Tests_SRS_UMOCKTYPES_STRUCT_42_009: [ Otherwise, umocktypes_are_equal_<type> shall return 1. ]*/
TEST_FUNCTION(umocktypes_are_equal_MY_STRUCT_structs_have_same_fields)
{
    // arrange
    MY_STRUCT my_struct;
    my_struct.foo = 42;
    my_struct.bar = 100;

    MY_STRUCT my_struct2;
    my_struct2.foo = 42;
    my_struct2.bar = 100;

    // act
    int result = umocktypes_are_equal_MY_STRUCT(&my_struct, &my_struct2);

    // assert
    ASSERT_ARE_EQUAL(int, 1, result);

    ASSERT_ARE_EQUAL(uint32_t, 1, mock_are_equal_my_int_was_called, "int should have been compared");
    ASSERT_ARE_EQUAL(uint32_t, 1, mock_are_equal_my_char_was_called, "char should have been compared");
}

/*Tests_SRS_UMOCKTYPES_STRUCT_42_007: [ umocktypes_are_equal_<type> shall call umocktypes_are_equal for each field in type. ]*/
/*Tests_SRS_UMOCKTYPES_STRUCT_42_008: [ If any call to umocktypes_are_equal does not return 1 then umocktypes_are_equal_<type> shall return 0. ]*/
TEST_FUNCTION(umocktypes_are_equal_MY_STRUCT_structs_one_different_field)
{
    // arrange
    MY_STRUCT my_struct;
    my_struct.foo = 42;
    my_struct.bar = 100;

    MY_STRUCT my_struct2;
    my_struct2.foo = 42;
    my_struct2.bar = 99;

    // act
    int result = umocktypes_are_equal_MY_STRUCT(&my_struct, &my_struct2);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);

    ASSERT_ARE_EQUAL(uint32_t, 1, mock_are_equal_my_int_was_called, "int should have been compared");
    ASSERT_ARE_EQUAL(uint32_t, 1, mock_are_equal_my_char_was_called, "char should have been compared");
}

/*Tests_SRS_UMOCKTYPES_STRUCT_42_007: [ umocktypes_are_equal_<type> shall call umocktypes_are_equal for each field in type. ]*/
/*Tests_SRS_UMOCKTYPES_STRUCT_42_009: [ Otherwise, umocktypes_are_equal_<type> shall return 1. ]*/
TEST_FUNCTION(umocktypes_are_equal_MY_NESTED_STRUCT_structs_have_same_fields)
{
    // arrange
    MY_NESTED_STRUCT my_struct;
    my_struct.i = -7;
    my_struct.inner.foo = 42;
    my_struct.inner.bar = 100;

    MY_NESTED_STRUCT my_struct2;
    my_struct2.i = -7;
    my_struct2.inner.foo = 42;
    my_struct2.inner.bar = 100;

    // act
    int result = umocktypes_are_equal_MY_NESTED_STRUCT(&my_struct, &my_struct2);

    // assert
    ASSERT_ARE_EQUAL(int, 1, result);

    ASSERT_ARE_EQUAL(uint32_t, 2, mock_are_equal_my_int_was_called, "int should have been compared");
    ASSERT_ARE_EQUAL(uint32_t, 1, mock_are_equal_my_char_was_called, "char should have been compared");
}

/*Tests_SRS_UMOCKTYPES_STRUCT_42_007: [ umocktypes_are_equal_<type> shall call umocktypes_are_equal for each field in type. ]*/
/*Tests_SRS_UMOCKTYPES_STRUCT_42_008: [ If any call to umocktypes_are_equal does not return 1 then umocktypes_are_equal_<type> shall return 0. ]*/
TEST_FUNCTION(umocktypes_are_equal_MY_NESTED_STRUCT_structs_one_different_field)
{
    // arrange
    MY_NESTED_STRUCT my_struct;
    my_struct.i = -7;
    my_struct.inner.foo = 42;
    my_struct.inner.bar = 100;

    MY_NESTED_STRUCT my_struct2;
    my_struct2.i = -7;
    my_struct2.inner.foo = 42;
    my_struct2.inner.bar = 99;

    // act
    int result = umocktypes_are_equal_MY_NESTED_STRUCT(&my_struct, &my_struct2);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);

    ASSERT_ARE_EQUAL(uint32_t, 2, mock_are_equal_my_int_was_called, "int should have been compared");
    ASSERT_ARE_EQUAL(uint32_t, 1, mock_are_equal_my_char_was_called, "char should have been compared");
}

TEST_FUNCTION(umocktypes_are_equal_MY_STRUCT_WITH_CONST_structs_have_same_fields)
{
    // arrange
    MY_STRUCT_WITH_CONST my_struct;
    my_struct.i = NULL;

    MY_STRUCT_WITH_CONST my_struct2;
    my_struct2.i = NULL;

    // act
    int result = umocktypes_are_equal_MY_STRUCT_WITH_CONST(&my_struct, &my_struct2);

    // assert
    ASSERT_ARE_EQUAL(int, 1, result);

    ASSERT_ARE_EQUAL(uint32_t, 1, mock_are_equal_my_const_int_ptr_was_called, "my_const_int_ptr should have been compared");
}

TEST_FUNCTION(umocktypes_are_equal_MY_STRUCT_WITH_VOLATILE_CONST_structs_have_same_fields)
{
    // arrange
    MY_STRUCT_WITH_VOLATILE_CONST my_struct = {0};
    my_const_int_const_volatile_ptr_assign(&my_struct.i, NULL);

    MY_STRUCT_WITH_VOLATILE_CONST my_struct2 = {0};
    my_const_int_const_volatile_ptr_assign(&my_struct2.i, NULL);

    // act
    int result = umocktypes_are_equal_MY_STRUCT_WITH_VOLATILE_CONST(&my_struct, &my_struct2);

    // assert
    ASSERT_ARE_EQUAL(int, 1, result);

    ASSERT_ARE_EQUAL(uint32_t, 1, mock_are_equal_my_const_int_const_volatile_ptr_was_called, "my_const_int_const_volatile_ptr should have been compared");
}

//
// umocktypes_copy_MY_STRUCT
//

/*Tests_SRS_UMOCKTYPES_STRUCT_42_010: [ If destination is NULL then umocktypes_copy_<type> shall fail and return a non-zero value. ]*/
TEST_FUNCTION(umocktypes_copy_MY_STRUCT_with_NULL_destination_fails)
{
    // arrange
    MY_STRUCT my_struct;
    my_struct.foo = 42;
    my_struct.bar = 100;

    // act
    int result = umocktypes_copy_MY_STRUCT(NULL, &my_struct);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
}

/*Tests_SRS_UMOCKTYPES_STRUCT_42_011: [ If source is NULL then umocktypes_copy_<type> shall fail and return a non-zero value. ]*/
TEST_FUNCTION(umocktypes_copy_MY_STRUCT_with_NULL_source_fails)
{
    // arrange
    MY_STRUCT my_struct;
    my_struct.foo = 42;
    my_struct.bar = 100;

    // act
    int result = umocktypes_copy_MY_STRUCT(&my_struct, NULL);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
}

/*Tests_SRS_UMOCKTYPES_STRUCT_42_012: [ umocktypes_copy_<type> shall call umocktypes_copy for each field in type. ]*/
/*Tests_SRS_UMOCKTYPES_STRUCT_42_014: [ Otherwise umocktypes_copy_<type> shall return 0. ]*/
TEST_FUNCTION(umocktypes_copy_MY_STRUCT_succeeds)
{
    // arrange
    MY_STRUCT my_struct;
    my_struct.foo = 42;
    my_struct.bar = 100;

    MY_STRUCT my_struct_copy;
    my_struct_copy.foo = 0;
    my_struct_copy.bar = 0;

    // act
    int result = umocktypes_copy_MY_STRUCT(&my_struct_copy, &my_struct);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);

    ASSERT_ARE_EQUAL(uint32_t, 1, mock_copy_my_int_was_called, "int should have been copied");
    ASSERT_ARE_EQUAL(uint32_t, 1, mock_copy_my_char_was_called, "char should have been copied");

    ASSERT_ARE_EQUAL(int, my_struct.foo, my_struct_copy.foo);
    ASSERT_ARE_EQUAL(char, my_struct.bar, my_struct_copy.bar);
}

/*Tests_SRS_UMOCKTYPES_STRUCT_42_012: [ umocktypes_copy_<type> shall call umocktypes_copy for each field in type. ]*/
/*Tests_SRS_UMOCKTYPES_STRUCT_42_013: [ If any call to umocktypes_copy does not return 0 then umocktypes_copy_<type> shall return a non-zero value. ]*/
TEST_FUNCTION(umocktypes_copy_MY_STRUCT_fails_to_copy_int_field)
{
    // arrange
    MY_STRUCT my_struct;
    my_struct.foo = 42;
    my_struct.bar = 100;

    MY_STRUCT my_struct_copy;
    my_struct_copy.foo = 0;
    my_struct_copy.bar = 0;

    mock_copy_my_int_fail_next = 1;

    // act
    int result = umocktypes_copy_MY_STRUCT(&my_struct_copy, &my_struct);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
}

/*Tests_SRS_UMOCKTYPES_STRUCT_42_012: [ umocktypes_copy_<type> shall call umocktypes_copy for each field in type. ]*/
/*Tests_SRS_UMOCKTYPES_STRUCT_42_013: [ If any call to umocktypes_copy does not return 0 then umocktypes_copy_<type> shall return a non-zero value. ]*/
TEST_FUNCTION(umocktypes_copy_MY_STRUCT_fails_to_copy_char_field)
{
    // arrange
    MY_STRUCT my_struct;
    my_struct.foo = 42;
    my_struct.bar = 100;

    MY_STRUCT my_struct_copy;
    my_struct_copy.foo = 0;
    my_struct_copy.bar = 0;

    mock_copy_my_char_fail_next = 1;

    // act
    int result = umocktypes_copy_MY_STRUCT(&my_struct_copy, &my_struct);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
}

/*Tests_SRS_UMOCKTYPES_STRUCT_42_012: [ umocktypes_copy_<type> shall call umocktypes_copy for each field in type. ]*/
/*Tests_SRS_UMOCKTYPES_STRUCT_42_014: [ Otherwise umocktypes_copy_<type> shall return 0. ]*/
TEST_FUNCTION(umocktypes_copy_MY_NESTED_STRUCT_succeeds)
{
    // arrange
    MY_NESTED_STRUCT my_struct;
    my_struct.i = -7;
    my_struct.inner.foo = 42;
    my_struct.inner.bar = 100;

    MY_NESTED_STRUCT my_struct_copy;
    my_struct_copy.i = 0;
    my_struct_copy.inner.foo = 0;
    my_struct_copy.inner.bar = 0;

    // act
    int result = umocktypes_copy_MY_NESTED_STRUCT(&my_struct_copy, &my_struct);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);

    ASSERT_ARE_EQUAL(uint32_t, 2, mock_copy_my_int_was_called, "int should have been copied");
    ASSERT_ARE_EQUAL(uint32_t, 1, mock_copy_my_char_was_called, "char should have been copied");

    ASSERT_ARE_EQUAL(int, my_struct.i, my_struct_copy.i);
    ASSERT_ARE_EQUAL(int, my_struct.inner.foo, my_struct_copy.inner.foo);
    ASSERT_ARE_EQUAL(char, my_struct.inner.bar, my_struct_copy.inner.bar);
}

TEST_FUNCTION(umocktypes_copy_MY_STRUCT_WITH_CONST_succeeds)
{
    // arrange
    MY_STRUCT_WITH_CONST my_struct;
    my_struct.i = NULL;

    MY_STRUCT_WITH_CONST my_struct_copy;

    // act
    int result = umocktypes_copy_MY_STRUCT_WITH_CONST(&my_struct_copy, &my_struct);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);

    ASSERT_ARE_EQUAL(uint32_t, 1, mock_copy_my_const_int_ptr_was_called, "my_const_int_ptr should have been copied");

    ASSERT_ARE_EQUAL(void_ptr, my_struct.i, my_struct_copy.i);
}

TEST_FUNCTION(umocktypes_copy_MY_STRUCT_WITH_VOLATILE_CONST_succeeds)
{
    // arrange
    MY_STRUCT_WITH_VOLATILE_CONST my_struct = {0};
    my_const_int_const_volatile_ptr_assign(&my_struct.i, NULL);

    MY_STRUCT_WITH_VOLATILE_CONST my_struct_copy;

    // act
    int result = umocktypes_copy_MY_STRUCT_WITH_VOLATILE_CONST(&my_struct_copy, &my_struct);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);

    ASSERT_ARE_EQUAL(uint32_t, 1, mock_copy_my_const_int_const_volatile_ptr_was_called, "my_const_int_const_volatile_ptr should have been copied");

    ASSERT_ARE_EQUAL(void_ptr, my_struct.i, my_struct_copy.i);
}

//
// umocktypes_free_MY_STRUCT
//

/*Tests_SRS_UMOCKTYPES_STRUCT_42_015: [ umocktypes_free_<type> shall call umocktypes_free for each field in type. ]*/
TEST_FUNCTION(umocktypes_free_MY_STRUCT_frees_each_field)
{
    // arrange
    MY_STRUCT my_struct = {0};
    my_struct.foo = 42;
    my_struct.bar = 100;

    // act
    umocktypes_free_MY_STRUCT(&my_struct);

    // assert
    ASSERT_ARE_EQUAL(uint32_t, 1, mock_free_my_int_was_called, "int should have been freed");
    ASSERT_ARE_EQUAL(uint32_t, 1, mock_free_my_char_was_called, "char should have been freed");
}

/*Tests_SRS_UMOCKTYPES_STRUCT_42_015: [ umocktypes_free_<type> shall call umocktypes_free for each field in type. ]*/
TEST_FUNCTION(umocktypes_free_MY_NESTED_STRUCT_frees_each_field)
{
    // arrange
    MY_NESTED_STRUCT my_struct = {0};
    my_struct.i = -7;
    my_struct.inner.foo = 42;
    my_struct.inner.bar = 100;

    // act
    umocktypes_free_MY_NESTED_STRUCT(&my_struct);

    // assert
    ASSERT_ARE_EQUAL(uint32_t, 2, mock_free_my_int_was_called, "int should have been freed");
    ASSERT_ARE_EQUAL(uint32_t, 1, mock_free_my_char_was_called, "char should have been freed");
}

TEST_FUNCTION(umocktypes_free_MY_STRUCT_WITH_CONST_frees_each_field)
{
    // arrange
    MY_STRUCT_WITH_CONST my_struct = {0};
    my_struct.i = NULL;

    // act
    umocktypes_free_MY_STRUCT_WITH_CONST(&my_struct);

    // assert
    ASSERT_ARE_EQUAL(uint32_t, 1, mock_free_my_const_int_ptr_was_called, "my_const_int_ptr should have been freed");
}

TEST_FUNCTION(umocktypes_free_MY_STRUCT_WITH_VOLATILE_CONST_frees_each_field)
{
    // arrange
    MY_STRUCT_WITH_VOLATILE_CONST my_struct = {0};
    my_const_int_const_volatile_ptr_assign(&my_struct.i, NULL);

    // act
    umocktypes_free_MY_STRUCT_WITH_VOLATILE_CONST(&my_struct);

    // assert
    ASSERT_ARE_EQUAL(uint32_t, 1, mock_free_my_const_int_const_volatile_ptr_was_called, "my_const_int_const_volatile_ptr should have been freed");
}

END_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)
