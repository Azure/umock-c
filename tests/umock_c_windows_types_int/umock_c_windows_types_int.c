// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.


#ifdef __cplusplus
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#else
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#endif

#include "macro_utils/macro_utils.h"
#include "testrunnerswitcher.h"

#include "umock_c/umocktypes_windows.h"

#include "umock_c/umock_c.h"
#define ENABLE_MOCKS
#include "test_dependency.h"
#undef ENABLE_MOCKS

static TEST_MUTEX_HANDLE test_mutex;

MU_DEFINE_ENUM_STRINGS(UMOCK_C_ERROR_CODE, UMOCK_C_ERROR_CODE_VALUES);

static void test_on_umock_c_error(UMOCK_C_ERROR_CODE error_code)
{
    ASSERT_FAIL("test_on_umock_c_error called with %" PRI_MU_ENUM "", MU_ENUM_VALUE(UMOCK_C_ERROR_CODE, error_code));
}

static char* build_calls_string(void)
{
    char* result;
    const char* test_expected_string =
        "[test_dependency_LONG_arg(42)]"
        "[test_dependency_LONGLONG_arg(4242)]"
        "[test_dependency_DWORD_arg(42)]"
        "[test_dependency_HRESULT_arg(1)]"
        "[test_dependency_BOOL_arg(1)]"
        "[test_dependency_PVOID_arg(%p)]"
        "[test_dependency_LPCSTR_arg(\"test\")]"
        "[test_dependency_LPSECURITY_ATTRIBUTES_arg(%p)]"
        "[test_dependency_HANDLE_arg(%p)]"
        "[test_dependency_UCHAR_arg(42)]"
        "[test_dependency_PTP_POOL_arg(%p)]"
        "[test_dependency_PTP_CLEANUP_GROUP_arg(%p)]"
        "[test_dependency_PTP_CALLBACK_ENVIRON_arg(%p)]"
        "[test_dependency_PTP_CLEANUP_GROUP_CANCEL_CALLBACK_arg(%p)]"
        "[test_dependency_PTP_IO_arg(%p)]"
        "[test_dependency_PTP_WIN32_IO_CALLBACK_arg(%p)]"
        "[test_dependency_PTP_WORK_CALLBACK_arg(%p)]"
        "[test_dependency_PTP_WORK_arg(%p)]"
        "[test_dependency_LPCVOID_arg(%p)]"
        "[test_dependency_LPDWORD_arg(%p)]"
        "[test_dependency_LPVOID_arg(%p)]"
        "[test_dependency_LPOVERLAPPED_arg(%p)]"
        "[test_dependency_PTP_SIMPLE_CALLBACK_arg(%p)]"
        "[test_dependency_LPLONG_arg(%p)]"
        "[test_dependency_BYTE_arg(43)]"
        "[test_dependency_BOOLEAN_arg(2)]"
        "[test_dependency_ULONG_arg(44)]"
        "[test_dependency_LONG64_arg(45)]";

    int needed_bytes = snprintf(NULL, 0, test_expected_string,
        (void*)0x4242, (void*)0x4243, (void*)0x4244,
        (void*)0x4245, (void*)0x4246, (void*)0x4247,
        (void*)0x4248, (void*)0x4249, (void*)0x424A,
        (void*)0x424B, (void*)0x424C, (void*)0x424D,
        (void*)0x424E, (void*)0x424F, (void*)0x4250,
        (void*)0x4251, (void*)0x4252);
    ASSERT_IS_TRUE(needed_bytes > 0);

    result = (char*)malloc(needed_bytes + 1);
    ASSERT_IS_NOT_NULL(result);

    int snprintf_result = snprintf(result, needed_bytes + 1, test_expected_string,
        (void*)0x4242, (void*)0x4243, (void*)0x4244,
        (void*)0x4245, (void*)0x4246, (void*)0x4247,
        (void*)0x4248, (void*)0x4249, (void*)0x424A,
        (void*)0x424B, (void*)0x424C, (void*)0x424D,
        (void*)0x424E, (void*)0x424F, (void*)0x4250,
        (void*)0x4251, (void*)0x4252);
    ASSERT_IS_TRUE(snprintf_result > 0);

    return result;
}

BEGIN_TEST_SUITE(umock_c_windows_types_int_tests)

