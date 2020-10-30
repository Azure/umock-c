// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifdef __cplusplus
#include <cstdlib>
#include <cwchar>
#else
#include <stdlib.h>
#include <wchar.h>
#endif

#include "macro_utils/macro_utils.h"
#include "testrunnerswitcher.h"
#include "umock_c/umocktypes.h"
#include "umock_c/umocktypes_windows.h"
#include "umock_c/umock_log.h"

void UMOCK_LOG(const char* format, ...)
{
    (void)format;
}

typedef struct EXPECTED_ALIAS_PAIR_TAG
{
    char* type;
    char* is_type;
} EXPECTED_ALIAS_PAIR;

#ifdef __cplusplus
extern "C" {
#endif

typedef struct umocktypes_register_alias_type_CALL_TAG
{
    char* type;
    char* is_type;
} umocktypes_register_alias_type_CALL;

static umocktypes_register_alias_type_CALL* umocktypes_register_alias_type_calls;
static size_t umocktypes_register_alias_type_count;
static size_t when_shall_umocktypes_register_alias_type_call_fail;
static int umocktypes_register_alias_type_result;
static int umocktypes_register_alias_type_fail_call_result;

int umocktypes_register_alias_type(const char* type, const char* is_type)
{
    int result;

    if (when_shall_umocktypes_register_alias_type_call_fail == umocktypes_register_alias_type_count)
    {
        result = umocktypes_register_alias_type_fail_call_result;
    }
    else
    {
        result = umocktypes_register_alias_type_result;
    }

    umocktypes_register_alias_type_CALL* new_calls = (umocktypes_register_alias_type_CALL*)realloc(umocktypes_register_alias_type_calls, sizeof(umocktypes_register_alias_type_CALL) * (umocktypes_register_alias_type_count + 1));
    if (new_calls != NULL)
    {
        umocktypes_register_alias_type_calls = new_calls;
        size_t string_length = strlen(type);
        umocktypes_register_alias_type_calls[umocktypes_register_alias_type_count].type = (char*)malloc(string_length + 1);
        (void)memcpy(umocktypes_register_alias_type_calls[umocktypes_register_alias_type_count].type, type, string_length + 1);
        string_length = strlen(is_type);
        umocktypes_register_alias_type_calls[umocktypes_register_alias_type_count].is_type = (char*)malloc(string_length + 1);
        (void)memcpy(umocktypes_register_alias_type_calls[umocktypes_register_alias_type_count].is_type, is_type, string_length + 1);

        umocktypes_register_alias_type_count++;
    }

    return result;
}

typedef struct umocktypes_charptr_register_types_CALL_TAG
{
    int dummy;
} umocktypes_charptr_register_types_CALL;

static umocktypes_charptr_register_types_CALL* umocktypes_charptr_register_types_calls;
static size_t umocktypes_charptr_register_types_count;
static size_t when_shall_umocktypes_charptr_register_types_call_fail;
static int umocktypes_charptr_register_types_result;
static int umocktypes_charptr_register_types_fail_call_result;

int umocktypes_charptr_register_types(void)
{
    int result;

    if (when_shall_umocktypes_charptr_register_types_call_fail == umocktypes_charptr_register_types_count)
    {
        result = umocktypes_charptr_register_types_fail_call_result;
    }
    else
    {
        result = umocktypes_charptr_register_types_result;
    }

    umocktypes_charptr_register_types_CALL* new_calls = (umocktypes_charptr_register_types_CALL*)realloc(umocktypes_charptr_register_types_calls, sizeof(umocktypes_charptr_register_types_CALL) * (umocktypes_charptr_register_types_count + 1));
    if (new_calls != NULL)
    {
        umocktypes_charptr_register_types_calls = new_calls;
        umocktypes_charptr_register_types_count++;
    }

    return result;
}

typedef struct umocktypes_wcharptr_register_types_CALL_TAG
{
    int dummy;
} umocktypes_wcharptr_register_types_CALL;

static umocktypes_wcharptr_register_types_CALL* umocktypes_wcharptr_register_types_calls;
static size_t umocktypes_wcharptr_register_types_count;
static size_t when_shall_umocktypes_wcharptr_register_types_call_fail;
static int umocktypes_wcharptr_register_types_result;
static int umocktypes_wcharptr_register_types_fail_call_result;

int umocktypes_wcharptr_register_types(void)
{
    int result;

    if (when_shall_umocktypes_wcharptr_register_types_call_fail == umocktypes_wcharptr_register_types_count)
    {
        result = umocktypes_wcharptr_register_types_fail_call_result;
    }
    else
    {
        result = umocktypes_wcharptr_register_types_result;
    }

    umocktypes_wcharptr_register_types_CALL* new_calls = (umocktypes_wcharptr_register_types_CALL*)realloc(umocktypes_wcharptr_register_types_calls, sizeof(umocktypes_wcharptr_register_types_CALL) * (umocktypes_wcharptr_register_types_count + 1));
    if (new_calls != NULL)
    {
        umocktypes_wcharptr_register_types_calls = new_calls;
        umocktypes_wcharptr_register_types_count++;
    }

    return result;
}

typedef struct umocktypes_stdint_register_types_CALL_TAG
{
    int dummy;
} umocktypes_stdint_register_types_CALL;

static umocktypes_stdint_register_types_CALL* umocktypes_stdint_register_types_calls;
static size_t umocktypes_stdint_register_types_count;
static size_t when_shall_umocktypes_stdint_register_types_call_fail;
static int umocktypes_stdint_register_types_result;
static int umocktypes_stdint_register_types_fail_call_result;

int umocktypes_stdint_register_types(void)
{
    int result;

    if (when_shall_umocktypes_stdint_register_types_call_fail == umocktypes_stdint_register_types_count)
    {
        result = umocktypes_stdint_register_types_fail_call_result;
    }
    else
    {
        result = umocktypes_stdint_register_types_result;
    }

    umocktypes_stdint_register_types_CALL* new_calls = (umocktypes_stdint_register_types_CALL*)realloc(umocktypes_stdint_register_types_calls, sizeof(umocktypes_stdint_register_types_CALL) * (umocktypes_stdint_register_types_count + 1));
    if (new_calls != NULL)
    {
        umocktypes_stdint_register_types_calls = new_calls;
        umocktypes_stdint_register_types_count++;
    }

    return result;
}

#ifdef __cplusplus
}
#endif

