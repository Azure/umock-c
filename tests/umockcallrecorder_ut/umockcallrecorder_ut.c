// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#include <string.h>                     // for strcpy, strlen

// TEST_DEFINE_ENUM_TYPE will use wchar.h, which we technically get from testrunnerswitcher.h
// IWYU pragma: no_include <wchar.h>
#include "testrunnerswitcher.h"

#include "umock_c/umockcallrecorder.h"
#include "umock_c/umockcall.h"
#include "umock_c/umock_lock_if.h"      // for UMOCK_C_LOCK_HANDLE, UMOCK_C_...
#include "umock_c/umock_log.h"

void UMOCK_LOG(const char* format, ...)
{
    (void)format;
}

static UMOCKCALL_HANDLE test_expected_umockcall_1 = (UMOCKCALL_HANDLE)0x4242;
static UMOCKCALL_HANDLE test_expected_umockcall_2 = (UMOCKCALL_HANDLE)0x4243;
static UMOCKCALL_HANDLE test_actual_umockcall_1 = (UMOCKCALL_HANDLE)0x4244;
static UMOCKCALL_HANDLE test_actual_umockcall_2 = (UMOCKCALL_HANDLE)0x4245;

typedef struct umockcall_get_ignore_all_calls_CALL_TAG
{
    UMOCKCALL_HANDLE call;
} umockcall_get_ignore_all_calls_CALL;

static int umockcall_get_ignore_all_calls_call_result;

typedef struct umockcall_are_equal_CALL_TAG
{
    UMOCKCALL_HANDLE left;
    UMOCKCALL_HANDLE right;
} umockcall_are_equal_CALL;

static int umockcall_are_equal_call_result;

typedef struct umockcall_clone_CALL_TAG
{
    UMOCKCALL_HANDLE umockcall;
} umockcall_clone_CALL;

static size_t umockcall_clone_call_count;
static size_t when_shall_umockcall_clone_fail;
static UMOCKCALL_HANDLE umockcall_clone_call_result;

typedef struct umockcall_set_fail_call_CALL_TAG
{
    UMOCKCALL_HANDLE umockcall;
    int fail_call;
} umockcall_set_fail_call_CALL;

static int umockcall_set_fail_call_call_result;

typedef struct umockcall_get_fail_call_CALL_TAG
{
    UMOCKCALL_HANDLE umockcall;
} umockcall_get_fail_call_CALL;

static int umockcall_get_fail_call_call_result;

typedef struct umockcall_destroy_CALL_TAG
{
    UMOCKCALL_HANDLE umockcall;
} umockcall_destroy_CALL;

static int umockcall_destroy_call_result;

typedef struct umockcall_stringify_CALL_TAG
{
    UMOCKCALL_HANDLE umockcall;
} umockcall_stringify_CALL;

static char* umockcall_stringify_call_result;

typedef struct umockcall_get_call_can_fail_CALL_TAG
{
    UMOCKCALL_HANDLE umockcall;
} umockcall_get_call_can_fail_CALL;

static int umockcall_get_call_can_fail_result;

typedef struct test_lock_acquire_shared_CALL_TAG
{
    UMOCK_C_LOCK_HANDLE lock;
} test_lock_acquire_shared_CALL;

typedef struct test_lock_release_shared_CALL_TAG
{
    UMOCK_C_LOCK_HANDLE lock;
} test_lock_release_shared_CALL;

typedef struct test_lock_acquire_exclusive_CALL_TAG
{
    UMOCK_C_LOCK_HANDLE lock;
} test_lock_acquire_exclusive_CALL;

typedef struct test_lock_release_exclusive_CALL_TAG
{
    UMOCK_C_LOCK_HANDLE lock;
} test_lock_release_exclusive_CALL;

typedef struct test_lock_destroy_CALL_TAG
{
    UMOCK_C_LOCK_HANDLE lock;
} test_lock_destroy_CALL;

static size_t malloc_call_count;
static size_t realloc_call_count;

static size_t when_shall_malloc_fail;
static size_t when_shall_realloc_fail;

typedef struct mock_malloc_CALL_TAG
{
    size_t size;
    } mock_malloc_CALL;

typedef struct mock_realloc_CALL_TAG
{
    void* ptr;
    size_t size;
} mock_realloc_CALL;

typedef struct mock_free_CALL_TAG
{
    void* ptr;
} mock_free_CALL;

typedef struct test_lock_factory_create_lock_CALL_TAG
{
    void* params;
} test_lock_factory_create_lock_CALL;

static UMOCK_C_LOCK_HANDLE test_lock_factory_create_lock_result;

typedef union TEST_MOCK_CALL_UNION_TAG
{
    umockcall_get_ignore_all_calls_CALL umockcall_get_ignore_all_calls;
    umockcall_are_equal_CALL umockcall_are_equal;
    umockcall_clone_CALL umockcall_clone;
    umockcall_set_fail_call_CALL umockcall_set_fail_call;
    umockcall_get_fail_call_CALL umockcall_get_fail_call;
    umockcall_destroy_CALL umockcall_destroy;
    umockcall_stringify_CALL umockcall_stringify;
    umockcall_get_call_can_fail_CALL umockcall_get_call_can_fail;
    mock_malloc_CALL mock_malloc;
    mock_realloc_CALL mock_realloc;
    mock_free_CALL mock_free;
    test_lock_factory_create_lock_CALL test_lock_factory_create_lock;
    test_lock_acquire_shared_CALL test_lock_acquire_shared;
    test_lock_release_shared_CALL test_lock_release_shared;
    test_lock_acquire_exclusive_CALL test_lock_acquire_exclusive;
    test_lock_release_exclusive_CALL test_lock_release_exclusive;
    test_lock_destroy_CALL test_lock_destroy;
} TEST_MOCK_CALL_UNION;

#define TEST_MOCK_CALL_TYPE_VALUES \
    TEST_MOCK_CALL_TYPE_umockcall_get_ignore_all_calls, \
    TEST_MOCK_CALL_TYPE_umockcall_are_equal, \
    TEST_MOCK_CALL_TYPE_umockcall_clone, \
    TEST_MOCK_CALL_TYPE_umockcall_set_fail_call, \
    TEST_MOCK_CALL_TYPE_umockcall_get_fail_call, \
    TEST_MOCK_CALL_TYPE_umockcall_destroy, \
    TEST_MOCK_CALL_TYPE_umockcall_stringify, \
    TEST_MOCK_CALL_TYPE_umockcall_get_call_can_fail, \
    TEST_MOCK_CALL_TYPE_mock_malloc, \
    TEST_MOCK_CALL_TYPE_mock_realloc, \
    TEST_MOCK_CALL_TYPE_mock_free, \
    TEST_MOCK_CALL_TYPE_test_lock_factory_create_lock, \
    TEST_MOCK_CALL_TYPE_test_lock_acquire_shared, \
    TEST_MOCK_CALL_TYPE_test_lock_release_shared, \
    TEST_MOCK_CALL_TYPE_test_lock_acquire_exclusive, \
    TEST_MOCK_CALL_TYPE_test_lock_release_exclusive, \
    TEST_MOCK_CALL_TYPE_test_lock_destroy \

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

int umockcall_get_ignore_all_calls(UMOCKCALL_HANDLE call)
{
    TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcall_get_ignore_all_calls;
        mocked_calls[mocked_call_count].u.umockcall_get_ignore_all_calls.call = call;
        mocked_call_count++;
    }

    return umockcall_get_ignore_all_calls_call_result;
}

int umockcall_are_equal(UMOCKCALL_HANDLE left, UMOCKCALL_HANDLE right)
{
    TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcall_are_equal;
        mocked_calls[mocked_call_count].u.umockcall_are_equal.left = left;
        mocked_calls[mocked_call_count].u.umockcall_are_equal.right = right;
        mocked_call_count++;
    }

    return umockcall_are_equal_call_result;
}

void umockcall_destroy(UMOCKCALL_HANDLE umockcall)
{
    TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcall_destroy;
        mocked_calls[mocked_call_count].u.umockcall_destroy.umockcall = umockcall;
        mocked_call_count++;
    }
}

UMOCKCALL_HANDLE umockcall_clone(UMOCKCALL_HANDLE umockcall)
{
    UMOCKCALL_HANDLE result;
    TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcall_clone;
        mocked_calls[mocked_call_count].u.umockcall_clone.umockcall = umockcall;
        umockcall_clone_call_count++;
        mocked_call_count++;
    }

    if ((when_shall_umockcall_clone_fail > 0) && (when_shall_umockcall_clone_fail == umockcall_clone_call_count))
    {
        result = NULL;
    }
    else
    {
        result = umockcall_clone_call_result;
    }

    return result;
}