TEST_SUITE_INITIALIZE(suite_init)
{
    test_mutex = TEST_MUTEX_CREATE();
    ASSERT_IS_NOT_NULL(test_mutex);

    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error), "umock_c_init");
    ASSERT_ARE_EQUAL(int, 0, umocktypes_windows_register_types(), "umocktypes_windows_register_types");
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

/* Tests_SRS_UMOCKTYPES_WINDOWS_01_001: [ The following Windows types shall be supported out of the box, aliased to their underlying types: ]*/
TEST_FUNCTION(unmatched_expected_calls_with_windows_args_are_reported)
{
    // arrange

    // act
    STRICT_EXPECTED_CALL(test_dependency_LONG_arg(42));
    STRICT_EXPECTED_CALL(test_dependency_LONGLONG_arg(4242));
    STRICT_EXPECTED_CALL(test_dependency_DWORD_arg(42));
    STRICT_EXPECTED_CALL(test_dependency_HRESULT_arg(1));
    STRICT_EXPECTED_CALL(test_dependency_BOOL_arg(TRUE));
    STRICT_EXPECTED_CALL(test_dependency_PVOID_arg((PVOID)0x4242));
    STRICT_EXPECTED_CALL(test_dependency_LPCSTR_arg("test"));
    STRICT_EXPECTED_CALL(test_dependency_LPSECURITY_ATTRIBUTES_arg((LPSECURITY_ATTRIBUTES)0x4243));
    STRICT_EXPECTED_CALL(test_dependency_HANDLE_arg((HANDLE)0x4244));
    STRICT_EXPECTED_CALL(test_dependency_UCHAR_arg(42));
    STRICT_EXPECTED_CALL(test_dependency_PTP_POOL_arg((PTP_POOL)0x4245));
    STRICT_EXPECTED_CALL(test_dependency_PTP_CLEANUP_GROUP_arg((PTP_CLEANUP_GROUP)0x4246));
    STRICT_EXPECTED_CALL(test_dependency_PTP_CALLBACK_ENVIRON_arg((PTP_CALLBACK_ENVIRON)0x4247));
    STRICT_EXPECTED_CALL(test_dependency_PTP_CLEANUP_GROUP_CANCEL_CALLBACK_arg((PTP_CLEANUP_GROUP_CANCEL_CALLBACK)0x4248));
    STRICT_EXPECTED_CALL(test_dependency_PTP_IO_arg((PTP_IO)0x4249));
    STRICT_EXPECTED_CALL(test_dependency_PTP_WIN32_IO_CALLBACK_arg((PTP_WIN32_IO_CALLBACK)0x424A));
    STRICT_EXPECTED_CALL(test_dependency_PTP_WORK_CALLBACK_arg((PTP_WORK_CALLBACK)0x424B));
    STRICT_EXPECTED_CALL(test_dependency_PTP_WORK_arg((PTP_WORK)0x424C));
    STRICT_EXPECTED_CALL(test_dependency_LPCVOID_arg((LPCVOID)0x424D));
    STRICT_EXPECTED_CALL(test_dependency_LPDWORD_arg((LPDWORD)0x424E));
    STRICT_EXPECTED_CALL(test_dependency_LPVOID_arg((LPVOID)0x424F));
    STRICT_EXPECTED_CALL(test_dependency_LPOVERLAPPED_arg((LPOVERLAPPED)0x4250));
    STRICT_EXPECTED_CALL(test_dependency_PTP_SIMPLE_CALLBACK_arg((PTP_SIMPLE_CALLBACK)0x4251));
    STRICT_EXPECTED_CALL(test_dependency_LPLONG_arg((LPLONG)0x4252));
    STRICT_EXPECTED_CALL(test_dependency_BYTE_arg(43));
    STRICT_EXPECTED_CALL(test_dependency_BOOLEAN_arg(2));
    STRICT_EXPECTED_CALL(test_dependency_ULONG_arg(44));
    STRICT_EXPECTED_CALL(test_dependency_LONG64_arg(45));

    // assert
    char* calls_string = build_calls_string();
    ASSERT_ARE_EQUAL(char_ptr, calls_string, umock_c_get_expected_calls());
    ASSERT_ARE_EQUAL(char_ptr, "", umock_c_get_actual_calls());

    // cleanup
    free(calls_string);
}

