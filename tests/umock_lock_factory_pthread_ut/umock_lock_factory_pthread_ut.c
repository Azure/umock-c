// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include <pthread.h>

// TEST_DEFINE_ENUM_TYPE will use wchar.h, which we technically get from testrunnerswitcher.h
// IWYU pragma: no_include <wchar.h>
#include "testrunnerswitcher.h"

#include "umock_c/umock_lock_factory_default.h"
#include "umock_c/umock_lock_if.h"               // for UMOCK_C_LOCK_IF_TAG
#include "umock_c/umock_log.h"

void UMOCK_LOG(const char* format, ...)
{
    (void)format;
}

static size_t malloc_call_count;
static size_t when_shall_malloc_fail;

typedef struct mock_malloc_CALL_TAG
{
    size_t size;
} mock_malloc_CALL;

typedef struct mock_free_CALL_TAG
{
    void* ptr;
} mock_free_CALL;

typedef struct mock_pthread_rwlock_init_CALL_TAG
{
    pthread_rwlock_t *rwlock;
    const pthread_rwlockattr_t *attr;
} mock_pthread_rwlock_init_CALL;

typedef struct mock_pthread_rwlock_rdlock_CALL_TAG
{
    void* rwlock;
} mock_pthread_rwlock_rdlock_CALL;

typedef struct mock_pthread_rwlock_unlock_CALL_TAG
{
    void* rwlock;
} mock_pthread_rwlock_unlock_CALL;

typedef struct mock_pthread_rwlock_wrlock_CALL_TAG
{
    void* rwlock;
} mock_pthread_rwlock_wrlock_CALL;

typedef struct mock_pthread_rwlock_destroy_CALL_TAG
{
    void* rwlock;
} mock_pthread_rwlock_destroy_CALL;

typedef union TEST_MOCK_CALL_UNION_TAG
{
    mock_malloc_CALL mock_malloc;
    mock_free_CALL mock_free;
    mock_pthread_rwlock_init_CALL mock_pthread_rwlock_init;
    mock_pthread_rwlock_rdlock_CALL mock_pthread_rwlock_rdlock;
    mock_pthread_rwlock_unlock_CALL mock_pthread_rwlock_unlock;
    mock_pthread_rwlock_wrlock_CALL mock_pthread_rwlock_wrlock;
    mock_pthread_rwlock_destroy_CALL mock_pthread_rwlock_destroy;
} TEST_MOCK_CALL_UNION;

#define TEST_MOCK_CALL_TYPE_VALUES \
    TEST_MOCK_CALL_TYPE_mock_malloc, \
    TEST_MOCK_CALL_TYPE_mock_free, \
    TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_init, \
    TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_rdlock, \
    TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_unlock, \
    TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_wrlock, \
    TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_destroy \

MU_DEFINE_ENUM(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_VALUES)
MU_DEFINE_ENUM_STRINGS(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_VALUES)
TEST_DEFINE_ENUM_TYPE(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_VALUES)

typedef struct TEST_MOCK_CALL_TAG
{
    TEST_MOCK_CALL_TYPE call_type;
    TEST_MOCK_CALL_UNION u;
} TEST_MOCK_CALL;

static size_t mocked_call_count;
static TEST_MOCK_CALL* mocked_calls;

#ifdef __cplusplus
extern "C" {
#endif

    void* mock_malloc(size_t size)
    {
        void* result;

        TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
        if (new_calls != NULL)
        {
            mocked_calls = new_calls;
            mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_mock_malloc;
            mocked_calls[mocked_call_count].u.mock_malloc.size = size;
            mocked_call_count++;
        }

        malloc_call_count++;
        if (malloc_call_count == when_shall_malloc_fail)
        {
            result = NULL;
        }
        else
        {
            result = malloc(size);
        }
        return result;
    }

    void mock_free(void* ptr)
    {
        TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
        if (new_calls != NULL)
        {
            mocked_calls = new_calls;
            mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_mock_free;
            mocked_calls[mocked_call_count].u.mock_free.ptr = ptr;
            mocked_call_count++;
        }

        free(ptr);
    }

#ifdef __cplusplus
}
#endif