static void init_mocked_calls(void)
{
    umocktypes_register_alias_type_result = 0;
    umocktypes_register_alias_type_fail_call_result = 0;
    umocktypes_register_alias_type_calls = NULL;
    umocktypes_register_alias_type_count = 0;
    when_shall_umocktypes_register_alias_type_call_fail = 0;

    umocktypes_charptr_register_types_result = 0;
    umocktypes_charptr_register_types_fail_call_result = 0;
    umocktypes_charptr_register_types_calls = NULL;
    umocktypes_charptr_register_types_count = 0;
    when_shall_umocktypes_charptr_register_types_call_fail = 0;

    umocktypes_wcharptr_register_types_result = 0;
    umocktypes_wcharptr_register_types_fail_call_result = 0;
    umocktypes_wcharptr_register_types_calls = NULL;
    umocktypes_wcharptr_register_types_count = 0;
    when_shall_umocktypes_wcharptr_register_types_call_fail = 0;

    umocktypes_stdint_register_types_result = 0;
    umocktypes_stdint_register_types_fail_call_result = 0;
    umocktypes_stdint_register_types_calls = NULL;
    umocktypes_stdint_register_types_count = 0;
    when_shall_umocktypes_stdint_register_types_call_fail = 0;
}

static void free_mocked_calls(void)
{
    size_t i;

    for (i = 0; i < umocktypes_register_alias_type_count; i++)
    {
        free(umocktypes_register_alias_type_calls[i].type);
        free(umocktypes_register_alias_type_calls[i].is_type);
    }
    umocktypes_register_alias_type_count = 0;

    if (umocktypes_register_alias_type_calls != NULL)
    {
        free(umocktypes_register_alias_type_calls);
        umocktypes_register_alias_type_calls = NULL;
    }

    if (umocktypes_charptr_register_types_calls != NULL)
    {
        free(umocktypes_charptr_register_types_calls);
        umocktypes_charptr_register_types_calls = NULL;
    }

    if (umocktypes_wcharptr_register_types_calls != NULL)
    {
        free(umocktypes_wcharptr_register_types_calls);
        umocktypes_wcharptr_register_types_calls = NULL;
    }

    if (umocktypes_stdint_register_types_calls != NULL)
    {
        free(umocktypes_stdint_register_types_calls);
        umocktypes_stdint_register_types_calls = NULL;
    }
}

