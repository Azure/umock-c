// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#include "testrunnerswitcher.h"
#include "umock_c/umockautoignoreargs.h"

typedef struct test_malloc_CALL_TAG
{
    size_t size;
} test_malloc_CALL;

static test_malloc_CALL* test_malloc_calls;
static size_t test_malloc_call_count;
static size_t when_shall_malloc_fail;


    void* mock_malloc(size_t size)
    {
        void* result;

        test_malloc_CALL* new_calls = realloc(test_malloc_calls, sizeof(test_malloc_CALL) * (test_malloc_call_count + 1));
        if (new_calls != NULL)
        {
            test_malloc_calls = new_calls;
            test_malloc_calls[test_malloc_call_count].size = size;
            test_malloc_call_count++;
        }

        if (when_shall_malloc_fail == test_malloc_call_count)
        {
            result = NULL;
        }
        else
        {
            result = malloc(size);
        }

        return result;
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
    when_shall_malloc_fail = 0;

    test_malloc_calls = NULL;
    test_malloc_call_count = 0;
}

TEST_FUNCTION_CLEANUP(test_function_cleanup)
{
    free(test_malloc_calls);
    test_malloc_calls = NULL;
    test_malloc_call_count = 0;
}

/* umockautoignoreargs_is_call_argument_ignored */

/* Tests_SRS_UMOCKAUTOIGNOREARGS_01_002: [ If call or is_argument_ignored is NULL, umockautoignoreargs_is_call_argument_ignored shall fail and return a non-zero value. ]*/
/* Tests_SRS_UMOCKAUTOIGNOREARGS_01_004: [ If umockautoignoreargs_is_call_argument_ignored fails parsing the call argument it shall fail and return a non-zero value. ]*/
/* Tests_SRS_UMOCKAUTOIGNOREARGS_01_009: [ If the number of arguments parsed from call is less than argument_index, umockautoignoreargs_is_call_argument_ignored shall fail and return a non-zero value. ]*/
/* Tests_SRS_UMOCKAUTOIGNOREARGS_01_010: [ umockautoignoreargs_is_call_argument_ignored shall look for the arguments as being the string contained in the scope of the rightmost parenthesis set in call. ]*/
/* Tests_SRS_UMOCKAUTOIGNOREARGS_01_011: [ If a valid scope of the rightmost parenthesis set cannot be formed (imbalanced parenthesis for example), umockautoignoreargs_is_call_argument_ignored shall fail and return a non-zero value. ]*/
PARAMETERIZED_TEST_FUNCTION(umockautoignoreargs_is_call_argument_ignored_fails,
    ARGS(const char*, call_str, size_t, arg_idx),
    CASE((NULL, 1), with_NULL_call),
    CASE((NULL, 1), with_NULL_is_argument_ignored_argument),
    CASE(("a", 1), when_no_lparen_is_found),
    CASE(("a()", 1), for_arg_1_when_no_args_in_call),
    CASE(("WRAPPER(a)(IGNORED_ARG(", 1), when_RPAREN_missing_at_end),
    CASE(("WRAPPER(a)(IGNORED_ARG)(", 1), when_extra_LPAREN_at_end),
    CASE(("WRAPPER(a)(IGNORED_ARG)()", 1), when_extra_LPAREN_RPAREN_at_end),
    CASE(("IGNORED_ARG, (0))", 1), with_not_enough_LPARENs_for_args))
{
    // arrange
    int result;
    int is_ignored;

    // act
    result = umockautoignoreargs_is_call_argument_ignored(call_str, arg_idx, &is_ignored);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
}

/* Tests_SRS_UMOCKAUTOIGNOREARGS_01_001: [ umockautoignoreargs_is_call_argument_ignored shall determine whether argument argument_index shall be ignored or not. ]*/
/* Tests_SRS_UMOCKAUTOIGNOREARGS_01_003: [ umockautoignoreargs_is_call_argument_ignored shall parse the call string as a function call: function_name(arg1, arg2, ...). ]*/
/* Tests_SRS_UMOCKAUTOIGNOREARGS_01_005: [ If umockautoignoreargs_is_call_argument_ignored was able to parse the argument_indexth argument it shall succeed and return 0, while writing whether the argument is ignored in the is_argument_ignored output argument. ]*/
/* Tests_SRS_UMOCKAUTOIGNOREARGS_01_007: [ If the argument value is IGNORED_ARG then is_argument_ignored shall be set to 1. ]*/
/* Tests_SRS_UMOCKAUTOIGNOREARGS_01_008: [ If the argument value is any other value then is_argument_ignored shall be set to 0. ]*/
/* Tests_SRS_UMOCKAUTOIGNOREARGS_01_010: [ umockautoignoreargs_is_call_argument_ignored shall look for the arguments as being the string contained in the scope of the rightmost parenthesis set in call. ]*/
/* Tests_SRS_UMOCKAUTOIGNOREARGS_01_012: [ If the argument value starts with IGNORED_STRUCT_ARG then is_argument_ignored shall be set to 1. ]*/
PARAMETERIZED_TEST_FUNCTION(umockautoignoreargs_is_call_argument_ignored_succeeds,
    ARGS(const char*, call_str, size_t, arg_idx, int, expected_ignored),
    CASE(("a(IGNORED_ARG)", 1, 1), for_arg_1_when_1_IGNORED_ARG),
    CASE(("a(\"a\", IGNORED_ARG)", 2, 1), for_arg_2_with_IGNORED_ARG),
    CASE(("a(\"a\", xx)", 2, 0), for_arg_2_no_match),
    CASE(("a (\"a\", IGNORED_ARG)", 2, 1), with_space_before_lparen),
    CASE(("a( \"a\", IGNORED_ARG)", 2, 1), with_space_after_lparen),
    CASE(("a(\"a\" , IGNORED_ARG)", 2, 1), with_space_before_comma),
    CASE(("a(\"a\", IGNORED_ARG )", 2, 1), with_space_before_rparen),
    CASE(("a(b(1,2), IGNORED_ARG)", 2, 1), first_arg_is_function_call),
    CASE(("a({1,2}, IGNORED_ARG)", 2, 1), first_arg_has_structure),
    CASE(("WRAPPER(a)(IGNORED_ARG)", 1, 1), other_parens_in_call),
    CASE(("WRAPPER(a)(IGNORED_ARG, b(0))", 1, 1), another_call_in_args),
    CASE(("WRAPPER(a)(IGNORED_ARG, (0))", 1, 1), another_value_in_parens),
    CASE(("a(IGNORED_STRUCT_ARG(struct))", 1, 1), with_IGNORED_STRUCT_ARG),
    CASE(("a(xxx, IGNORED_STRUCT_ARG(struct))", 2, 1), IGNORED_STRUCT_ARG_as_2nd_arg),
    CASE(("a(xxx, IGNORED_STRUCT_ARG(struct))", 1, 0), IGNORED_STRUCT_ARG_does_not_ignore_1st_arg))
{
    // arrange
    int result;
    int is_ignored;

    // act
    result = umockautoignoreargs_is_call_argument_ignored(call_str, arg_idx, &is_ignored);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(int, expected_ignored, is_ignored);
}

END_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)