static int mock_pthread_rwlock_init_result;
static int mock_pthread_rwlock_rdlock_result;
static int mock_pthread_rwlock_unlock_result;
static int mock_pthread_rwlock_wrlock_result;
static int mock_pthread_rwlock_destroy_result;

int mock_pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_init;
        mocked_calls[mocked_call_count].u.mock_pthread_rwlock_init.rwlock = rwlock;
        mocked_calls[mocked_call_count].u.mock_pthread_rwlock_init.attr = attr;
        mocked_call_count++;
    }
    return mock_pthread_rwlock_init_result;
}

int mock_pthread_rwlock_rdlock(pthread_rwlock_t *rwlock)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_rdlock;
        mocked_calls[mocked_call_count].u.mock_pthread_rwlock_rdlock.rwlock = rwlock;
        mocked_call_count++;
    }

    return 0;
}

int mock_pthread_rwlock_unlock(pthread_rwlock_t *rwlock)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_unlock;
        mocked_calls[mocked_call_count].u.mock_pthread_rwlock_unlock.rwlock = rwlock;
        mocked_call_count++;
    }

    return 0;
}

int mock_pthread_rwlock_wrlock(pthread_rwlock_t *rwlock)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_wrlock;
        mocked_calls[mocked_call_count].u.mock_pthread_rwlock_wrlock.rwlock = rwlock;
        mocked_call_count++;
    }

    return 0;
}

int mock_pthread_rwlock_destroy(pthread_rwlock_t *rwlock)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_destroy;
        mocked_calls[mocked_call_count].u.mock_pthread_rwlock_destroy.rwlock = rwlock;
        mocked_call_count++;
    }

    return 0;
}

static void reset_all_calls(void)
{
    malloc_call_count = 0;
    when_shall_malloc_fail = 0;

    mock_pthread_rwlock_init_result = 0;
    mock_pthread_rwlock_rdlock_result = 0;
    mock_pthread_rwlock_unlock_result = 0;
    mock_pthread_rwlock_wrlock_result = 0;
    mock_pthread_rwlock_destroy_result = 0;

    if (mocked_calls != NULL)
    {
        free(mocked_calls);
        mocked_calls = NULL;
    }

    mocked_call_count = 0;
}

static TEST_MUTEX_HANDLE test_mutex;
static TEST_MUTEX_HANDLE global_mutex;

BEGIN_TEST_SUITE(umock_lock_factory_pthread_unittests)

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
    ASSERT_ARE_EQUAL(int, 0, TEST_MUTEX_ACQUIRE(test_mutex));
    reset_all_calls();
}

TEST_FUNCTION_CLEANUP(test_function_cleanup)
{
    reset_all_calls();
    TEST_MUTEX_RELEASE(test_mutex);
}

/* umock_lock_factory_create_lock */

/* Tests_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_001: [ `umock_lock_factory_create_lock` shall allocate memory for the lock. ]*/
/* Tests_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_002: [ `umock_lock_factory_create_lock` shall initialize a pthread RW lock that is encapsulated by the new `UMOCK_C_LOCK_HANDLE`. ]*/
/* Tests_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_003: [ `umock_lock_factory_create_lock` shall return a lock handle that has the function pointers set to `umock_lock_pthread_acquire_shared`, `umock_lock_pthread_release_shared`, `umock_lock_pthread_acquire_exclusive`, `umock_lock_pthread_release_exclusive` and `umock_lock_pthread_destroy`. ]*/
TEST_FUNCTION(umock_lock_factory_create_lock_succeeds)
{
    // arrange

    // act
    UMOCK_C_LOCK_HANDLE lock = umock_lock_factory_create_lock(NULL);

    // assert
    ASSERT_IS_NOT_NULL(lock);
    ASSERT_ARE_EQUAL(size_t, 2, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_init, mocked_calls[1].call_type);
    ASSERT_IS_NOT_NULL(lock->acquire_exclusive);
    ASSERT_IS_NOT_NULL(lock->release_exclusive);
    ASSERT_IS_NOT_NULL(lock->acquire_shared);
    ASSERT_IS_NOT_NULL(lock->release_shared);
    ASSERT_IS_NOT_NULL(lock->destroy);

    // cleanup
    lock->destroy(lock);
}