/* Tests_SRS_UMOCKTYPES_WINDOWS_01_001: [ The following Windows types shall be supported out of the box, aliased to their underlying types: ]*/
TEST_FUNCTION(unmatched_actual_calls_with_windows_args_are_reported)
{
    // arrange

    // act
    test_dependency_LONG_arg(42);
    test_dependency_LONGLONG_arg(4242);
    test_dependency_DWORD_arg(42);
    test_dependency_HRESULT_arg(1);
    test_dependency_BOOL_arg(TRUE);
    test_dependency_PVOID_arg((PVOID)0x4242);
    test_dependency_LPCSTR_arg("test");
    test_dependency_LPSECURITY_ATTRIBUTES_arg((LPSECURITY_ATTRIBUTES)0x4243);
    test_dependency_HANDLE_arg((HANDLE)0x4244);
    test_dependency_UCHAR_arg(42);
    test_dependency_PTP_POOL_arg((PTP_POOL)0x4245);
    test_dependency_PTP_CLEANUP_GROUP_arg((PTP_CLEANUP_GROUP)0x4246);
    test_dependency_PTP_CALLBACK_ENVIRON_arg((PTP_CALLBACK_ENVIRON)0x4247);
    test_dependency_PTP_CLEANUP_GROUP_CANCEL_CALLBACK_arg((PTP_CLEANUP_GROUP_CANCEL_CALLBACK)0x4248);
    test_dependency_PTP_IO_arg((PTP_IO)0x4249);
    test_dependency_PTP_WIN32_IO_CALLBACK_arg((PTP_WIN32_IO_CALLBACK)0x424A);
    test_dependency_PTP_WORK_CALLBACK_arg((PTP_WORK_CALLBACK)0x424B);
    test_dependency_PTP_WORK_arg((PTP_WORK)0x424C);
    test_dependency_LPCVOID_arg((LPCVOID)0x424D);
    test_dependency_LPDWORD_arg((LPDWORD)0x424E);
    test_dependency_LPVOID_arg((LPVOID)0x424F);
    test_dependency_LPOVERLAPPED_arg((LPOVERLAPPED)0x4250);
    test_dependency_PTP_SIMPLE_CALLBACK_arg((PTP_SIMPLE_CALLBACK)0x4251);
    test_dependency_LPLONG_arg((LPLONG)0x4252);
    test_dependency_BYTE_arg(43);
    test_dependency_BOOLEAN_arg(2);
    test_dependency_ULONG_arg(44);
    test_dependency_LONG64_arg(45);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "", umock_c_get_expected_calls());
    char* calls_string = build_calls_string();
    ASSERT_ARE_EQUAL(char_ptr, calls_string, umock_c_get_actual_calls());

    // cleanup
    free(calls_string);
}

