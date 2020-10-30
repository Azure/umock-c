// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdint.h>
#include <wchar.h>
#include "windows.h"
#include "macro_utils/macro_utils.h"
#include "umock_c/umock_c.h"
#include "umock_c/umocktypes.h"
#include "umock_c/umocktypes_charptr.h"
#include "umock_c/umocktypes_wcharptr.h"
#include "umock_c/umocktypes_stdint.h"
#include "umock_c/umocktypes_windows.h"
#include "umock_c/umock_log.h"

/* Codes_SRS_UMOCKTYPES_WINDOWS_01_001: [ LONG as an alias of long. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_002: [ LONGLONG as an alias of long long. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_003: [ DWORD as an alias of unsigned long. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_004: [ HRESULT as an alias of LONG. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_025: [ BOOL as an alias of int. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_007: [ PVOID as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_008: [ LPCSTR as an alias of const char*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_010: [ LPSECURITY_ATTRIBUTES as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_011: [ HANDLE as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_012: [ UCHAR as an alias of unsigned char. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_013: [ PTP_POOL as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_014: [ PTP_CLEANUP_GROUP as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_015: [ PTP_CALLBACK_ENVIRON as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_016: [ PTP_CLEANUP_GROUP_CANCEL_CALLBACK as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_017: [ PTP_IO as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_018: [ PTP_WIN32_IO_CALLBACK as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_019: [ PTP_WORK_CALLBACK as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_020: [ PTP_WORK as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_021: [ LPCVOID as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_022: [ LPDWORD as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_023: [ LPOVERLAPPED as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_024: [ LPVOID as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_027: [ PTP_SIMPLE_CALLBACK as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_028: [ LPLONG as an alias of void*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_029: [ BYTE as an alias of unsigned char. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_030: [ BOOLEAN as an alias of BYTE. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_031: [ ULONG as an alias of unsigned long. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_032: [ LPCWSTR as an alias of const wchar_t*. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_01_034: [ LONG64 as an alias of int64_t. ]*/
/* Codes_SRS_UMOCKTYPES_WINDOWS_43_036: [ SHORT as an alias of int16_t. ]*/
#define WINDOWS_TYPES_ALIAS_PAIRS \
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
    LONG64, int64_t ,\
    SHORT, int16_t \

#define REGISTER_ALIAS_PAIR(alias_pair_type, alias_pair_is_type) \
    if ( \
        (result == 0) && \
        (UMOCK_INTERNAL_REGISTER_ALIAS_TYPE(alias_pair_type, alias_pair_is_type) != 0) \
       ) \
    { \
        /* Codes_SRS_UMOCKTYPES_WINDOWS_01_006: [ If registering any of the types fails, umocktypes_windows_register_types shall fail and return a non-zero value. ]*/ \
        UMOCK_LOG("umocktypes_register_alias_type failed for " MU_TOSTRING(alias_pair_type)); \
        result = MU_FAILURE; \
    }

/* Codes_SRS_UMOCKTYPES_WINDOWS_01_001: [ The following Windows types shall be supported out of the box, aliased to their underlying types: ]*/
int umocktypes_windows_register_types(void)
{
    /* Codes_SRS_UMOCKTYPES_WINDOWS_01_005: [ On success, umocktypes_windows_register_types shall return 0. ]*/
    int result;

    /* Codes_SRS_UMOCKTYPES_WINDOWS_01_026: [ umocktypes_windows_register_types shall register the charptr types by calling umocktypes_charptr_register_types. ]*/
    if (umocktypes_charptr_register_types() != 0)
    {
        UMOCK_LOG("umocktypes_charptr_register_types failed");
        result = MU_FAILURE;
    }
    /* Codes_SRS_UMOCKTYPES_WINDOWS_01_033: [ umocktypes_windows_register_types shall register the wcharptr types by calling umocktypes_wcharptr_register_types. ]*/
    else if (umocktypes_wcharptr_register_types() != 0)
    {
        UMOCK_LOG("umocktypes_wcharptr_register_types failed");
        result = MU_FAILURE;
    }
    /* Codes_SRS_UMOCKTYPES_WINDOWS_01_035: [ umocktypes_windows_register_types shall register the stdint types by calling umocktypes_stdint_register_types. ]*/
    else if (umocktypes_stdint_register_types() != 0)
    {
        UMOCK_LOG("umocktypes_stdint_register_types failed");
        result = MU_FAILURE;
    }
    else
    {
        result = 0;

        /* Codes_SRS_UMOCKTYPES_WINDOWS_01_009: [ umocktypes_windows_register_types shall register support for the following alias types: ]*/
        MU_FOR_EACH_2(REGISTER_ALIAS_PAIR, WINDOWS_TYPES_ALIAS_PAIRS);
    }

    return result;
}