/* Tests_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_004: [ If any error occurs, `umock_lock_factory_create_lock` shall fail and return `NULL`. ]*/
TEST_FUNCTION(when_allocating_memory_fails_umock_lock_factory_create_lock_also_fails)
{
    // arrange
    when_shall_malloc_fail = 1;

    // act
    UMOCK_C_LOCK_HANDLE lock = umock_lock_factory_create_lock(NULL);

    // assert
    ASSERT_IS_NULL(lock);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
}

/* Tests_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_004: [ If any error occurs, `umock_lock_factory_create_lock` shall fail and return `NULL`. ]*/
TEST_FUNCTION(when_initializing_the_lock_fails_umock_lock_factory_create_lock_also_fails)
{
    // arrange
    mock_pthread_rwlock_init_result = 1;

    // act
    UMOCK_C_LOCK_HANDLE lock = umock_lock_factory_create_lock(NULL);

    // assert
    ASSERT_IS_NULL(lock);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_init, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[2].call_type);
}

/* umock_lock_pthread_acquire_shared */

/* Tests_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_010: [ If `lock` is `NULL`, `umock_lock_pthread_acquire_shared` shall return. ]*/
TEST_FUNCTION(umock_lock_pthread_acquire_shared_with_NULL_lock_returns)
{
    // arrange
    UMOCK_C_LOCK_HANDLE lock = umock_lock_factory_create_lock(NULL);
    ASSERT_IS_NOT_NULL(lock);
    reset_all_calls();

    // act
    lock->acquire_shared(NULL);

    // assert
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);

    // cleanup
    lock->destroy(lock);
}

/* Tests_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_005: [ `umock_lock_pthread_acquire_shared` shall acquire the read lock by calling `pthread_rwlock_rdlock`. ]*/
TEST_FUNCTION(umock_lock_pthread_acquire_shared_acquires_the_lock_in_shared_mode)
{
    // arrange
    UMOCK_C_LOCK_HANDLE lock = umock_lock_factory_create_lock(NULL);
    ASSERT_IS_NOT_NULL(lock);
    reset_all_calls();

    // act
    lock->acquire_shared(lock);

    // assert
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_rdlock, mocked_calls[0].call_type);

    // cleanup
    lock->destroy(lock);
}

/* umock_lock_pthread_release_shared */

/* Tests_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_011: [ If `lock` is `NULL`, `umock_lock_pthread_release_shared` shall return. ]*/
TEST_FUNCTION(umock_lock_pthread_release_shared_with_NULL_lock_returns)
{
    // arrange
    UMOCK_C_LOCK_HANDLE lock = umock_lock_factory_create_lock(NULL);
    ASSERT_IS_NOT_NULL(lock);
    reset_all_calls();

    // act
    lock->release_shared(NULL);

    // assert
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);

    // cleanup
    lock->destroy(lock);
}

/* Tests_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_006: [ `umock_lock_pthread_release_shared` shall release the lock that was acquired in shared mode by calling `pthread_rwlock_unlock`. ]*/
TEST_FUNCTION(umock_lock_pthread_release_shared_releases_the_lock_in_shared_mode)
{
    // arrange
    UMOCK_C_LOCK_HANDLE lock = umock_lock_factory_create_lock(NULL);
    ASSERT_IS_NOT_NULL(lock);
    reset_all_calls();

    // act
    lock->release_shared(lock);

    // assert
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_unlock, mocked_calls[0].call_type);

    // cleanup
    lock->destroy(lock);
}

/* umock_lock_pthread_acquire_exclusive */