/* Tests_SRS_UMOCKTYPES_WINDOWS_01_001: [ The following Windows types shall be supported out of the box, aliased to their underlying types: ]*/
TEST_FUNCTION(matched_calls_with_windows_args_are_not_reported)
{
    // arrange
    STRICT_EXPECTED_CALL(test_dependency_LONG_arg(42));
    STRICT_EXPECTED_CALL(test_dependency_LONGLONG_arg(4242));
    STRICT_EXPECTED_CALL(test_dependency_DWORD_arg(42));
    STRICT_EXPECTED_CALL(test_dependency_HRESULT_arg(1));
    STRICT_EXPECTED_CALL(test_dependency_BOOL_arg(TRUE));
    STRICT_EXPECTED_CALL(test_dependency_PVOID_arg((PVOID)0x4242));
    STRICT_EXPECTED_CALL(test_dependency_LPCSTR_arg("test"));
    STRICT_EXPECTED_CALL(test_dependency_LPSECURITY_ATTRIBUTES_arg((LPSECURITY_ATTRIBUTES)0x4243));
    STRICT_EXPECTED_CALL(test_dependency_HANDLE_arg((HANDLE)0x4244));
    STRICT_EXPECTED_CALL(test_dependency_UCHAR_arg(42));
    STRICT_EXPECTED_CALL(test_dependency_PTP_POOL_arg((PTP_POOL)0x4245));
    STRICT_EXPECTED_CALL(test_dependency_PTP_CLEANUP_GROUP_arg((PTP_CLEANUP_GROUP)0x4246));
    STRICT_EXPECTED_CALL(test_dependency_PTP_CALLBACK_ENVIRON_arg((PTP_CALLBACK_ENVIRON)0x4247));
    STRICT_EXPECTED_CALL(test_dependency_PTP_CLEANUP_GROUP_CANCEL_CALLBACK_arg((PTP_CLEANUP_GROUP_CANCEL_CALLBACK)0x4248));
    STRICT_EXPECTED_CALL(test_dependency_PTP_IO_arg((PTP_IO)0x4249));
    STRICT_EXPECTED_CALL(test_dependency_PTP_WIN32_IO_CALLBACK_arg((PTP_WIN32_IO_CALLBACK)0x424A));
    STRICT_EXPECTED_CALL(test_dependency_PTP_WORK_CALLBACK_arg((PTP_WORK_CALLBACK)0x424B));
    STRICT_EXPECTED_CALL(test_dependency_PTP_WORK_arg((PTP_WORK)0x424C));
    STRICT_EXPECTED_CALL(test_dependency_LPCVOID_arg((LPCVOID)0x424D));
    STRICT_EXPECTED_CALL(test_dependency_LPDWORD_arg((LPDWORD)0x424E));
    STRICT_EXPECTED_CALL(test_dependency_LPVOID_arg((LPVOID)0x424F));
    STRICT_EXPECTED_CALL(test_dependency_LPOVERLAPPED_arg((LPOVERLAPPED)0x4250));
    STRICT_EXPECTED_CALL(test_dependency_PTP_SIMPLE_CALLBACK_arg((PTP_SIMPLE_CALLBACK)0x4251));
    STRICT_EXPECTED_CALL(test_dependency_LPLONG_arg((LPLONG)0x4252));
    STRICT_EXPECTED_CALL(test_dependency_BYTE_arg(43));
    STRICT_EXPECTED_CALL(test_dependency_BOOLEAN_arg(2));
    STRICT_EXPECTED_CALL(test_dependency_ULONG_arg(44));
    STRICT_EXPECTED_CALL(test_dependency_LONG64_arg(45));

    // act
    test_dependency_LONG_arg(42);
    test_dependency_LONGLONG_arg(4242);
    test_dependency_DWORD_arg(42);
    test_dependency_HRESULT_arg(1);
    test_dependency_BOOL_arg(TRUE);
    test_dependency_PVOID_arg((PVOID)0x4242);
    test_dependency_LPCSTR_arg("test");
    test_dependency_LPSECURITY_ATTRIBUTES_arg((LPSECURITY_ATTRIBUTES)0x4243);
    test_dependency_HANDLE_arg((HANDLE)0x4244);
    test_dependency_UCHAR_arg(42);
    test_dependency_PTP_POOL_arg((PTP_POOL)0x4245);
    test_dependency_PTP_CLEANUP_GROUP_arg((PTP_CLEANUP_GROUP)0x4246);
    test_dependency_PTP_CALLBACK_ENVIRON_arg((PTP_CALLBACK_ENVIRON)0x4247);
    test_dependency_PTP_CLEANUP_GROUP_CANCEL_CALLBACK_arg((PTP_CLEANUP_GROUP_CANCEL_CALLBACK)0x4248);
    test_dependency_PTP_IO_arg((PTP_IO)0x4249);
    test_dependency_PTP_WIN32_IO_CALLBACK_arg((PTP_WIN32_IO_CALLBACK)0x424A);
    test_dependency_PTP_WORK_CALLBACK_arg((PTP_WORK_CALLBACK)0x424B);
    test_dependency_PTP_WORK_arg((PTP_WORK)0x424C);
    test_dependency_LPCVOID_arg((LPCVOID)0x424D);
    test_dependency_LPDWORD_arg((LPDWORD)0x424E);
    test_dependency_LPVOID_arg((LPVOID)0x424F);
    test_dependency_LPOVERLAPPED_arg((LPOVERLAPPED)0x4250);
    test_dependency_PTP_SIMPLE_CALLBACK_arg((PTP_SIMPLE_CALLBACK)0x4251);
    test_dependency_LPLONG_arg((LPLONG)0x4252);
    test_dependency_BYTE_arg(43);
    test_dependency_BOOLEAN_arg(2);
    test_dependency_ULONG_arg(44);
    test_dependency_LONG64_arg(45);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "", umock_c_get_expected_calls());
    ASSERT_ARE_EQUAL(char_ptr, "", umock_c_get_actual_calls());
}

END_TEST_SUITE(umock_c_windows_types_int_tests)
