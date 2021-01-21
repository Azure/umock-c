// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stddef.h>                              // for NULL

#include "windows.h"

#include "umock_c/umockalloc.h"
#include "umock_c/umock_log.h"
#include "umock_c/umock_lock_if.h"               // for UMOCK_C_LOCK_HANDLE
#include "umock_c/umock_lock_factory_default.h"

typedef struct UMOCK_C_LOCK_WINDOWS_TAG
{
    UMOCK_C_LOCK_IF lock_if;
    SRWLOCK srw_lock;
} UMOCK_C_LOCK_WINDOWS;

static void umock_lock_windows_acquire_shared(UMOCK_C_LOCK_HANDLE lock)
{
    if (lock == NULL)
    {
        /* Codes_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_010: [ If lock is NULL, umock_lock_windows_acquire_shared shall return. ]*/
        UMOCK_LOG("Invalid arguments: UMOCK_C_LOCK_HANDLE lock=%p", lock);
    }
    else
    {
        UMOCK_C_LOCK_WINDOWS* wmock_c_lock_windows = (UMOCK_C_LOCK_WINDOWS*)lock;

        /* Codes_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_005: [ umock_lock_windows_acquire_shared shall acquire the lock in shared mode by calling AcquireSRWLockShared. ]*/
        AcquireSRWLockShared(&wmock_c_lock_windows->srw_lock);
    }
}

static void umock_lock_windows_release_shared(UMOCK_C_LOCK_HANDLE lock)
{
    if (lock == NULL)
    {
        /* Codes_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_011: [ If lock is NULL, umock_lock_windows_release_shared shall return. ]*/
        UMOCK_LOG("Invalid arguments: UMOCK_C_LOCK_HANDLE lock=%p", lock);
    }
    else
    {
        UMOCK_C_LOCK_WINDOWS* wmock_c_lock_windows = (UMOCK_C_LOCK_WINDOWS*)lock;

        /* Codes_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_006: [ umock_lock_windows_release_shared shall release the lock that was acquired in shared mode by calling ReleaseSRWLockShared. ]*/
        ReleaseSRWLockShared(&wmock_c_lock_windows->srw_lock);
    }
}

static void umock_lock_windows_acquire_exclusive(UMOCK_C_LOCK_HANDLE lock)
{
    if (lock == NULL)
    {
        /* Codes_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_012: [ If lock is NULL, umock_lock_windows_acquire_exclusive shall return. ]*/
        UMOCK_LOG("Invalid arguments: UMOCK_C_LOCK_HANDLE lock=%p", lock);
    }
    else
    {
        UMOCK_C_LOCK_WINDOWS* wmock_c_lock_windows = (UMOCK_C_LOCK_WINDOWS*)lock;

        /* Codes_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_007: [ umock_lock_windows_acquire_exclusive shall acquire the lock in exclusive mode by calling AcquireSRWLockExclusive. ]*/
        AcquireSRWLockExclusive(&wmock_c_lock_windows->srw_lock);
    }
}

static void umock_lock_windows_release_exclusive(UMOCK_C_LOCK_HANDLE lock)
{
    if (lock == NULL)
    {
        /* Codes_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_013: [ If lock is NULL, umock_lock_windows_release_exclusive shall return. ]*/
        UMOCK_LOG("Invalid arguments: UMOCK_C_LOCK_HANDLE lock=%p", lock);
    }
    else
    {
        UMOCK_C_LOCK_WINDOWS* wmock_c_lock_windows = (UMOCK_C_LOCK_WINDOWS*)lock;

        /* Codes_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_008: [ umock_lock_windows_release_exclusive shall release the lock that was acquired in exclusive mode by calling ReleaseSRWLockExclusive. ]*/
        ReleaseSRWLockExclusive(&wmock_c_lock_windows->srw_lock);
    }
}

static void umock_lock_windows_destroy(UMOCK_C_LOCK_HANDLE lock)
{
    if (lock == NULL)
    {
        /* Codes_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_014: [ If lock is NULL, umock_lock_windows_destroy shall return. ]*/
        UMOCK_LOG("Invalid arguments: UMOCK_C_LOCK_HANDLE lock=%p", lock);
    }
    else
    {
        UMOCK_C_LOCK_WINDOWS* wmock_c_lock_windows = (UMOCK_C_LOCK_WINDOWS*)lock;

        /* Codes_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_009: [ umock_lock_windows_destroy shall free the memory associated with the lock. ]*/
        umockalloc_free(wmock_c_lock_windows);
    }
}

UMOCK_C_LOCK_HANDLE umock_lock_factory_create_lock(void* params)
{
    (void)params;

    UMOCK_C_LOCK_HANDLE result;
    /* Codes_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_001: [ umock_lock_factory_create_lock shall allocate memory for the lock. ]*/
    UMOCK_C_LOCK_WINDOWS* srw_lock_windows = umockalloc_malloc(sizeof(UMOCK_C_LOCK_WINDOWS));
    if (srw_lock_windows == NULL)
    {
        /* Codes_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_004: [ If any error occurs, umock_lock_factory_create_lock shall fail and return NULL. ]*/
        UMOCK_LOG("umockalloc_malloc(%zu) failed", sizeof(UMOCK_C_LOCK_WINDOWS));
        result = NULL;
    }
    else
    {
        /* Codes_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_003: [ umock_lock_factory_create_lock shall return a lock handle that has the function pointers set to umock_lock_windows_acquire_shared, umock_lock_windows_release_shared, umock_lock_windows_acquire_exclusive, umock_lock_windows_release_exclusive and umock_lock_windows_destroy. ]*/
        srw_lock_windows->lock_if.acquire_shared = umock_lock_windows_acquire_shared;
        srw_lock_windows->lock_if.release_shared = umock_lock_windows_release_shared;
        srw_lock_windows->lock_if.acquire_exclusive = umock_lock_windows_acquire_exclusive;
        srw_lock_windows->lock_if.release_exclusive = umock_lock_windows_release_exclusive;
        srw_lock_windows->lock_if.destroy = umock_lock_windows_destroy;

        /* Codes_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_002: [ umock_lock_factory_create_lock shall initialize a SRW lock that is encapsulated by the new UMOCK_C_LOCK_HANDLE. ]*/
        InitializeSRWLock(&srw_lock_windows->srw_lock);

        result = &srw_lock_windows->lock_if;
    }

    return result;
}
