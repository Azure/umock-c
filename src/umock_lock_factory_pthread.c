// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#include <pthread.h>

#include "umock_c/umockalloc.h"
#include "umock_c/umock_log.h"
#include "umock_c/umock_lock_if.h"               // for UMOCK_C_LOCK_HANDLE
#include "umock_c/umock_lock_factory_default.h"

typedef struct UMOCK_C_LOCK_PTHREAD_TAG
{
    UMOCK_C_LOCK_IF lock_if;
    pthread_rwlock_t rw_lock;
} UMOCK_C_LOCK_PTHREAD;

static void umock_lock_pthreads_acquire_shared(UMOCK_C_LOCK_HANDLE lock)
{
    if (lock == NULL)
    {
        /* Codes_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_010: [ If lock is NULL, umock_lock_pthread_acquire_shared shall return. ]*/
        UMOCK_LOG("Invalid arguments: UMOCK_C_LOCK_HANDLE lock=%p", lock);
    }
    else
    {
        UMOCK_C_LOCK_PTHREAD* umock_c_lock_pthread = (UMOCK_C_LOCK_PTHREAD*)lock;
        /* Codes_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_005: [ umock_lock_pthread_acquire_shared shall acquire the read lock by calling pthread_rwlock_rdlock. ]*/
        if (pthread_rwlock_rdlock(&umock_c_lock_pthread->rw_lock) != 0)
        {
            UMOCK_LOG("pthread_rwlock_rdlock failed");
        }
    }
}

static void umock_lock_pthreads_release_shared(UMOCK_C_LOCK_HANDLE lock)
{
    if (lock == NULL)
    {
        /* Codes_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_011: [ If lock is NULL, umock_lock_pthread_release_shared shall return. ]*/
        UMOCK_LOG("Invalid arguments: UMOCK_C_LOCK_HANDLE lock=%p", lock);
    }
    else
    {
        UMOCK_C_LOCK_PTHREAD* umock_c_lock_pthread = (UMOCK_C_LOCK_PTHREAD*)lock;
        /* Codes_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_006: [ umock_lock_pthread_release_shared shall release the lock that was acquired in shared mode by calling pthread_rwlock_unlock. ]*/
        if (pthread_rwlock_unlock(&umock_c_lock_pthread->rw_lock) != 0)
        {
            UMOCK_LOG("pthread_rwlock_unlock failed");
        }
    }
}

static void umock_lock_pthreads_acquire_exclusive(UMOCK_C_LOCK_HANDLE lock)
{
    if (lock == NULL)
    {
        /* Codes_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_012: [ If lock is NULL, umock_lock_pthread_acquire_exclusive shall return. ]*/
        UMOCK_LOG("Invalid arguments: UMOCK_C_LOCK_HANDLE lock=%p", lock);
    }
    else
    {
        UMOCK_C_LOCK_PTHREAD* umock_c_lock_pthread = (UMOCK_C_LOCK_PTHREAD*)lock;
        /* Codes_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_007: [ umock_lock_pthread_acquire_exclusive shall acquire the lock in exclusive mode by calling pthread_rwlock_wrlock. ]*/
        if (pthread_rwlock_wrlock(&umock_c_lock_pthread->rw_lock) != 0)
        {
            UMOCK_LOG("pthread_rwlock_rdlock failed");
        }
    }
}

static void umock_lock_pthreads_release_exclusive(UMOCK_C_LOCK_HANDLE lock)
{
    if (lock == NULL)
    {
        /* Codes_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_013: [ If lock is NULL, umock_lock_pthread_release_exclusive shall return. ]*/
        UMOCK_LOG("Invalid arguments: UMOCK_C_LOCK_HANDLE lock=%p", lock);
    }
    else
    {
        UMOCK_C_LOCK_PTHREAD* umock_c_lock_pthread = (UMOCK_C_LOCK_PTHREAD*)lock;
        if (pthread_rwlock_unlock(&umock_c_lock_pthread->rw_lock) != 0)
        {
            UMOCK_LOG("pthread_rwlock_unlock failed");
        }
    }
}

static void umock_lock_pthreads_destroy(UMOCK_C_LOCK_HANDLE lock)
{
    if (lock == NULL)
    {
        /* Codes_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_014: [ If lock is NULL, umock_lock_pthread_destroy shall return. ]*/
        UMOCK_LOG("Invalid arguments: UMOCK_C_LOCK_HANDLE lock=%p", lock);
    }
    else
    {
        UMOCK_C_LOCK_PTHREAD* umock_c_lock_pthread = (UMOCK_C_LOCK_PTHREAD*)lock;
        /* Codes_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_001: [ umock_lock_pthread_destroy shall release the resources for the pthread lock by calling pthread_rwlock_destroy. ]*/
        if (pthread_rwlock_destroy(&umock_c_lock_pthread->rw_lock) != 0)
        {
            UMOCK_LOG("pthread_rwlock_destroy failed");
        }

        /* Codes_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_009: [ umock_lock_pthread_destroy shall free the memory associated with the lock. ]*/
        umockalloc_free(umock_c_lock_pthread);
    }
}

UMOCK_C_LOCK_HANDLE umock_lock_factory_create_lock(void* params)
{
    (void)params;

    UMOCK_C_LOCK_HANDLE result;
    /* Codes_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_001: [ umock_lock_factory_create_lock shall allocate memory for the lock. ]*/
    UMOCK_C_LOCK_PTHREAD* rw_lock_pthreads = umockalloc_malloc(sizeof(UMOCK_C_LOCK_PTHREAD));
    if (rw_lock_pthreads == NULL)
    {
        /* Codes_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_004: [ If any error occurs, umock_lock_factory_create_lock shall fail and return NULL. ]*/
        UMOCK_LOG("umockalloc_malloc(%zu) failed", sizeof(UMOCK_C_LOCK_PTHREAD));
    }
    else
    {
        /* Codes_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_003: [ umock_lock_factory_create_lock shall return a lock handle that has the function pointers set to umock_lock_pthread_acquire_shared, umock_lock_pthread_release_shared, umock_lock_pthread_acquire_exclusive, umock_lock_pthread_release_exclusive and umock_lock_pthread_destroy. ]*/
        rw_lock_pthreads->lock_if.acquire_shared = umock_lock_pthreads_acquire_shared;
        rw_lock_pthreads->lock_if.release_shared = umock_lock_pthreads_release_shared;
        rw_lock_pthreads->lock_if.acquire_exclusive = umock_lock_pthreads_acquire_exclusive;
        rw_lock_pthreads->lock_if.release_exclusive = umock_lock_pthreads_release_exclusive;
        rw_lock_pthreads->lock_if.destroy = umock_lock_pthreads_destroy;

        /* Codes_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_002: [] umock_lock_factory_create_lock shall initialize a pthread RW lock that is encapsulated by the new UMOCK_C_LOCK_HANDLE. ]*/
        if (pthread_rwlock_init(&rw_lock_pthreads->rw_lock, NULL) != 0)
        {
            /* Codes_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_004: [ If any error occurs, umock_lock_factory_create_lock shall fail and return NULL. ]*/
            UMOCK_LOG("pthread_rwlock_init failed");
        }
        else
        {
            result = &rw_lock_pthreads->lock_if;
            goto all_ok;
        }

        umockalloc_free(rw_lock_pthreads);
    }

    result = NULL;

all_ok:
    return result;
}