int umockcall_set_fail_call(UMOCKCALL_HANDLE umockcall, int fail_call)
{
    TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcall_set_fail_call;
        mocked_calls[mocked_call_count].u.umockcall_set_fail_call.umockcall = umockcall;
        mocked_calls[mocked_call_count].u.umockcall_set_fail_call.fail_call = fail_call;
        mocked_call_count++;
    }

    return umockcall_set_fail_call_call_result;
}

int umockcall_get_fail_call(UMOCKCALL_HANDLE umockcall)
{
    TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcall_get_fail_call;
        mocked_calls[mocked_call_count].u.umockcall_get_fail_call.umockcall = umockcall;
        mocked_call_count++;
    }

    return umockcall_get_fail_call_call_result;
}

char* umockcall_stringify(UMOCKCALL_HANDLE umockcall)
{
    char* result;

    TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcall_stringify;
        mocked_calls[mocked_call_count].u.umockcall_stringify.umockcall = umockcall;
        mocked_call_count++;
    }

    if (umockcall_stringify_call_result == NULL)
    {
        result = NULL;
    }
    else
    {
        result = malloc(strlen(umockcall_stringify_call_result) + 1);
        if (result != NULL)
        {
            (void)strcpy(result, umockcall_stringify_call_result);
        }
    }

    return result;
}

int umockcall_get_call_can_fail(UMOCKCALL_HANDLE umockcall)
{
    TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcall_get_call_can_fail;
        mocked_calls[mocked_call_count].u.umockcall_get_call_can_fail.umockcall = umockcall;
        mocked_call_count++;
    }

    return umockcall_get_call_can_fail_result;
}


    void* mock_malloc(size_t size)
    {
        void* result;

        TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
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

    void* mock_realloc(void* ptr, size_t size)
    {
        void* result;

        TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
        if (new_calls != NULL)
        {
            mocked_calls = new_calls;
            mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_mock_realloc;
            mocked_calls[mocked_call_count].u.mock_realloc.ptr = ptr;
            mocked_calls[mocked_call_count].u.mock_realloc.size = size;
            mocked_call_count++;
        }

        realloc_call_count++;
        if (realloc_call_count == when_shall_realloc_fail)
        {
            result = NULL;
        }
        else
        {
            result = realloc(ptr, size);
        }
        return result;
    }

    void mock_free(void* ptr)
    {
        TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
        if (new_calls != NULL)
        {
            mocked_calls = new_calls;
            mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_mock_free;
            mocked_calls[mocked_call_count].u.mock_free.ptr = ptr;
            mocked_call_count++;
        }

        free(ptr);
    }


void test_lock_acquire_shared(UMOCK_C_LOCK_HANDLE lock)
{
    TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_test_lock_acquire_shared;
        mocked_calls[mocked_call_count].u.test_lock_acquire_shared.lock = lock;
        mocked_call_count++;
    }
}

void test_lock_release_shared(UMOCK_C_LOCK_HANDLE lock)
{
    TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_test_lock_release_shared;
        mocked_calls[mocked_call_count].u.test_lock_release_shared.lock = lock;
        mocked_call_count++;
    }
}

void test_lock_acquire_exclusive(UMOCK_C_LOCK_HANDLE lock)
{
    TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_test_lock_acquire_exclusive;
        mocked_calls[mocked_call_count].u.test_lock_acquire_exclusive.lock = lock;
        mocked_call_count++;
    }
}

void test_lock_release_exclusive(UMOCK_C_LOCK_HANDLE lock)
{
    TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_test_lock_release_exclusive;
        mocked_calls[mocked_call_count].u.test_lock_release_exclusive.lock = lock;
        mocked_call_count++;
    }
}

void test_lock_destroy(UMOCK_C_LOCK_HANDLE lock)
{
    TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_test_lock_destroy;
        mocked_calls[mocked_call_count].u.test_lock_destroy.lock = lock;
        mocked_call_count++;
    }
}

UMOCK_C_LOCK_HANDLE test_lock_factory_create_lock(void* params)
{
    TEST_MOCK_CALL* new_calls = realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_test_lock_factory_create_lock;
        mocked_calls[mocked_call_count].u.test_lock_factory_create_lock.params = params;
        mocked_call_count++;
    }

    return test_lock_factory_create_lock_result;
}

static const UMOCK_C_LOCK_IF test_lock =
{
    test_lock_acquire_shared,
    test_lock_release_shared,
    test_lock_acquire_exclusive,
    test_lock_release_exclusive,
    test_lock_destroy
};

static UMOCK_C_LOCK_HANDLE test_lock_handle = &test_lock;

static void reset_all_calls(void)
{
    malloc_call_count = 0;
    when_shall_malloc_fail = 0;
    realloc_call_count = 0;
    when_shall_realloc_fail = 0;

    umockcall_clone_call_count = 0;
    when_shall_umockcall_clone_fail = 0;

    umockcall_set_fail_call_call_result = 0;
    umockcall_get_call_can_fail_result = 0;

    umockcall_are_equal_call_result = 1;
    umockcall_get_ignore_all_calls_call_result = 0;

    test_lock_factory_create_lock_result = test_lock_handle;

    if (mocked_calls != NULL)
    {
        free(mocked_calls);
        mocked_calls = NULL;
    }

    mocked_call_count = 0;
}

static TEST_MUTEX_HANDLE test_mutex;
static TEST_MUTEX_HANDLE global_mutex;

BEGIN_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)

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

/* umockcallrecorder_create */

/* Tests_SRS_UMOCKCALLRECORDER_01_001: [ umockcallrecorder_create shall create a new instance of a call recorder and return a non-NULL handle to it on success. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_095: [ lock_factory_create_lock may be NULL. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_096: [ lock_factory_create_lock shall be saved for later use. ]*/
TEST_FUNCTION(umockcallrecorder_create_succeeds)
{
    // arrange

    // act
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);

    // assert
    ASSERT_IS_NOT_NULL(call_recorder);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_002: [ If any error occurs, umockcallrecorder_create shall return NULL. ]*/
TEST_FUNCTION(when_allocating_memory_fails_then_umockcallrecorder_create_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE call_recorder;
    when_shall_malloc_fail = 1;

    // act
    call_recorder = umockcallrecorder_create(NULL, NULL);

    // assert
    ASSERT_IS_NULL(call_recorder);
}

/* Codes_SRS_UMOCKCALLRECORDER_01_097: [ If lock_factory_create_lock is not NULL, umockcallrecorder_create shall call lock_factory_create_lock to create the lock used when working with the stored calls. ]*/
TEST_FUNCTION(umockcallrecorder_create_with_non_NULL_lock_factory_succeeds)
{
    // arrange
    test_lock_factory_create_lock_result = test_lock_handle;

    // act
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(test_lock_factory_create_lock, (void*)0x4242);

    // assert
    ASSERT_IS_NOT_NULL(call_recorder);
    ASSERT_ARE_EQUAL(size_t, 2, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_factory_create_lock, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4242, mocked_calls[1].u.test_lock_factory_create_lock.params);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_002: [ If any error occurs, umockcallrecorder_create shall return NULL. ]*/
TEST_FUNCTION(if_creating_the_lock_fails_umockcallrecorder_create_also_fails)
{
    // arrange
    test_lock_factory_create_lock_result = NULL;

    // act
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(test_lock_factory_create_lock, (void*)0x4242);

    // assert
    ASSERT_IS_NULL(call_recorder);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_factory_create_lock, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4242, mocked_calls[1].u.test_lock_factory_create_lock.params);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[2].call_type);
}

/* umockcallrecorder_destroy */

/* Tests_SRS_UMOCKCALLRECORDER_01_003: [ umockcallrecorder_destroy shall free the resources associated with a the call recorder identified by the umock_call_recorder argument. ]*/
TEST_FUNCTION(umockcallrecorder_destroy_frees_the_call_recorder_resources)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    reset_all_calls();

    // act
    umockcallrecorder_destroy(call_recorder);

    // assert
    ASSERT_IS_NOT_NULL(call_recorder);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[0].call_type);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_004: [ If umock_call_recorder is NULL, umockcallrecorder_destroy shall do nothing. ]*/