/* Tests_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_012: [ If `lock` is `NULL`, `umock_lock_pthread_acquire_exclusive` shall return. ]*/
TEST_FUNCTION(umock_lock_pthread_acquire_exclusive_with_NULL_lock_returns)
{
    // arrange
    UMOCK_C_LOCK_HANDLE lock = umock_lock_factory_create_lock(NULL);
    ASSERT_IS_NOT_NULL(lock);
    reset_all_calls();

    // act
    lock->acquire_exclusive(NULL);

    // assert
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);

    // cleanup
    lock->destroy(lock);
}

/* Tests_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_007: [ `umock_lock_pthread_acquire_exclusive` shall acquire the lock in exclusive mode by calling `pthread_rwlock_wrlock`. ]*/
TEST_FUNCTION(umock_lock_pthread_acquire_exclusive_acquires_the_lock_in_exclusive_mode)
{
    // arrange
    UMOCK_C_LOCK_HANDLE lock = umock_lock_factory_create_lock(NULL);
    ASSERT_IS_NOT_NULL(lock);
    reset_all_calls();

    // act
    lock->acquire_exclusive(lock);

    // assert
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_wrlock, mocked_calls[0].call_type);

    // cleanup
    lock->destroy(lock);
}

/* umock_lock_pthread_release_exclusive */

/* Tests_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_013: [ If `lock` is `NULL`, `umock_lock_pthread_release_exclusive` shall return. ]*/
TEST_FUNCTION(umock_lock_pthread_release_exclusive_with_NULL_lock_returns)
{
    // arrange
    UMOCK_C_LOCK_HANDLE lock = umock_lock_factory_create_lock(NULL);
    ASSERT_IS_NOT_NULL(lock);
    reset_all_calls();

    // act
    lock->release_exclusive(NULL);

    // assert
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);

    // cleanup
    lock->destroy(lock);
}

/* Tests_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_008: [ `umock_lock_pthread_release_exclusive` shall release the lock that was acquired in exclusive mode by calling `pthread_rwlock_unlock`. ]*/
TEST_FUNCTION(umock_lock_pthread_release_exclusive_releases_the_lock_in_exclusive_mode)
{
    // arrange
    UMOCK_C_LOCK_HANDLE lock = umock_lock_factory_create_lock(NULL);
    ASSERT_IS_NOT_NULL(lock);
    reset_all_calls();

    // act
    lock->release_exclusive(lock);

    // assert
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_unlock, mocked_calls[0].call_type);

    // cleanup
    lock->destroy(lock);
}

/* umock_lock_pthread_destroy */

/* Tests_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_014: [ If `lock` is `NULL`, `umock_lock_pthread_destroy` shall return. ]*/
TEST_FUNCTION(umock_lock_pthread_destroy_with_NULL_lock_returns)
{
    // arrange
    UMOCK_C_LOCK_HANDLE lock = umock_lock_factory_create_lock(NULL);
    ASSERT_IS_NOT_NULL(lock);
    reset_all_calls();

    // act
    lock->destroy(NULL);

    // assert
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);

    // cleanup
    lock->destroy(lock);
}

/* Tests_SRS_UMOCK_LOCK_FACTORY_WINDOWS_01_001: [ `umock_lock_pthread_destroy` shall release the resources for the pthread lock by calling `pthread_rwlock_destroy`. ]*/
/* Tests_SRS_UMOCK_LOCK_FACTORY_PTHREAD_01_009: [ `umock_lock_pthread_destroy` shall free the memory associated with the lock. ]*/
TEST_FUNCTION(umock_lock_pthread_destroy_frees_the_resources)
{
    // arrange
    UMOCK_C_LOCK_HANDLE lock = umock_lock_factory_create_lock(NULL);
    ASSERT_IS_NOT_NULL(lock);
    reset_all_calls();

    // act
    lock->destroy(lock);

    // assert
    ASSERT_ARE_EQUAL(size_t, 2, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_pthread_rwlock_destroy, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[1].call_type);
}

END_TEST_SUITE(umock_lock_factory_pthread_unittests)