static TEST_MUTEX_HANDLE test_mutex;
static TEST_MUTEX_HANDLE global_mutex;

BEGIN_TEST_SUITE(umocktypes_windows_unittests)

TEST_SUITE_INITIALIZE(suite_init)
{
    test_mutex = TEST_MUTEX_CREATE();
    ASSERT_IS_NOT_NULL(test_mutex);
}

TEST_SUITE_CLEANUP(suite_cleanup)
{
    TEST_MUTEX_DESTROY(test_mutex);
}

TEST_FUNCTION_INITIALIZE(test_function_init)
{
    int mutex_acquire_result = TEST_MUTEX_ACQUIRE(test_mutex);
    ASSERT_ARE_EQUAL(int, 0, mutex_acquire_result);

    init_mocked_calls();
}

TEST_FUNCTION_CLEANUP(test_function_cleanup)
{
    free_mocked_calls();

    TEST_MUTEX_RELEASE(test_mutex);
}

/* umocktypes_windows_register_types */

#define EXPECTED_ALIAS_PAIRS \
    LONG, long, \
    LONGLONG, long long, \
    DWORD, unsigned long, \
    HRESULT, LONG, \
    BOOL, int, \
    PVOID, void*, \
    LPCSTR, const char*, \
    LPSECURITY_ATTRIBUTES, void*, \
    HANDLE, void*, \
    UCHAR, unsigned char, \
    PTP_POOL, void*, \
    PTP_CLEANUP_GROUP, void*, \
    PTP_CALLBACK_ENVIRON, void*, \
    PTP_CLEANUP_GROUP_CANCEL_CALLBACK, void*, \
    PTP_IO, void*, \
    PTP_WIN32_IO_CALLBACK, void*, \
    PTP_WORK_CALLBACK, void*, \
    PTP_WORK, void*, \
    LPCVOID, void*, \
    LPDWORD, void*, \
    LPOVERLAPPED, void*, \
    LPVOID, void*, \
    PTP_SIMPLE_CALLBACK, void*, \
    LPLONG, void*, \
    BYTE, unsigned char, \
    BOOLEAN, BYTE, \
    ULONG, unsigned long, \
    LPCWSTR, const wchar_t*, \
    LONG64, int64_t, \
    SHORT, int16_t \

#define ASSERT_EXPECTED_ALIAS_PAIR(alias_pair_type, alias_pair_is_type) \
    ASSERT_ARE_EQUAL(char_ptr, MU_TOSTRING(alias_pair_type), umocktypes_register_alias_type_calls[i].type); \
    ASSERT_ARE_EQUAL(char_ptr, MU_TOSTRING(alias_pair_is_type), umocktypes_register_alias_type_calls[i++].is_type); \

