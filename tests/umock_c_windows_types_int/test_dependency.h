// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TEST_DEPENDENCY_H
#define TEST_DEPENDENCY_H

#include "windows.h"
#include "umock_c/umock_c_prod.h"


    MOCKABLE_FUNCTION(, void, test_dependency_LONG_arg, LONG, LONG_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_LONGLONG_arg, LONGLONG, LONGLONG_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_DWORD_arg, DWORD, DWORD_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_HRESULT_arg, HRESULT, HRESULT_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_BOOL_arg, BOOL, BOOL_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_PVOID_arg, PVOID, PVOID_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_LPCSTR_arg, LPCSTR, LPCSTR_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_LPSECURITY_ATTRIBUTES_arg, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_HANDLE_arg, HANDLE, HANDLE_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_UCHAR_arg, UCHAR, UCHAR_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_PTP_POOL_arg, PTP_POOL, PTP_POOL_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_PTP_CLEANUP_GROUP_arg, PTP_CLEANUP_GROUP, PTP_CLEANUP_GROUP_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_PTP_CALLBACK_ENVIRON_arg, PTP_CALLBACK_ENVIRON, PTP_CALLBACK_ENVIRON_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_PTP_CLEANUP_GROUP_CANCEL_CALLBACK_arg, PTP_CLEANUP_GROUP_CANCEL_CALLBACK, PTP_CLEANUP_GROUP_CANCEL_CALLBACK_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_PTP_IO_arg, PTP_IO, PTP_IO_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_PTP_WIN32_IO_CALLBACK_arg, PTP_WIN32_IO_CALLBACK, PTP_WIN32_IO_CALLBACK_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_PTP_WORK_CALLBACK_arg, PTP_WORK_CALLBACK, PTP_WORK_CALLBACK_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_PTP_WORK_arg, PTP_WORK, PTP_WORK_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_LPCVOID_arg, LPCVOID, LPCVOID_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_LPDWORD_arg, LPDWORD, LPDWORD_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_LPOVERLAPPED_arg, LPOVERLAPPED, LPOVERLAPPED_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_LPVOID_arg, LPVOID, LPVOID_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_PTP_SIMPLE_CALLBACK_arg, PTP_SIMPLE_CALLBACK, PTP_SIMPLE_CALLBACK_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_LPLONG_arg, LPLONG, LPLONG_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_BYTE_arg, BYTE, BYTE_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_BOOLEAN_arg, BOOLEAN, BOOLEAN_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_ULONG_arg, ULONG, ULONG_arg);
    MOCKABLE_FUNCTION(, void, test_dependency_LONG64_arg, LONG64, LONG64_arg);


#endif /* TEST_DEPENDENCY_H */