TEST_FUNCTION(umockcallrecorder_destroy_with_NULL_does_nothing)
{
    // arrange

    // act
    umockcallrecorder_destroy(NULL);

    // assert
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_003: [ umockcallrecorder_destroy shall free the resources associated with a the call recorder identified by the umock_call_recorder argument. ]*/
TEST_FUNCTION(umockcallrecorder_destroy_with_one_expected_call_frees_the_call_recorder_resources)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    umockcall_are_equal_call_result = 0;

    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);

    reset_all_calls();

    // act
    umockcallrecorder_destroy(call_recorder);

    // assert
    ASSERT_IS_NOT_NULL(call_recorder);
    /* 8 calls total */
    ASSERT_ARE_EQUAL(size_t, 6, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_destroy, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_expected_umockcall_1, mocked_calls[0].u.umockcall_destroy.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_destroy, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_expected_umockcall_2, mocked_calls[1].u.umockcall_destroy.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_destroy, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_actual_umockcall_1, mocked_calls[3].u.umockcall_destroy.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[4].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[5].call_type);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_098: [ If a lock was created in umockcallrecorder_create, the lock shall be destroyed. ]*/
TEST_FUNCTION(umockcallrecorder_destroy_destroys_the_lock_created_in_create)
{
    // arrange
    test_lock_factory_create_lock_result = test_lock_handle;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(test_lock_factory_create_lock, NULL);
    reset_all_calls();

    // act
    umockcallrecorder_destroy(call_recorder);

    // assert
    ASSERT_IS_NOT_NULL(call_recorder);
    ASSERT_ARE_EQUAL(size_t, 2, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_destroy, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_lock_handle, mocked_calls[0].u.test_lock_destroy.lock);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[1].call_type);
}

/* umockcallrecorder_reset_all_calls */

/* Tests_SRS_UMOCKCALLRECORDER_01_005: [ umockcallrecorder_reset_all_calls shall free all the expected and actual calls for the call recorder identified by umock_call_recorder. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_006: [ On success umockcallrecorder_reset_all_calls shall return 0. ]*/
TEST_FUNCTION(umockcallrecorder_reset_all_calls_frees_all_existing_expected_and_actual_calls)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    umockcall_are_equal_call_result = 0;

    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    reset_all_calls();

    // act
    result = umockcallrecorder_reset_all_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 5, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_destroy, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_expected_umockcall_1, mocked_calls[0].u.umockcall_destroy.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_destroy, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_expected_umockcall_2, mocked_calls[1].u.umockcall_destroy.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_destroy, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_actual_umockcall_1, mocked_calls[3].u.umockcall_destroy.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[4].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_007: [ If umock_call_recorder is NULL, umockcallrecorder_reset_all_calls shall fail and return a non-zero value. ]*/
TEST_FUNCTION(umockcallrecorder_reset_all_calls_with_NULL_call_recorder_fails)
{
    // arrange

    // act
    int result = umockcallrecorder_reset_all_calls(NULL);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_065: [ If a lock was created for the call recorder, umockcallrecorder_reset_all_calls shall acquire the lock in exclusive mode. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_066: [ If a lock was created for the call recorder, umockcallrecorder_reset_all_calls shall release the exclusive lock. ]*/
TEST_FUNCTION(umockcallrecorder_reset_all_calls_with_lock_functions_locks_and_unlocks)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(test_lock_factory_create_lock, NULL);
    UMOCKCALL_HANDLE matched_call;
    umockcall_are_equal_call_result = 0;

    ASSERT_ARE_EQUAL(int, 0, umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1));
    ASSERT_ARE_EQUAL(int, 0, umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call));
    reset_all_calls();

    // act
    result = umockcallrecorder_reset_all_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 6, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_acquire_exclusive, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_destroy, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_expected_umockcall_1, mocked_calls[1].u.umockcall_destroy.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_destroy, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_actual_umockcall_1, mocked_calls[3].u.umockcall_destroy.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[4].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_release_exclusive, mocked_calls[5].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* umockcallrecorder_add_expected_call */

/* Tests_SRS_UMOCKCALLRECORDER_01_008: [ umockcallrecorder_add_expected_call shall add the mock_call call to the expected call list maintained by the call recorder identified by umock_call_recorder. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_009: [ On success umockcallrecorder_add_expected_call shall return 0. ]*/
TEST_FUNCTION(umockcallrecorder_add_expected_call_adds_an_expected_call)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);

    // act
    int result = umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_012: [ If any of the arguments is NULL, umockcallrecorder_add_expected_call shall fail and return a non-zero value. ]*/
TEST_FUNCTION(umockcallrecorder_add_expected_call_with_NULL_call_recorder_fails)
{
    // arrange

    // act
    int result = umockcallrecorder_add_expected_call(NULL, test_expected_umockcall_1);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_012: [ If any of the arguments is NULL, umockcallrecorder_add_expected_call shall fail and return a non-zero value. ]*/
TEST_FUNCTION(umockcallrecorder_add_expected_call_with_NULL_mock_call_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);

    // act
    int result = umockcallrecorder_add_expected_call(call_recorder, NULL);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_013: [ If any error occurs, umockcallrecorder_add_expected_call shall fail and return a non-zero value. ]*/
TEST_FUNCTION(when_allocating_memory_fails_umockcallrecorder_add_expected_call_fails)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    reset_all_calls();
    when_shall_realloc_fail = 1;

    // act
    result = umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_068: [ If a lock was created for the call recorder, umockcallrecorder_add_expected_call shall acquire the lock in exclusive mode. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_069: [ If a lock was created for the call recorder, umockcallrecorder_add_expected_call shall release the exclusive lock. ]*/
TEST_FUNCTION(umockcallrecorder_add_expected_call_with_locks_setup_locks_and_unlocks)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(test_lock_factory_create_lock, NULL);
    reset_all_calls();

    // act
    int result = umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_acquire_exclusive, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_realloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_release_exclusive, mocked_calls[2].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* umockcallrecorder_add_actual_call */

/* Tests_SRS_UMOCKCALLRECORDER_01_014: [ umockcallrecorder_add_actual_call shall check whether the call mock_call matches any of the expected calls maintained by umock_call_recorder. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_015: [ If the call does not match any of the expected calls, then umockcallrecorder_add_actual_call shall add the mock_call call to the actual call list maintained by umock_call_recorder. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_018: [ When no error is encountered, umockcallrecorder_add_actual_call shall return 0. ]*/
TEST_FUNCTION(umockcallrecorder_add_actual_call_without_any_expected_calls_succeeds)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;

    // act
    int result = umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_IS_NULL(matched_call);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_014: [ umockcallrecorder_add_actual_call shall check whether the call mock_call matches any of the expected calls maintained by umock_call_recorder. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_015: [ If the call does not match any of the expected calls, then umockcallrecorder_add_actual_call shall add the mock_call call to the actual call list maintained by umock_call_recorder. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_018: [ When no error is encountered, umockcallrecorder_add_actual_call shall return 0. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_017: [ Comparing the calls shall be done by calling umockcall_are_equal. ]*/
TEST_FUNCTION(umockcallrecorder_add_actual_call_with_a_call_that_does_not_match_succeeds)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    umockcall_are_equal_call_result = 0;
    reset_all_calls();

    // act
    result = umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_get_ignore_all_calls, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_are_equal, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_expected_umockcall_1, mocked_calls[1].u.umockcall_are_equal.left);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_actual_umockcall_1, mocked_calls[1].u.umockcall_are_equal.right);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_destroy, mocked_calls[2].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_019: [ If any of the arguments is NULL, umockcallrecorder_add_actual_call shall fail and return a non-zero value. ]*/
TEST_FUNCTION(umockcallrecorder_add_actual_call_with_NULL_call_recorder_fails)
{
    // arrange
    UMOCKCALL_HANDLE matched_call;

    // act
    int result = umockcallrecorder_add_actual_call(NULL, test_actual_umockcall_1, &matched_call);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_019: [ If any of the arguments is NULL, umockcallrecorder_add_actual_call shall fail and return a non-zero value. ]*/
TEST_FUNCTION(umockcallrecorder_add_actual_call_with_NULL_actual_call_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;

    // act
    int result = umockcallrecorder_add_actual_call(call_recorder, NULL, &matched_call);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_019: [ If any of the arguments is NULL, umockcallrecorder_add_actual_call shall fail and return a non-zero value. ]*/
TEST_FUNCTION(umockcallrecorder_add_actual_call_with_NULL_matched_call_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);

    // act
    int result = umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, NULL);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_020: [ If allocating memory for the actual calls fails, umockcallrecorder_add_actual_call shall fail and return a non-zero value. ]*/
TEST_FUNCTION(when_allocating_memory_for_the_actual_calls_fails_umockcallrecorder_add_actual_call_fails)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    reset_all_calls();
    when_shall_realloc_fail = 1;

    // act
    result = umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_021: [ If umockcall_are_equal fails, umockcallrecorder_add_actual_call shall fail and return a non-zero value. ]*/
TEST_FUNCTION(when_umockcall_are_equal_fails_then_umockcallrecorder_add_actual_call_fails)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();
    umockcall_are_equal_call_result = -1;

    // act
    result = umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 2, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_get_ignore_all_calls, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_are_equal, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_expected_umockcall_1, mocked_calls[1].u.umockcall_are_equal.left);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_actual_umockcall_1, mocked_calls[1].u.umockcall_are_equal.right);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_016: [ If the call matches one of the expected calls, a handle to the matched call shall be filled into the matched_call argument. ]*/
TEST_FUNCTION(when_the_actual_call_matches_the_expected_call_then_the_matched_call_is_returned)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();
    umockcall_are_equal_call_result = 1;

    // act
    result = umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, matched_call);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_get_ignore_all_calls, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_are_equal, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_expected_umockcall_1, mocked_calls[1].u.umockcall_are_equal.left);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_actual_umockcall_1, mocked_calls[1].u.umockcall_are_equal.right);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_destroy, mocked_calls[2].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_016: [ If the call matches one of the expected calls, a handle to the matched call shall be filled into the matched_call argument. ]*/