/* Tests_SRS_UMOCKTYPES_WINDOWS_01_026: [ umocktypes_windows_register_types shall register the charptr types by calling umocktypes_charptr_register_types. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_033: [ umocktypes_windows_register_types shall register the wcharptr types by calling umocktypes_wcharptr_register_types. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_009: [ umocktypes_windows_register_types shall register support for the following alias types: ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_035: [ umocktypes_windows_register_types shall register the stdint types by calling umocktypes_stdint_register_types. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_001: [ LONG as an alias of long. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_002: [ LONGLONG as an alias of long long. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_003: [ DWORD as an alias of unsigned long. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_004: [ HRESULT as an alias of LONG. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_025: [ BOOL as an alias of int. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_007: [ PVOID as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_008: [ LPCSTR as an alias of const char*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_010: [ LPSECURITY_ATTRIBUTES as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_011: [ HANDLE as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_012: [ UCHAR as an alias of unsigned char. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_013: [ PTP_POOL as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_014: [ PTP_CLEANUP_GROUP as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_015: [ PTP_CALLBACK_ENVIRON as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_016: [ PTP_CLEANUP_GROUP_CANCEL_CALLBACK as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_017: [ PTP_IO as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_018: [ PTP_WIN32_IO_CALLBACK as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_019: [ PTP_WORK_CALLBACK as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_020: [ PTP_WORK as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_021: [ LPCVOID as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_022: [ LPDWORD as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_023: [ LPOVERLAPPED as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_024: [ LPVOID as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_027: [ PTP_SIMPLE_CALLBACK as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_028: [ LPLONG as an alias of void*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_029: [ BYTE as an alias of unsigned char. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_030: [ BOOLEAN as an alias of BYTE. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_031: [ ULONG as an alias of unsigned long. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_032: [ LPCWSTR as an alias of const wchar_t*. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_034: [ LONG64 as an alias of int64_t. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_43_036: [ SHORT as an alias of int16_t. ]*/
/* Tests_SRS_UMOCKTYPES_WINDOWS_01_005: [ On success, umocktypes_windows_register_types shall return 0. ]*/
TEST_FUNCTION(umocktypes_windows_register_types_registers_all_types)
{
    // arrange
    int result;

    // act
    result = umocktypes_windows_register_types();

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    int i = 0;
    ASSERT_ARE_EQUAL(size_t, MU_DIV2(MU_COUNT_ARG(EXPECTED_ALIAS_PAIRS)), umocktypes_register_alias_type_count);
    MU_FOR_EACH_2(ASSERT_EXPECTED_ALIAS_PAIR, EXPECTED_ALIAS_PAIRS);
    ASSERT_ARE_EQUAL(size_t, 1, umocktypes_charptr_register_types_count);
    ASSERT_ARE_EQUAL(size_t, 1, umocktypes_wcharptr_register_types_count);
    ASSERT_ARE_EQUAL(size_t, 1, umocktypes_stdint_register_types_count);
}

/* Tests_SRS_UMOCKTYPES_WINDOWS_01_006: [ If registering any of the types fails, umocktypes_windows_register_types shall fail and return a non-zero value. ]*/
TEST_FUNCTION(when_underlying_calls_fail_umocktypes_windows_register_types_fails)
{
    // arrange
    int result;
    size_t i;

    for (i = 0; i < MU_DIV2(MU_COUNT_ARG(EXPECTED_ALIAS_PAIRS)); i++)
    {
        init_mocked_calls();
        when_shall_umocktypes_register_alias_type_call_fail = i;
        umocktypes_register_alias_type_fail_call_result = MU_FAILURE;

        // act
        result = umocktypes_windows_register_types();

        // assert
        ASSERT_ARE_NOT_EQUAL(int, 0, result);

        free_mocked_calls();
    }
}

/* Tests_SRS_UMOCKTYPES_WINDOWS_01_006: [ If registering any of the types fails, umocktypes_windows_register_types shall fail and return a non-zero value. ]*/
TEST_FUNCTION(when_umocktypes_charptr_register_types_fails_umocktypes_windows_register_types_fails)
{
    // arrange
    int result;

    when_shall_umocktypes_charptr_register_types_call_fail = 0;
    umocktypes_charptr_register_types_fail_call_result = MU_FAILURE;

    // act
    result = umocktypes_windows_register_types();

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
}

END_TEST_SUITE(umocktypes_windows_unittests)