TEST_FUNCTION(when_the_actual_call_matches_the_1st_of_2_expected_call_then_the_matched_call_is_returned)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);
    reset_all_calls();
    umockcall_are_equal_call_result = 1;

    // act
    result = umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, matched_call);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_get_ignore_all_calls, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_are_equal, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_expected_umockcall_1, mocked_calls[1].u.umockcall_are_equal.left);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_actual_umockcall_1, mocked_calls[1].u.umockcall_are_equal.right);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_destroy, mocked_calls[2].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_016: [ If the call matches one of the expected calls, a handle to the matched call shall be filled into the matched_call argument. ]*/
TEST_FUNCTION(when_the_actual_call_matches_the_2nd_of_2_expected_call_then_the_matched_call_is_returned)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);
    umockcall_are_equal_call_result = 1;
    umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    reset_all_calls();
    umockcall_are_equal_call_result = 1;

    // act
    result = umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_2, &matched_call);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_2, matched_call);
    ASSERT_ARE_EQUAL(size_t, 4, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_get_ignore_all_calls, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_get_ignore_all_calls, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_are_equal, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_expected_umockcall_2, mocked_calls[2].u.umockcall_are_equal.left);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_actual_umockcall_2, mocked_calls[2].u.umockcall_are_equal.right);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_destroy, mocked_calls[3].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_014: [ umockcallrecorder_add_actual_call shall check whether the call mock_call matches any of the expected calls maintained by umock_call_recorder. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_018: [ When no error is encountered, umockcallrecorder_add_actual_call shall return 0. ]*/
TEST_FUNCTION(two_actual_calls_can_be_added)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);

    // act
    result = umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_2, &matched_call);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_014: [ umockcallrecorder_add_actual_call shall check whether the call mock_call matches any of the expected calls maintained by umock_call_recorder. ]*/
TEST_FUNCTION(only_the_first_expected_call_is_checked_for_match)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    umockcall_are_equal_call_result = 0;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);
    reset_all_calls();
    umockcall_are_equal_call_result = 0;

    // act
    result = umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_IS_NULL(matched_call);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_get_ignore_all_calls, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_are_equal, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_expected_umockcall_1, mocked_calls[1].u.umockcall_are_equal.left);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_actual_umockcall_1, mocked_calls[1].u.umockcall_are_equal.right);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_realloc, mocked_calls[2].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_014: [ umockcallrecorder_add_actual_call shall check whether the call mock_call matches any of the expected calls maintained by umock_call_recorder. ]*/
TEST_FUNCTION(if_matching_fails_subsequent_actual_calls_are_not_matched)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    umockcall_stringify_call_result = "[a()]";
    umockcall_are_equal_call_result = 0;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    reset_all_calls();
    umockcall_are_equal_call_result = 1;
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_2, &matched_call);
    reset_all_calls();
    umockcall_are_equal_call_result = 1;

    // act
    result = umockcallrecorder_get_actual_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "[a()][a()]", result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_057: [ If any expected call has ignore_all_calls set and the actual call is equal to it when comparing the 2 calls, then the call shall be considered matched and not added to the actual calls list. ]*/
TEST_FUNCTION(if_expected_call_has_ignore_all_calls_the_actual_call_is_not_recorded)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    umockcall_stringify_call_result = "[a()]";
    umockcall_are_equal_call_result = 1;
    umockcall_get_ignore_all_calls_call_result = 1;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    reset_all_calls();

    // act
    result = umockcallrecorder_get_actual_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "", result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_057: [ If any expected call has ignore_all_calls set and the actual call is equal to it when comparing the 2 calls, then the call shall be considered matched and not added to the actual calls list. ]*/
TEST_FUNCTION(if_expected_call_has_ignore_all_calls_2_actual_calls_are_not_recorded)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    umockcall_stringify_call_result = "[a()]";
    umockcall_are_equal_call_result = 1;
    umockcall_get_ignore_all_calls_call_result = 1;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    reset_all_calls();

    // act
    result = umockcallrecorder_get_actual_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "", result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_058: [ If getting ignore_all_calls by calling umockcall_get_ignore_all_calls fails, umockcallrecorder_add_actual_call shall fail and return a non-zero value. ]*/
TEST_FUNCTION(if_expected_call_has_ignore_all_calls_and_umockcall_get_ignore_all_calls_fails_then_umockcallrecorder_get_actual_calls_fails)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    int add_call_result;
    umockcall_stringify_call_result = "[a()]";
    umockcall_are_equal_call_result = 1;
    umockcall_get_ignore_all_calls_call_result = -1;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    add_call_result = umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    reset_all_calls();

    // act
    result = umockcallrecorder_get_actual_calls(call_recorder);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, add_call_result);
    ASSERT_ARE_EQUAL(char_ptr, "", result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_071: [ If a lock was created for the call recorder, umockcallrecorder_add_actual_call shall acquire the lock in exclusive mode. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_070: [ If a lock was created for the call recorder, umockcallrecorder_add_actual_call shall release the exclusive lock. ]*/
TEST_FUNCTION(umockcallrecorder_add_actual_call_with_lock_functions_set_locks_and_unlocks)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(test_lock_factory_create_lock, NULL);
    UMOCKCALL_HANDLE matched_call;
    ASSERT_ARE_EQUAL(int, 0, umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1));
    reset_all_calls();
    umockcall_are_equal_call_result = 0;

    // act
    result = umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 5, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_acquire_exclusive, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_get_ignore_all_calls, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_are_equal, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_expected_umockcall_1, mocked_calls[2].u.umockcall_are_equal.left);
    ASSERT_ARE_EQUAL(void_ptr, (void*)test_actual_umockcall_1, mocked_calls[2].u.umockcall_are_equal.right);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_realloc, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_release_exclusive, mocked_calls[4].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* umockcallrecorder_get_actual_calls */

/* Tests_SRS_UMOCKCALLRECORDER_01_022: [ umockcallrecorder_get_actual_calls shall return a pointer to the string representation of all the actual calls. ]*/
TEST_FUNCTION(umockcallrecorder_get_actual_calls_with_no_calls_returns_an_empty_string)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);

    // act
    const char* result = umockcallrecorder_get_actual_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "", result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_022: [ umockcallrecorder_get_actual_calls shall return a pointer to the string representation of all the actual calls. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_023: [ The string for each call shall be obtained by calling umockcall_stringify. ]*/
TEST_FUNCTION(umockcallrecorder_get_actual_calls_with_1_call_returns_one_stringified_call)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    reset_all_calls();
    umockcall_stringify_call_result = "[a()]";

    // act
    result = umockcallrecorder_get_actual_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "[a()]", result);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_stringify, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_realloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[2].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_022: [ umockcallrecorder_get_actual_calls shall return a pointer to the string representation of all the actual calls. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_023: [ The string for each call shall be obtained by calling umockcall_stringify. ]*/
TEST_FUNCTION(umockcallrecorder_get_actual_calls_with_2_calls_returns_the_stringified_calls)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    reset_all_calls();
    umockcall_stringify_call_result = "[a()]";

    // act
    result = umockcallrecorder_get_actual_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "[a()][a()]", result);
    ASSERT_ARE_EQUAL(size_t, 6, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_stringify, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_realloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_stringify, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_realloc, mocked_calls[4].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[5].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_025: [ If umockcall_stringify fails, umockcallrecorder_get_actual_calls shall fail and return NULL. ]*/
TEST_FUNCTION(when_stringifying_one_call_fails_then_umockcallrecorder_get_actual_calls_fails)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    umockcall_stringify_call_result = NULL;
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);

    // act
    result = umockcallrecorder_get_actual_calls(call_recorder);

    // assert
    ASSERT_IS_NULL(result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_024: [ If the umock_call_recorder is NULL, umockcallrecorder_get_actual_calls shall fail and return NULL. ]*/
TEST_FUNCTION(umockcallrecorder_get_actual_calls_with_NULL_call_recorder_fails)
{
    // arrange

    // act
    const char* result = umockcallrecorder_get_actual_calls(NULL);

    // assert
    ASSERT_IS_NULL(result);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_026: [ If allocating memory for the resulting string fails, umockcallrecorder_get_actual_calls shall fail and return NULL. ]*/
TEST_FUNCTION(when_allocating_memory_for_the_resulting_string_for_no_calls_fails_then_umockcallrecorder_get_actual_calls_fails)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    reset_all_calls();

    when_shall_realloc_fail = 1;

    // act
    result = umockcallrecorder_get_actual_calls(call_recorder);

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_realloc, mocked_calls[0].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_026: [ If allocating memory for the resulting string fails, umockcallrecorder_get_actual_calls shall fail and return NULL. ]*/
TEST_FUNCTION(when_allocating_memory_for_the_resulting_string_fails_then_umockcallrecorder_get_actual_calls_fails)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    reset_all_calls();

    umockcall_stringify_call_result = "[a()]";
    when_shall_realloc_fail = 1;

    // act
    result = umockcallrecorder_get_actual_calls(call_recorder);

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_stringify, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_realloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[2].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_022: [ umockcallrecorder_get_actual_calls shall return a pointer to the string representation of all the actual calls. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_023: [ The string for each call shall be obtained by calling umockcall_stringify. ]*/
TEST_FUNCTION(umockcallrecorder_get_actual_calls_when_the_actual_call_does_not_match_the_expected_should_return_the_actual_call)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    umockcall_are_equal_call_result = 0;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    reset_all_calls();
    umockcall_stringify_call_result = "[a()]";

    // act
    result = umockcallrecorder_get_actual_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "[a()]", result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_073: [ If a lock was created for the call recorder, umockcallrecorder_get_actual_calls shall acquire the lock in exclusive mode. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_074: [ If a lock was created for the call recorder, umockcallrecorder_get_actual_calls shall release the exclusive lock. ]*/
TEST_FUNCTION(umockcallrecorder_get_actual_calls_with_lock_functions_setup_locks_and_unlocks)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(test_lock_factory_create_lock, NULL);
    UMOCKCALL_HANDLE matched_call;
    ASSERT_ARE_EQUAL(int, 0, umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call));
    reset_all_calls();
    umockcall_stringify_call_result = "[a()]";

    // act
    result = umockcallrecorder_get_actual_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "[a()]", result);
    ASSERT_ARE_EQUAL(size_t, 5, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_acquire_exclusive, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_stringify, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_realloc, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_release_exclusive, mocked_calls[4].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* umockcallrecorder_get_expected_calls */

/* Tests_SRS_UMOCKCALLRECORDER_01_027: [ umockcallrecorder_get_expected_calls shall return a pointer to the string representation of all the expected calls. ]*/
TEST_FUNCTION(umockcallrecorder_get_expected_calls_with_no_calls_returns_an_empty_string)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);

    // act
    const char* result = umockcallrecorder_get_expected_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "", result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_027: [ umockcallrecorder_get_expected_calls shall return a pointer to the string representation of all the expected calls. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_028: [ The string for each call shall be obtained by calling umockcall_stringify. ]*/
TEST_FUNCTION(umockcallrecorder_get_expected_calls_with_1_call_returns_one_stringified_call)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();
    umockcall_stringify_call_result = "[a()]";

    // act
    result = umockcallrecorder_get_expected_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "[a()]", result);
    ASSERT_ARE_EQUAL(size_t, 1, realloc_call_count);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_027: [ umockcallrecorder_get_expected_calls shall return a pointer to the string representation of all the expected calls. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_028: [ The string for each call shall be obtained by calling umockcall_stringify. ]*/
TEST_FUNCTION(umockcallrecorder_get_expected_calls_with_2_calls_returns_the_stringified_calls)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();
    umockcall_stringify_call_result = "[a()]";

    // act
    result = umockcallrecorder_get_expected_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "[a()][a()]", result);
    ASSERT_ARE_EQUAL(size_t, 2, realloc_call_count);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_030: [ If umockcall_stringify fails, umockcallrecorder_get_expected_calls shall fail and return NULL. ]*/
TEST_FUNCTION(when_stringifying_one_call_fails_then_umockcallrecorder_get_expected_calls_fails)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    umockcall_stringify_call_result = NULL;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);

    // act
    result = umockcallrecorder_get_expected_calls(call_recorder);

    // assert
    ASSERT_IS_NULL(result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_029: [ If the umock_call_recorder is NULL, umockcallrecorder_get_expected_calls shall fail and return NULL. ]*/
TEST_FUNCTION(umockcallrecorder_get_expected_calls_with_NULL_call_recorder_fails)
{
    // arrange

    // act
    const char* result = umockcallrecorder_get_expected_calls(NULL);

    // assert
    ASSERT_IS_NULL(result);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_031: [ If allocating memory for the resulting string fails, umockcallrecorder_get_expected_calls shall fail and return NULL. ]*/
TEST_FUNCTION(when_allocating_memory_for_the_resulting_string__for_no_calls_fails_then_umockcallrecorder_get_expected_calls_fails)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    reset_all_calls();

    when_shall_realloc_fail = 1;

    // act
    result = umockcallrecorder_get_expected_calls(call_recorder);

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 1, realloc_call_count);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_031: [ If allocating memory for the resulting string fails, umockcallrecorder_get_expected_calls shall fail and return NULL. ]*/
TEST_FUNCTION(when_allocating_memory_for_the_resulting_string_fails_then_umockcallrecorder_get_expected_calls_fails)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    umockcall_stringify_call_result = "[a()]";
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();

    when_shall_realloc_fail = 1;

    // act
    result = umockcallrecorder_get_expected_calls(call_recorder);

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 1, realloc_call_count);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_031: [ If allocating memory for the resulting string fails, umockcallrecorder_get_expected_calls shall fail and return NULL. ]*/
TEST_FUNCTION(umockcallrecorder_get_expected_calls_with_a_matched_expected_call_yields_no_calls_in_the_string)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    umockcall_are_equal_call_result = 1;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);

    // act
    result = umockcallrecorder_get_expected_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "", result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_027: [ umockcallrecorder_get_expected_calls shall return a pointer to the string representation of all the expected calls. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_028: [ The string for each call shall be obtained by calling umockcall_stringify. ]*/
TEST_FUNCTION(umockcallrecorder_get_expected_calls_when_the_actual_call_does_not_match_the_expected_should_return_the_expected_call)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    umockcall_are_equal_call_result = 0;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    reset_all_calls();
    umockcall_stringify_call_result = "[a()]";

    // act
    result = umockcallrecorder_get_expected_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "[a()]", result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_054: [ Calls that have the ignore_all_calls property set shall not be reported in the expected call list. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_055: [ Getting the ignore_all_calls property shall be done by calling umockcall_get_ignore_all_calls. ]*/
TEST_FUNCTION(umockcallrecorder_get_expected_calls_with_1_expectd_call_with_ignore_all_calls_set_returns_an_empty_string)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    umockcall_are_equal_call_result = 0;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();
    umockcall_stringify_call_result = "[a()]";
    umockcall_get_ignore_all_calls_call_result = 1;

    // act
    result = umockcallrecorder_get_expected_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "", result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_056: [ If umockcall_get_ignore_all_calls returns a negative value then umockcallrecorder_get_expected_calls shall fail and return NULL. ]*/
TEST_FUNCTION(when_getting_the_ignore_all_cals_fails_umockcallrecorder_get_expected_calls_fails)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();
    umockcall_stringify_call_result = "[a()]";
    umockcall_are_equal_call_result = 0;
    umockcall_get_ignore_all_calls_call_result = -1;

    // act
    result = umockcallrecorder_get_expected_calls(call_recorder);

    // assert
    ASSERT_IS_NULL(result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_076: [ If a lock was created for the call recorder, umockcallrecorder_get_expected_calls shall acquire the lock in exclusive mode. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_077: [ If a lock was created for the call recorder, umockcallrecorder_get_expected_calls shall release the exclusive lock. ]*/
TEST_FUNCTION(umockcallrecorder_get_expected_calls_with_lock_functions_setup_locks_and_unlocks)
{
    // arrange
    const char* result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(test_lock_factory_create_lock, NULL);
    ASSERT_ARE_EQUAL(int, 0, umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1));
    reset_all_calls();
    umockcall_stringify_call_result = "[a()]";

    // act
    result = umockcallrecorder_get_expected_calls(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "[a()]", result);
    ASSERT_ARE_EQUAL(size_t, 6, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_acquire_exclusive, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_get_ignore_all_calls, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_stringify, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_realloc, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[4].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_release_exclusive, mocked_calls[5].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* umockcallrecorder_get_last_expected_call */

/* Tests_SRS_UMOCKCALLRECORDER_01_034: [ If no expected call has been recorded for umock_call_recorder then umockcallrecorder_get_last_expected_call shall fail and return NULL. ]*/
TEST_FUNCTION(umockcallrecorder_get_last_expected_call_without_any_expected_calls_returns_NULL)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);

    // act
    UMOCKCALL_HANDLE result = umockcallrecorder_get_last_expected_call(call_recorder);

    // assert
    ASSERT_IS_NULL(result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_033: [ If umock_call_recorder is NULL, umockcallrecorder_get_last_expected_call shall fail and return NULL. ]*/
TEST_FUNCTION(umockcallrecorder_get_last_expected_call_with_NULL_call_recorder_fails)
{
    // arrange

    // act
    UMOCKCALL_HANDLE result = umockcallrecorder_get_last_expected_call(NULL);

    // assert
    ASSERT_IS_NULL(result);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_032: [ umockcallrecorder_get_last_expected_call shall return the last expected call for the umock_call_recorder call recorder. ]*/
TEST_FUNCTION(umockcallrecorder_get_last_expected_call_with_1_expected_call_returns_the_last_expected_call)
{
    // arrange
    UMOCKCALL_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();

    // act
    result = umockcallrecorder_get_last_expected_call(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, result);
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_032: [ umockcallrecorder_get_last_expected_call shall return the last expected call for the umock_call_recorder call recorder. ]*/
TEST_FUNCTION(umockcallrecorder_get_last_expected_call_with_2_expected_calls_returns_the_last_expected_call)
{
    // arrange
    UMOCKCALL_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);

    // act
    result = umockcallrecorder_get_last_expected_call(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_2, result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_079: [ If a lock was created for the call recorder, umockcallrecorder_get_last_expected_call shall acquire the lock in shared mode. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_080: [ If a lock was created for the call recorder, umockcallrecorder_get_last_expected_call shall release the shared lock. ]*/
TEST_FUNCTION(umockcallrecorder_get_last_expected_call_with_lock_functions_setup_locks_and_unlocks)
{
    // arrange
    UMOCKCALL_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(test_lock_factory_create_lock, NULL);
    ASSERT_ARE_EQUAL(int, 0, umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1));
    reset_all_calls();

    // act
    result = umockcallrecorder_get_last_expected_call(call_recorder);

    // assert
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, result);
    ASSERT_ARE_EQUAL(size_t, 2, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_acquire_shared, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_release_shared, mocked_calls[1].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* umockcallrecorder_clone */

/* Tests_SRS_UMOCKCALLRECORDER_01_035: [ umockcallrecorder_clone shall clone a call recorder and return a handle to the newly cloned call recorder. ]*/
TEST_FUNCTION(umockcallrecorder_clone_on_a_recorder_with_no_calls_succeeds)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);

    // act
    UMOCKCALLRECORDER_HANDLE result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NOT_NULL(result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
    umockcallrecorder_destroy(result);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_036: [ If the umock_call_recorder argument is NULL, umockcallrecorder_clone shall fail and return NULL. ]*/
TEST_FUNCTION(umockcallrecorder_clone_with_NULL_returns_NULL)
{
    // arrange

    // act
    UMOCKCALLRECORDER_HANDLE result = umockcallrecorder_clone(NULL);

    // assert
    ASSERT_IS_NULL(result);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_037: [ If allocating memory for the new umock call recorder instance fails, umockcallrecorder_clone shall fail and return NULL. ]*/
TEST_FUNCTION(when_allocating_memory_for_call_recorder_fails_umockcallrecorder_clone_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    reset_all_calls();
    when_shall_malloc_fail = 1;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NULL(result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_038: [ umockcallrecorder_clone shall clone all the expected calls. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_039: [ Each expected call shall be cloned by calling umockcall_clone. ]*/
TEST_FUNCTION(umockcallrecorder_clone_with_one_expected_call_clones_the_expected_call)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();
    umockcall_clone_call_result = (UMOCKCALL_HANDLE)0x4245;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NOT_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 4, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, mocked_calls[2].u.umockcall_clone.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[3].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
    umockcallrecorder_destroy(result);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_038: [ umockcallrecorder_clone shall clone all the expected calls. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_039: [ Each expected call shall be cloned by calling umockcall_clone. ]*/
TEST_FUNCTION(umockcallrecorder_clone_with_2_expected_calls_clones_the_expected_call)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);
    reset_all_calls();
    umockcall_clone_call_result = (UMOCKCALL_HANDLE)0x4245;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NOT_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 5, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, mocked_calls[2].u.umockcall_clone.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_2, mocked_calls[3].u.umockcall_clone.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[4].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
    umockcallrecorder_destroy(result);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_040: [ If cloning an expected call fails, umockcallrecorder_clone shall fail and return NULL. ]*/
TEST_FUNCTION(when_cloning_the_expected_call_fails_umockcallrecorder_clone_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();
    umockcall_clone_call_result = NULL;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 5, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, mocked_calls[2].u.umockcall_clone.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[4].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_040: [ If cloning an expected call fails, umockcallrecorder_clone shall fail and return NULL. ]*/
TEST_FUNCTION(when_cloning_the_1st_out_of_2_expected_calls_fails_umockcallrecorder_clone_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);
    reset_all_calls();
    umockcall_clone_call_result = (UMOCKCALL_HANDLE)0x4245;
    when_shall_umockcall_clone_fail = 1;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 5, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, mocked_calls[2].u.umockcall_clone.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[4].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_040: [ If cloning an expected call fails, umockcallrecorder_clone shall fail and return NULL. ]*/
TEST_FUNCTION(when_cloning_the_2nd_out_of_2_expected_calls_fails_umockcallrecorder_clone_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);
    reset_all_calls();
    umockcall_clone_call_result = (UMOCKCALL_HANDLE)0x4245;
    when_shall_umockcall_clone_fail = 2;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 7, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, mocked_calls[2].u.umockcall_clone.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_2, mocked_calls[3].u.umockcall_clone.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_destroy, mocked_calls[4].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[5].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[6].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_052: [ If any error occurs, umockcallrecorder_clone shall fail and return NULL. ]*/
TEST_FUNCTION(when_allocating_memory_for_expected_calls_fails_umockcallrecorder_clone_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();
    umockcall_clone_call_result = (UMOCKCALL_HANDLE)0x4245;
    when_shall_malloc_fail = 2;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[2].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_041: [ umockcallrecorder_clone shall clone all the actual calls. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_042: [ Each actual call shall be cloned by calling umockcall_clone. ]*/
TEST_FUNCTION(umockcallrecorder_clone_with_one_actual_call_succeeds)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    reset_all_calls();
    umockcall_clone_call_result = (UMOCKCALL_HANDLE)0x4245;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NOT_NULL(result);

    ASSERT_ARE_EQUAL(size_t, 4, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_actual_umockcall_1, mocked_calls[3].u.umockcall_clone.umockcall);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
    umockcallrecorder_destroy(result);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_041: [ umockcallrecorder_clone shall clone all the actual calls. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_042: [ Each actual call shall be cloned by calling umockcall_clone. ]*/
TEST_FUNCTION(umockcallrecorder_clone_with_2_actual_calls_succeeds)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_2, &matched_call);
    reset_all_calls();
    umockcall_clone_call_result = (UMOCKCALL_HANDLE)0x4245;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NOT_NULL(result);

    ASSERT_ARE_EQUAL(size_t, 5, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_actual_umockcall_1, mocked_calls[3].u.umockcall_clone.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[4].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_actual_umockcall_2, mocked_calls[4].u.umockcall_clone.umockcall);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
    umockcallrecorder_destroy(result);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_043: [ If cloning an actual call fails, umockcallrecorder_clone shall fail and return NULL. ]*/
TEST_FUNCTION(when_cloning_actual_call_fails_umockcallrecorder_clone_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    reset_all_calls();
    umockcall_clone_call_result = NULL;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 7, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_actual_umockcall_1, mocked_calls[3].u.umockcall_clone.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[4].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[5].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[6].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_043: [ If cloning an actual call fails, umockcallrecorder_clone shall fail and return NULL. ]*/
TEST_FUNCTION(when_cloning_the_1st_of_2_actual_calls_fails_umockcallrecorder_clone_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_2, &matched_call);
    reset_all_calls();
    umockcall_clone_call_result = NULL;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 7, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_actual_umockcall_1, mocked_calls[3].u.umockcall_clone.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[4].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[5].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[6].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_043: [ If cloning an actual call fails, umockcallrecorder_clone shall fail and return NULL. ]*/
TEST_FUNCTION(when_cloning_the_2nd_of_2_actual_calls_fails_umockcallrecorder_clone_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call);
    (void)umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_2, &matched_call);
    reset_all_calls();
    when_shall_umockcall_clone_fail = 2;
    umockcall_clone_call_result = (UMOCKCALL_HANDLE)0x4245;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 9, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_actual_umockcall_1, mocked_calls[3].u.umockcall_clone.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[4].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_actual_umockcall_2, mocked_calls[4].u.umockcall_clone.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_destroy, mocked_calls[5].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[6].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[7].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[8].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Codes_SRS_UMOCKCALLRECORDER_01_052: [ If any error occurs, umockcallrecorder_clone shall fail and return NULL. ]*/
TEST_FUNCTION(when_allocating_memory_for_actual_calls_fails_umockcallrecorder_clone_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    UMOCKCALL_HANDLE matched_call;
    (void)umockcallrecorder_add_actual_call(call_recorder, test_expected_umockcall_1, &matched_call);
    reset_all_calls();
    umockcall_clone_call_result = (UMOCKCALL_HANDLE)0x4245;
    when_shall_malloc_fail = 2;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[2].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_082: [ If a lock was created for the call recorder umock_call_recorder, umockcallrecorder_clone shall acquire_the lock in shared mode for umock_call_recorder. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_083: [ If a lock was created for the call recorder umock_call_recorder, umockcallrecorder_clone shall release the shared lock for umock_call_recorder. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_085: [ If the lock_factory_create_lock associated with umock_call_recorder is not NULL, umockcallrecorder_clone shall create a new lock for the cloned call recorder. ]*/
TEST_FUNCTION(umockcallrecorder_clone_with_lock_functions_setup_locks_and_unlocks)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(test_lock_factory_create_lock, (void*)0x4242);
    UMOCKCALL_HANDLE matched_call;
    ASSERT_ARE_EQUAL(int, 0, umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call));
    reset_all_calls();
    umockcall_clone_call_result = (UMOCKCALL_HANDLE)0x4245;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NOT_NULL(result);

    ASSERT_ARE_EQUAL(size_t, 7, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_acquire_shared, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_factory_create_lock, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4242, mocked_calls[2].u.test_lock_factory_create_lock.params);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[4].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[5].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_actual_umockcall_1, mocked_calls[5].u.umockcall_clone.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_release_shared, mocked_calls[6].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
    umockcallrecorder_destroy(result);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_052: [ If any error occurs, umockcallrecorder_clone shall fail and return NULL. ]*/
TEST_FUNCTION(when_creating_the_new_lock_fails_umockcallrecorder_clone_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(test_lock_factory_create_lock, (void*)0x4242);
    UMOCKCALL_HANDLE matched_call;
    ASSERT_ARE_EQUAL(int, 0, umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call));
    reset_all_calls();
    test_lock_factory_create_lock_result = NULL;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NULL(result);

    ASSERT_ARE_EQUAL(size_t, 5, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_acquire_shared, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_factory_create_lock, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4242, mocked_calls[2].u.test_lock_factory_create_lock.params);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_release_shared, mocked_calls[4].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_052: [ If any error occurs, umockcallrecorder_clone shall fail and return NULL. ]*/
TEST_FUNCTION(when_cloning_the_call_fails_the_newly_created_lock_gets_destroyed)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(test_lock_factory_create_lock, (void*)0x4242);
    UMOCKCALL_HANDLE matched_call;
    ASSERT_ARE_EQUAL(int, 0, umockcallrecorder_add_actual_call(call_recorder, test_actual_umockcall_1, &matched_call));
    reset_all_calls();
    umockcall_clone_call_result = NULL;

    // act
    result = umockcallrecorder_clone(call_recorder);

    // assert
    ASSERT_IS_NULL(result);

    ASSERT_ARE_EQUAL(size_t, 11, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_acquire_shared, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_factory_create_lock, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4242, mocked_calls[2].u.test_lock_factory_create_lock.params);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[3].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_malloc, mocked_calls[4].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_clone, mocked_calls[5].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_actual_umockcall_1, mocked_calls[5].u.umockcall_clone.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[6].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[7].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_destroy, mocked_calls[8].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_lock_handle, mocked_calls[8].u.test_lock_destroy.lock);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_mock_free, mocked_calls[9].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_release_shared, mocked_calls[10].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* umockcallrecorder_get_expected_call_count */

/* Tests_SRS_UMOCKCALLRECORDER_01_044: [ umockcallrecorder_get_expected_call_count shall return in the expected_call_count argument the number of expected calls associated with the call recorder. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_045: [ On success umockcallrecorder_get_expected_call_count shall return 0. ]*/
TEST_FUNCTION(umockcallrecorder_get_expected_call_count_when_no_expected_calls_are_there_yields_0)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    size_t expected_call_count;

    // act
    result = umockcallrecorder_get_expected_call_count(call_recorder, &expected_call_count);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 0, expected_call_count);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_044: [ umockcallrecorder_get_expected_call_count shall return in the expected_call_count argument the number of expected calls associated with the call recorder. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_045: [ On success umockcallrecorder_get_expected_call_count shall return 0. ]*/
TEST_FUNCTION(umockcallrecorder_get_expected_call_count_when_2_expected_calls_are_there_yields_2)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    size_t expected_call_count;
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);

    // act
    result = umockcallrecorder_get_expected_call_count(call_recorder, &expected_call_count);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 2, expected_call_count);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_046: [ If any of the arguments is NULL, umockcallrecorder_get_expected_call_count shall return a non-zero value. ]*/
TEST_FUNCTION(umockcallrecorder_get_expected_call_with_NULL_call_recorder_fails)
{
    // arrange
    size_t expected_call_count;

    // act
    int result = umockcallrecorder_get_expected_call_count(NULL, &expected_call_count);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_046: [ If any of the arguments is NULL, umockcallrecorder_get_expected_call_count shall return a non-zero value. ]*/
TEST_FUNCTION(umockcallrecorder_get_expected_call_with_NULL_expected_call_count_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);

    // act
    int result = umockcallrecorder_get_expected_call_count(call_recorder, NULL);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_086: [ If a lock was created for the call recorder, umockcallrecorder_get_expected_call_count shall acquire the lock in shared mode. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_087: [ If a lock was created for the call recorder, umockcallrecorder_get_expected_call_count shall release the shared lock. ]*/
TEST_FUNCTION(umockcallrecorder_get_expected_call_count_with_lock_functions_setup_locks_and_unlocks)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(test_lock_factory_create_lock, NULL);
    size_t expected_call_count;
    reset_all_calls();

    // act
    result = umockcallrecorder_get_expected_call_count(call_recorder, &expected_call_count);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 0, expected_call_count);
    ASSERT_ARE_EQUAL(size_t, 2, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_acquire_shared, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_release_shared, mocked_calls[1].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* umockcallrecorder_fail_call */

/* Tests_SRS_UMOCKCALLRECORDER_01_047: [ umockcallrecorder_fail_call shall mark an expected call as to be failed by calling umockcall_set_fail_call with a 1 value for fail_call. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_048: [ On success, umockcallrecorder_fail_call shall return 0. ]*/
TEST_FUNCTION(umockcallrecorder_fail_call_sets_fail_call_to_1_for_the_first_call)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);
    reset_all_calls();

    // act
    result = umockcallrecorder_fail_call(call_recorder, 0);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_set_fail_call, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, mocked_calls[0].u.umockcall_set_fail_call.umockcall);
    ASSERT_ARE_EQUAL(int, 1, mocked_calls[0].u.umockcall_set_fail_call.fail_call);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_047: [ umockcallrecorder_fail_call shall mark an expected call as to be failed by calling umockcall_set_fail_call with a 1 value for fail_call. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_048: [ On success, umockcallrecorder_fail_call shall return 0. ]*/
TEST_FUNCTION(umockcallrecorder_fail_call_sets_fail_call_to_1_for_the_second_call)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);
    reset_all_calls();

    // act
    result = umockcallrecorder_fail_call(call_recorder, 1);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_set_fail_call, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_2, mocked_calls[0].u.umockcall_set_fail_call.umockcall);
    ASSERT_ARE_EQUAL(int, 1, mocked_calls[0].u.umockcall_set_fail_call.fail_call);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_047: [ umockcallrecorder_fail_call shall mark an expected call as to be failed by calling umockcall_set_fail_call with a 1 value for fail_call. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_048: [ On success, umockcallrecorder_fail_call shall return 0. ]*/
TEST_FUNCTION(two_umockcallrecorder_fail_call_calls_succeed)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);
    umockcallrecorder_fail_call(call_recorder, 0);
    reset_all_calls();

    // act
    result = umockcallrecorder_fail_call(call_recorder, 1);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_set_fail_call, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_2, mocked_calls[0].u.umockcall_set_fail_call.umockcall);
    ASSERT_ARE_EQUAL(int, 1, mocked_calls[0].u.umockcall_set_fail_call.fail_call);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_049: [ If umock_call_recorder is NULL, umockcallrecorder_fail_call shall return a non-zero value. ]*/
TEST_FUNCTION(umockcallrecorder_fail_call_with_NULL_call_recorder_fails)
{
    // arrange

    // act
    int result = umockcallrecorder_fail_call(NULL, 0);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_050: [ If index is invalid, umockcallrecorder_fail_call shall return a non-zero value. ]*/
TEST_FUNCTION(umockcallrecorder_fail_call_with_index_too_high_fails)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();

    // act
    result = umockcallrecorder_fail_call(call_recorder, 1);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_050: [ If index is invalid, umockcallrecorder_fail_call shall return a non-zero value. ]*/
TEST_FUNCTION(umockcallrecorder_fail_call_with_0_index_when_no_calls_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    reset_all_calls();

    // act
    int result = umockcallrecorder_fail_call(call_recorder, 0);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_051: [ If umockcall_set_fail_call fails, umockcallrecorder_fail_call shall return a non-zero value. ]*/
TEST_FUNCTION(when_umockcall_set_fail_call_fails_then_umockcallrecorder_fail_call_fails)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();
    umockcall_set_fail_call_call_result = 1;

    // act
    result = umockcallrecorder_fail_call(call_recorder, 0);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_set_fail_call, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, mocked_calls[0].u.umockcall_set_fail_call.umockcall);
    ASSERT_ARE_EQUAL(int, 1, mocked_calls[0].u.umockcall_set_fail_call.fail_call);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_089: [ If a lock was created for the call recorder, umockcallrecorder_fail_call shall acquire the lock in exclusive mode. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_090: [ If a lock was created for the call recorder, umockcallrecorder_fail_call shall release the exclusive lock. ]*/
TEST_FUNCTION(umockcallrecorder_fail_call_with_lock_functions_set_locks_and_unlocks)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(test_lock_factory_create_lock, NULL);
    ASSERT_ARE_EQUAL(int, 0, umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1));
    reset_all_calls();

    // act
    result = umockcallrecorder_fail_call(call_recorder, 0);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_acquire_exclusive, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_set_fail_call, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, mocked_calls[1].u.umockcall_set_fail_call.umockcall);
    ASSERT_ARE_EQUAL(int, 1, mocked_calls[1].u.umockcall_set_fail_call.fail_call);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_release_exclusive, mocked_calls[2].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* umockcallrecorder_can_call_fail */

/* Tests_SRS_UMOCKCALLRECORDER_31_061: [ umockcallrecorder_can_call_fail shall determine whether given call can fail or not by calling umockcall_get_call_can_fail. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_31_059: [ umockcallrecorder_can_call_fail shall return in the can_call_fail argument whether the call can fail or not. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_31_060: [ On success umockcallrecorder_can_call_fail shall return 0. ]*/
TEST_FUNCTION(umockcallrecorder_can_call_fail_index_0_caller_sets_0)
{
    // arrange
    int result;
    int can_call_fail;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);
    reset_all_calls();

    // act
    umockcall_get_call_can_fail_result = 0;
    result = umockcallrecorder_can_call_fail(call_recorder, 0, &can_call_fail);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(int, 0, can_call_fail);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_get_call_can_fail, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, mocked_calls[0].u.umockcall_get_call_can_fail.umockcall);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_31_061: [ umockcallrecorder_can_call_fail shall determine whether given call can fail or not by calling umockcall_get_call_can_fail. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_31_059: [ umockcallrecorder_can_call_fail shall return in the can_call_fail argument whether the call can fail or not. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_31_060: [ On success umockcallrecorder_can_call_fail shall return 0. ]*/
TEST_FUNCTION(umockcallrecorder_can_call_fail_index_0_caller_sets_1)
{
    // arrange
    int result;
    int can_call_fail;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);
    reset_all_calls();

    // act
    umockcall_get_call_can_fail_result = 1;
    result = umockcallrecorder_can_call_fail(call_recorder, 0, &can_call_fail);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(int, 1, can_call_fail);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_get_call_can_fail, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, mocked_calls[0].u.umockcall_get_call_can_fail.umockcall);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_31_061: [ umockcallrecorder_can_call_fail shall determine whether given call can fail or not by calling umockcall_get_call_can_fail. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_31_059: [ umockcallrecorder_can_call_fail shall return in the can_call_fail argument whether the call can fail or not. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_31_060: [ On success umockcallrecorder_can_call_fail shall return 0. ]*/
TEST_FUNCTION(umockcallrecorder_can_call_fail_index_1_caller_sets_1)
{
    // arrange
    int result;
    int can_call_fail;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_2);
    reset_all_calls();

    // act
    umockcall_get_call_can_fail_result = 1;
    result = umockcallrecorder_can_call_fail(call_recorder, 1, &can_call_fail);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(int, 1, can_call_fail);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_get_call_can_fail, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_2, mocked_calls[0].u.umockcall_get_call_can_fail.umockcall);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_31_056: [ If umock_call_recorder or call_can_fail is NULL, umockcallrecorder_can_call_fail shall return a non-zero value. ]*/
TEST_FUNCTION(umockcallrecorder_can_call_fail_with_NULL_call_recorder_fails)
{
    // arrange
    int can_call_fail;

    // act
    int result = umockcallrecorder_can_call_fail(NULL, 0, &can_call_fail);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);
}

/* Tests_SRS_UMOCKCALLRECORDER_31_056: [ If umock_call_recorder or call_can_fail is NULL, umockcallrecorder_can_call_fail shall return a non-zero value. ]*/
TEST_FUNCTION(umockcallrecorder_can_call_fail_with_NULL_can_call_fail_fails)
{
    // arrange
    int result;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();

    // act
    result = umockcallrecorder_can_call_fail(call_recorder, 1, NULL);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_31_057: [ If index is greater or equal to the current expected calls count, umockcallrecorder_can_call_fail shall return a non-zero value. ]*/
TEST_FUNCTION(umockcallrecorder_can_call_fail_with_index_too_high_fails)
{
    // arrange
    int result;
    int can_call_fail;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();

    // act
    result = umockcallrecorder_can_call_fail(call_recorder, 1, &can_call_fail);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_31_058: [ If umockcall_get_call_can_fail returns -1, umockcallrecorder_can_call_fail shall return an error to the caller  ]*/
TEST_FUNCTION(umockcallrecorder_can_call_fail_when_umockcall_fails)
{
    // arrange
    int result;
    int can_call_fail;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(NULL, NULL);
    (void)umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1);
    reset_all_calls();
    umockcall_get_call_can_fail_result = -1;

    // act
    result = umockcallrecorder_can_call_fail(call_recorder, 0, &can_call_fail);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_get_call_can_fail, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, mocked_calls[0].u.umockcall_get_call_can_fail.umockcall);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

/* Tests_SRS_UMOCKCALLRECORDER_01_092: [ If a lock was created for the call recorder, umockcallrecorder_can_call_fail shall acquire the lock in exclusive mode. ]*/
/* Tests_SRS_UMOCKCALLRECORDER_01_094: [ If a lock was created for the call recorder, umockcallrecorder_can_call_fail shall release the exclusive lock. ]*/
TEST_FUNCTION(umockcallrecorder_can_call_fail_with_lock_functions_setup_locks_and_unlocks)
{
    // arrange
    int result;
    int can_call_fail;
    UMOCKCALLRECORDER_HANDLE call_recorder = umockcallrecorder_create(test_lock_factory_create_lock, NULL);
    ASSERT_ARE_EQUAL(int, 0, umockcallrecorder_add_expected_call(call_recorder, test_expected_umockcall_1));
    reset_all_calls();
    umockcall_get_call_can_fail_result = 0;

    // act
    result = umockcallrecorder_can_call_fail(call_recorder, 0, &can_call_fail);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(int, 0, can_call_fail);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_acquire_shared, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcall_get_call_can_fail, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_umockcall_1, mocked_calls[1].u.umockcall_get_call_can_fail.umockcall);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_lock_release_shared, mocked_calls[2].call_type);

    // cleanup
    umockcallrecorder_destroy(call_recorder);
}

END_TEST_SUITE(TEST_SUITE_NAME_FROM_CMAKE)
