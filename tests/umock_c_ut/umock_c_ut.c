// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include "macro_utils/macro_utils.h" // IWYU pragma: keep

// TEST_DEFINE_ENUM_TYPE will use wchar.h, which we technically get from testrunnerswitcher.h
// IWYU pragma: no_include <wchar.h>
#include "testrunnerswitcher.h"

#include "umock_c/umockalloc.h"          // for umockalloc_free, umockalloc_...
#include "umock_c/umockcall.h"           // for UMOCKCALL_HANDLE, UMOCKCALL_TAG
#include "umock_c/umockcallrecorder.h"
#include "umock_c/umocktypes.h"
#include "umock_c/umocktypes_c.h"
#include "umock_c/umock_c.h"
#include "umock_c/umock_log.h"
#include "umock_c/umock_lock_factory.h"
#include "umock_c/umock_lock_if.h"       // for UMOCK_C_LOCK_HANDLE

void UMOCK_LOG(const char* format, ...)
{
    (void)format;
}

static UMOCKCALL_HANDLE test_expected_call = (UMOCKCALL_HANDLE)0x4242;
static UMOCKCALL_HANDLE test_actual_call = (UMOCKCALL_HANDLE)0x4243;
static UMOCKCALLRECORDER_HANDLE test_call_recorder = (UMOCKCALLRECORDER_HANDLE)0x4244;
static UMOCKCALLRECORDER_HANDLE test_cloned_call_recorder = (UMOCKCALLRECORDER_HANDLE)0x4245;

static int umocktypes_init_result;
static int umocktypes_c_register_types_result;

typedef struct umockcallrecorder_create_CALL_TAG
{
    UMOCK_C_LOCK_FACTORY_CREATE_LOCK_FUNC lock_factory_create_lock;
    void* lock_factory_create_lock_params;
} umockcallrecorder_create_CALL;

static UMOCKCALLRECORDER_HANDLE umockcallrecorder_create_result;

typedef struct umockcallrecorder_destroy_CALL_TAG
{
    UMOCKCALLRECORDER_HANDLE umock_call_recorder;
} umockcallrecorder_destroy_CALL;

typedef struct umockcallrecorder_reset_all_calls_CALL_TAG
{
    UMOCKCALLRECORDER_HANDLE umock_call_recorder;
} umockcallrecorder_reset_all_calls_CALL;

static int umockcallrecorder_reset_all_calls_result;

typedef struct umockcallrecorder_get_actual_calls_CALL_TAG
{
    UMOCKCALLRECORDER_HANDLE umock_call_recorder;
} umockcallrecorder_get_actual_calls_CALL;

static const char* umockcallrecorder_get_actual_calls_result;

typedef struct umockcallrecorder_get_expected_calls_CALL_TAG
{
    UMOCKCALLRECORDER_HANDLE umock_call_recorder;
} umockcallrecorder_get_expected_calls_CALL;

static const char* umockcallrecorder_get_expected_calls_result;

typedef struct umockcallrecorder_get_last_expected_call_CALL_TAG
{
    UMOCKCALLRECORDER_HANDLE umock_call_recorder;
} umockcallrecorder_get_last_expected_call_CALL;

static UMOCKCALL_HANDLE umockcallrecorder_get_last_expected_call_result;

typedef struct umockcallrecorder_add_expected_call_CALL_TAG
{
    UMOCKCALLRECORDER_HANDLE umock_call_recorder;
    UMOCKCALL_HANDLE mock_call;
} umockcallrecorder_add_expected_call_CALL;

static int umockcallrecorder_add_expected_call_result;

typedef struct umockcallrecorder_add_actual_call_CALL_TAG
{
    UMOCKCALLRECORDER_HANDLE umock_call_recorder;
    UMOCKCALL_HANDLE mock_call;
    UMOCKCALL_HANDLE* matched_call;
} umockcallrecorder_add_actual_call_CALL;

static int umockcallrecorder_add_actual_call_result;

typedef struct umockcallrecorder_clone_CALL_TAG
{
    UMOCKCALLRECORDER_HANDLE umock_call_recorder;
} umockcallrecorder_clone_CALL;

static UMOCKCALLRECORDER_HANDLE umockcallrecorder_clone_result;

typedef struct umocktypes_init_CALL_TAG
{
    int dummy;
} umocktypes_init_CALL;

typedef struct umocktypes_deinit_CALL_TAG
{
    int dummy;
} umocktypes_deinit_CALL;

typedef struct umocktypes_c_register_types_CALL_TAG
{
    int dummy;
} umocktypes_c_register_types_CALL;

typedef struct test_on_umock_c_error_CALL_TAG
{
    UMOCK_C_ERROR_CODE error_code;
} test_on_umock_c_error_CALL;

typedef union TEST_MOCK_CALL_UNION_TAG
{
    test_on_umock_c_error_CALL test_on_umock_c_error;
    umockcallrecorder_create_CALL umockcallrecorder_create;
    umockcallrecorder_get_last_expected_call_CALL umockcallrecorder_get_last_expected_call;
    umockcallrecorder_get_expected_calls_CALL umockcallrecorder_get_expected_calls;
    umockcallrecorder_destroy_CALL umockcallrecorder_destroy;
    umockcallrecorder_reset_all_calls_CALL umockcallrecorder_reset_all_calls;
    umockcallrecorder_get_actual_calls_CALL umockcallrecorder_get_actual_calls;
    umockcallrecorder_add_expected_call_CALL umockcallrecorder_add_expected_call;
    umockcallrecorder_add_actual_call_CALL umockcallrecorder_add_actual_call;
    umockcallrecorder_clone_CALL umockcallrecorder_clone;
    umocktypes_init_CALL umocktypes_init;
    umocktypes_deinit_CALL umocktypes_deinit;
    umocktypes_c_register_types_CALL umocktypes_c_register_types;
} TEST_MOCK_CALL_UNION;

#define TEST_MOCK_CALL_TYPE_VALUES \
    TEST_MOCK_CALL_TYPE_test_on_umock_c_error, \
    TEST_MOCK_CALL_TYPE_umockcallrecorder_create, \
    TEST_MOCK_CALL_TYPE_umockcallrecorder_get_last_expected_call, \
    TEST_MOCK_CALL_TYPE_umockcallrecorder_get_expected_calls, \
    TEST_MOCK_CALL_TYPE_umockcallrecorder_destroy, \
    TEST_MOCK_CALL_TYPE_umockcallrecorder_reset_all_calls, \
    TEST_MOCK_CALL_TYPE_umockcallrecorder_get_actual_calls, \
    TEST_MOCK_CALL_TYPE_umockcallrecorder_add_expected_call, \
    TEST_MOCK_CALL_TYPE_umockcallrecorder_add_actual_call, \
    TEST_MOCK_CALL_TYPE_umockcallrecorder_clone, \
    TEST_MOCK_CALL_TYPE_umocktypes_init, \
    TEST_MOCK_CALL_TYPE_umocktypes_deinit, \
    TEST_MOCK_CALL_TYPE_umocktypes_c_register_types \

MU_DEFINE_ENUM(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_VALUES)
MU_DEFINE_ENUM_STRINGS(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_VALUES)
TEST_DEFINE_ENUM_TYPE(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_VALUES)

TEST_DEFINE_ENUM_TYPE(UMOCK_C_ERROR_CODE, UMOCK_C_ERROR_CODE_VALUES)

typedef struct TEST_MOCK_CALL_TAG
{
    TEST_MOCK_CALL_TYPE call_type;
    TEST_MOCK_CALL_UNION u;
} TEST_MOCK_CALL;

static size_t mocked_call_count;
static TEST_MOCK_CALL* mocked_calls;

UMOCKCALLRECORDER_HANDLE umockcallrecorder_create(UMOCK_C_LOCK_FACTORY_CREATE_LOCK_FUNC lock_factory_create_lock, void* lock_factory_create_lock_params)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcallrecorder_create;
        mocked_calls[mocked_call_count].u.umockcallrecorder_create.lock_factory_create_lock = lock_factory_create_lock;
        mocked_calls[mocked_call_count].u.umockcallrecorder_create.lock_factory_create_lock_params = lock_factory_create_lock_params;
        mocked_call_count++;
    }

    return umockcallrecorder_create_result;
}

void umockcallrecorder_destroy(UMOCKCALLRECORDER_HANDLE umock_call_recorder)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcallrecorder_destroy;
        mocked_calls[mocked_call_count].u.umockcallrecorder_destroy.umock_call_recorder = umock_call_recorder;
        mocked_call_count++;
    }
}

int umockcallrecorder_reset_all_calls(UMOCKCALLRECORDER_HANDLE umock_call_recorder)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcallrecorder_reset_all_calls;
        mocked_calls[mocked_call_count].u.umockcallrecorder_reset_all_calls.umock_call_recorder = umock_call_recorder;
        mocked_call_count++;
    }

    return umockcallrecorder_reset_all_calls_result;
}

int umockcallrecorder_add_expected_call(UMOCKCALLRECORDER_HANDLE umock_call_recorder, UMOCKCALL_HANDLE mock_call)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcallrecorder_add_expected_call;
        mocked_calls[mocked_call_count].u.umockcallrecorder_add_expected_call.umock_call_recorder = umock_call_recorder;
        mocked_calls[mocked_call_count].u.umockcallrecorder_add_expected_call.mock_call = mock_call;
        mocked_call_count++;
    }

    return umockcallrecorder_add_expected_call_result;
}

int umockcallrecorder_add_actual_call(UMOCKCALLRECORDER_HANDLE umock_call_recorder, UMOCKCALL_HANDLE mock_call, UMOCKCALL_HANDLE* matched_call)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcallrecorder_add_actual_call;
        mocked_calls[mocked_call_count].u.umockcallrecorder_add_actual_call.umock_call_recorder = umock_call_recorder;
        mocked_calls[mocked_call_count].u.umockcallrecorder_add_actual_call.mock_call = mock_call;
        mocked_calls[mocked_call_count].u.umockcallrecorder_add_actual_call.matched_call = matched_call;
        mocked_call_count++;
    }

    return umockcallrecorder_add_actual_call_result;
}

UMOCKCALLRECORDER_HANDLE umockcallrecorder_clone(UMOCKCALLRECORDER_HANDLE umock_call_recorder)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcallrecorder_clone;
        mocked_calls[mocked_call_count].u.umockcallrecorder_clone.umock_call_recorder = umock_call_recorder;
        mocked_call_count++;
    }

    return umockcallrecorder_clone_result;
}

const char* umockcallrecorder_get_actual_calls(UMOCKCALLRECORDER_HANDLE umock_call_recorder)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcallrecorder_get_actual_calls;
        mocked_calls[mocked_call_count].u.umockcallrecorder_get_actual_calls.umock_call_recorder = umock_call_recorder;
        mocked_call_count++;
    }

    return umockcallrecorder_get_actual_calls_result;
}

const char* umockcallrecorder_get_expected_calls(UMOCKCALLRECORDER_HANDLE umock_call_recorder)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcallrecorder_get_expected_calls;
        mocked_calls[mocked_call_count].u.umockcallrecorder_get_expected_calls.umock_call_recorder = umock_call_recorder;
        mocked_call_count++;
    }

    return umockcallrecorder_get_expected_calls_result;
}

UMOCKCALL_HANDLE umockcallrecorder_get_last_expected_call(UMOCKCALLRECORDER_HANDLE umock_call_recorder)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umockcallrecorder_get_last_expected_call;
        mocked_calls[mocked_call_count].u.umockcallrecorder_get_last_expected_call.umock_call_recorder = umock_call_recorder;
        mocked_call_count++;
    }

    return umockcallrecorder_get_last_expected_call_result;
}

int umocktypes_init(void)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umocktypes_init;
        mocked_call_count++;
    }

    return umocktypes_init_result;
}

void umocktypes_deinit(void)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umocktypes_deinit;
        mocked_call_count++;
    }
}

int umocktypes_c_register_types(void)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_umocktypes_c_register_types;
        mocked_call_count++;
    }

    return umocktypes_c_register_types_result;
}

static void test_on_umock_c_error(UMOCK_C_ERROR_CODE error_code)
{
    TEST_MOCK_CALL* new_calls = (TEST_MOCK_CALL*)realloc(mocked_calls, sizeof(TEST_MOCK_CALL) * (mocked_call_count + 1));
    if (new_calls != NULL)
    {
        mocked_calls = new_calls;
        mocked_calls[mocked_call_count].call_type = TEST_MOCK_CALL_TYPE_test_on_umock_c_error;
        mocked_calls[mocked_call_count].u.test_on_umock_c_error.error_code = error_code;
        mocked_call_count++;
    }
}

void reset_all_calls(void)
{
    mocked_call_count = 0;
    if (mocked_calls != NULL)
    {
        free(mocked_calls);
        mocked_calls = NULL;
    }

    umocktypes_init_result = 0;
    umocktypes_c_register_types_result = 0;
    umockcallrecorder_create_result = test_call_recorder;
    umockcallrecorder_reset_all_calls_result = 0;
    umockcallrecorder_get_actual_calls_result = NULL;
    umockcallrecorder_get_expected_calls_result = NULL;
    umockcallrecorder_get_last_expected_call_result = NULL;
    umockcallrecorder_add_expected_call_result = 0;
    umockcallrecorder_add_actual_call_result = 0;
    umockcallrecorder_clone_result = test_cloned_call_recorder;
}

void* umockalloc_malloc(size_t size)
{
    return malloc(size);
}

void umockalloc_free(void* ptr)
{
    free(ptr);
}

static UMOCK_C_LOCK_HANDLE test_lock_factory_create_lock(void* params)
{
    (void)params;
    return NULL;
}

static TEST_MUTEX_HANDLE test_mutex;

BEGIN_TEST_SUITE(umock_c_unittests)

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

    umock_c_deinit();
    reset_all_calls();
}

TEST_FUNCTION_CLEANUP(test_function_cleanup)
{
    reset_all_calls();

    TEST_MUTEX_RELEASE(test_mutex);
}

/* umock_c_init */

/* Tests_SRS_UMOCK_C_01_001: [umock_c_init shall initialize the umock library.] */
/* Tests_SRS_UMOCK_C_01_023: [ umock_c_init shall initialize the umock types by calling umocktypes_init. ]*/
/* Tests_SRS_UMOCK_C_01_004: [ On success, umock_c_init shall return 0. ]*/
/* Tests_SRS_UMOCK_C_01_002: [ umock_c_init shall register the C native types by calling umocktypes_c_register_types. ]*/
/* Tests_SRS_UMOCK_C_01_003: [ umock_c_init shall create a call recorder by calling umockcallrecorder_create. ]*/
/* Tests_SRS_UMOCK_C_01_006: [ The on_umock_c_error callback shall be stored to be used for later error callbacks. ]*/
TEST_FUNCTION(when_all_calls_succeed_umock_c_init_succeeds)
{
    // arrange

    // act
    int result = umock_c_init(test_on_umock_c_error);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_init, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_c_register_types, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_create, mocked_calls[2].call_type);
}

/* Tests_SRS_UMOCK_C_01_005: [ If any of the calls fails, umock_c_init shall fail and return a non-zero value. ]*/
TEST_FUNCTION(when_umocktypes_init_fails_then_umock_c_init_fails)
{
    // arrange
    int result;
    umocktypes_init_result = 1;

    // act
    result = umock_c_init(test_on_umock_c_error);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_init, mocked_calls[0].call_type);
}

/* Tests_SRS_UMOCK_C_01_005: [ If any of the calls fails, umock_c_init shall fail and return a non-zero value. ]*/
TEST_FUNCTION(when_umocktypes_c_register_types_fails_then_umock_c_init_fails)
{
    // arrange
    int result;
    umocktypes_c_register_types_result = 1;

    // act
    result = umock_c_init(test_on_umock_c_error);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 2, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_init, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_c_register_types, mocked_calls[1].call_type);
}

/* Tests_SRS_UMOCK_C_01_005: [ If any of the calls fails, umock_c_init shall fail and return a non-zero value. ]*/
TEST_FUNCTION(when_creating_the_call_recorder_fails_then_umock_c_init_fails)
{
    // arrange
    int result;
    umockcallrecorder_create_result = NULL;

    // act
    result = umock_c_init(test_on_umock_c_error);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 4, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_init, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_c_register_types, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_create, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_deinit, mocked_calls[3].call_type);
}

/* Tests_SRS_UMOCK_C_01_007: [ umock_c_init when umock is already initialized shall fail and return a non-zero value. ]*/
TEST_FUNCTION(umock_c_init_when_already_initialized_fails)
{
    // arrange
    int result;
    umock_c_init(test_on_umock_c_error);

    // act
    result = umock_c_init(test_on_umock_c_error);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
}

/* Tests_SRS_UMOCK_C_01_024: [ on_umock_c_error shall be optional. ]*/
TEST_FUNCTION(umock_c_init_with_NULL_callback_succeeds)
{
    // arrange

    // act
    int result = umock_c_init(NULL);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_init, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_c_register_types, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_create, mocked_calls[2].call_type);
}

/* umock_c_init_with_lock_factory */

/* Tests_SRS_UMOCK_C_01_042: [ umock_c_init_with_lock_factory shall perform the same initialization like umock_c_init while passing lock_factory_create_lock and lock_factory_create_lock_params as arguments to umockcallrecorder_create. ] */
/* Tests_SRS_UMOCK_C_01_043: [ On success, umock_c_init_with_lock_factory shall return 0. ]*/
TEST_FUNCTION(umock_c_init_with_lock_factory_succeeds)
{
    // arrange

    // act
    int result = umock_c_init_with_lock_factory(test_on_umock_c_error, test_lock_factory_create_lock, (void*)0x4242);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_init, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_c_register_types, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_create, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_lock_factory_create_lock, mocked_calls[2].u.umockcallrecorder_create.lock_factory_create_lock);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4242, mocked_calls[2].u.umockcallrecorder_create.lock_factory_create_lock_params);
}

/* Tests_SRS_UMOCK_C_01_044: [ If any of the calls fails, umock_c_init_with_lock_factory shall fail and return a non-zero value. ]*/
TEST_FUNCTION(when_umocktypes_init_fails_then_umock_c_init_with_lock_factory_fails)
{
    // arrange
    int result;
    umocktypes_init_result = 1;

    // act
    result = umock_c_init_with_lock_factory(test_on_umock_c_error, test_lock_factory_create_lock, (void*)0x4242);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_init, mocked_calls[0].call_type);
}

/* Tests_SRS_UMOCK_C_01_044: [ If any of the calls fails, umock_c_init_with_lock_factory shall fail and return a non-zero value. ]*/
TEST_FUNCTION(when_umocktypes_c_register_types_fails_then_umock_c_init_with_lock_factory_fails)
{
    // arrange
    int result;
    umocktypes_c_register_types_result = 1;

    // act
    result = umock_c_init_with_lock_factory(test_on_umock_c_error, test_lock_factory_create_lock, (void*)0x4242);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 2, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_init, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_c_register_types, mocked_calls[1].call_type);
}

/* Tests_SRS_UMOCK_C_01_044: [ If any of the calls fails, umock_c_init_with_lock_factory shall fail and return a non-zero value. ]*/
TEST_FUNCTION(when_creating_the_call_recorder_fails_then_umock_c_init_with_lock_factory_fails)
{
    // arrange
    int result;
    umockcallrecorder_create_result = NULL;

    // act
    result = umock_c_init_with_lock_factory(test_on_umock_c_error, test_lock_factory_create_lock, (void*)0x4242);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 4, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_init, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_c_register_types, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_create, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_lock_factory_create_lock, mocked_calls[2].u.umockcallrecorder_create.lock_factory_create_lock);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4242, mocked_calls[2].u.umockcallrecorder_create.lock_factory_create_lock_params);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_deinit, mocked_calls[3].call_type);
}

/* Tests_SRS_UMOCK_C_01_007: [ umock_c_init when umock is already initialized shall fail and return a non-zero value. ]*/
TEST_FUNCTION(umock_c_init_with_lock_factory_when_already_initialized_fails)
{
    // arrange
    int result;
    umock_c_init(test_on_umock_c_error);

    // act
    result = umock_c_init_with_lock_factory(test_on_umock_c_error, test_lock_factory_create_lock, (void*)0x4242);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
}

/* Tests_SRS_UMOCK_C_01_024: [ on_umock_c_error shall be optional. ]*/
TEST_FUNCTION(umock_c_init_with_lock_factory_with_NULL_callback_succeeds)
{
    // arrange

    // act
    int result = umock_c_init_with_lock_factory(NULL, test_lock_factory_create_lock, (void*)0x4242);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 3, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_init, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_c_register_types, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_create, mocked_calls[2].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_lock_factory_create_lock, mocked_calls[2].u.umockcallrecorder_create.lock_factory_create_lock);
    ASSERT_ARE_EQUAL(void_ptr, (void*)0x4242, mocked_calls[2].u.umockcallrecorder_create.lock_factory_create_lock_params);
}

/* umock_c_deinit */

/* Tests_SRS_UMOCK_C_01_008: [ umock_c_deinit shall deinitialize the umock types by calling umocktypes_deinit. ]*/
/* Tests_SRS_UMOCK_C_01_009: [ umock_c_deinit shall free the call recorder created in umock_c_init. ]*/
TEST_FUNCTION(umock_c_deinit_deinitializes_types_and_destroys_call_recorder)
{
    // arrange
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(NULL));
    reset_all_calls();

    // act
    umock_c_deinit();

    // assert
    ASSERT_ARE_EQUAL(size_t, 2, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_destroy, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[0].u.umockcallrecorder_destroy.umock_call_recorder);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umocktypes_deinit, mocked_calls[1].call_type);
}

/* Tests_SRS_UMOCK_C_01_008: [ umock_c_deinit shall deinitialize the umock types by calling umocktypes_deinit. ]*/
/* Tests_SRS_UMOCK_C_01_009: [ umock_c_deinit shall free the call recorder created in umock_c_init. ]*/
TEST_FUNCTION(umock_c_deinit_when_not_initialized_does_nothing)
{
    // arrange
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(NULL));
    umock_c_deinit();
    reset_all_calls();

    // act
    umock_c_deinit();

    // assert
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);
}

/* umock_c_reset_all_calls */

/* Tests_SRS_UMOCK_C_01_012: [ If the module is not initialized, umock_c_reset_all_calls shall do nothing. ]*/
TEST_FUNCTION(umock_c_reset_all_calls_when_the_module_is_not_initialized_does_nothing)
{
    // arrange

    // act
    umock_c_reset_all_calls();

    // assert
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);
}

/* Tests_SRS_UMOCK_C_01_011: [ umock_c_reset_all_calls shall reset all calls by calling umockcallrecorder_reset_all_calls on the call recorder created in umock_c_init. ]*/
TEST_FUNCTION(umock_c_reset_all_calls_calls_the_call_recorder_reset_all_calls)
{
    // arrange
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(NULL));
    reset_all_calls();

    // act
    umock_c_reset_all_calls();

    // assert
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_reset_all_calls, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[0].u.umockcallrecorder_reset_all_calls.umock_call_recorder);
}

/* Tests_SRS_UMOCK_C_01_025: [ If the underlying umockcallrecorder_reset_all_calls fails, the on_umock_c_error callback shall be triggered with UMOCK_C_RESET_CALLS_ERROR. ]*/
TEST_FUNCTION(when_the_underlying_call_recorder_reset_all_calls_fails_then_umock_c_reset_all_calls_triggers_the_on_error_callback)
{
    // arrange
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    reset_all_calls();
    umockcallrecorder_reset_all_calls_result = 1;

    // act
    umock_c_reset_all_calls();

    // assert
    ASSERT_ARE_EQUAL(size_t, 2, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_reset_all_calls, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[0].u.umockcallrecorder_reset_all_calls.umock_call_recorder);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_test_on_umock_c_error, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(UMOCK_C_ERROR_CODE, UMOCK_C_RESET_CALLS_ERROR, mocked_calls[1].u.test_on_umock_c_error.error_code);
}

/* umock_c_get_actual_calls */

/* Tests_SRS_UMOCK_C_01_013: [ umock_c_get_actual_calls shall return the string for the recorded actual calls by calling umockcallrecorder_get_actual_calls on the call recorder created in umock_c_init. ]*/
TEST_FUNCTION(umock_c_get_actual_calls_calls_the_underlying_call_recorder_get_actual_calls)
{
    // arrange
    const char* result;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    reset_all_calls();
    umockcallrecorder_get_actual_calls_result = "[a()]";

    // act
    result = umock_c_get_actual_calls();

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "[a()]", result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_get_actual_calls, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[0].u.umockcallrecorder_get_actual_calls.umock_call_recorder);
}

/* Tests_SRS_UMOCK_C_01_013: [ umock_c_get_actual_calls shall return the string for the recorded actual calls by calling umockcallrecorder_get_actual_calls on the call recorder created in umock_c_init. ]*/
TEST_FUNCTION(when_the_underlying_call_recorder_get_actual_calls_fails_then_umock_c_get_actual_calls_returns_NULL)
{
    // arrange
    const char* result;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    reset_all_calls();
    umockcallrecorder_get_actual_calls_result = NULL;

    // act
    result = umock_c_get_actual_calls();

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_get_actual_calls, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[0].u.umockcallrecorder_get_actual_calls.umock_call_recorder);
}

/* Tests_SRS_UMOCK_C_01_014: [ If the module is not initialized, umock_c_get_actual_calls shall return NULL. ]*/
TEST_FUNCTION(umock_c_get_actual_calls_when_the_module_is_not_initialized_fails)
{
    // arrange

    // act
    const char* result = umock_c_get_actual_calls();

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);
}

/* umock_c_get_expected_calls */

/* Tests_SRS_UMOCK_C_01_015: [ umock_c_get_expected_calls shall return the string for the recorded expected calls by calling umockcallrecorder_get_expected_calls on the call recorder created in umock_c_init. ]*/
TEST_FUNCTION(umock_c_get_expected_calls_calls_the_underlying_call_recorder_get_expected_calls)
{
    // arrange
    const char* result;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    reset_all_calls();
    umockcallrecorder_get_expected_calls_result = "[a()]";

    // act
    result = umock_c_get_expected_calls();

    // assert
    ASSERT_ARE_EQUAL(char_ptr, "[a()]", result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_get_expected_calls, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[0].u.umockcallrecorder_get_expected_calls.umock_call_recorder);
}

/* Tests_SRS_UMOCK_C_01_015: [ umock_c_get_expected_calls shall return the string for the recorded expected calls by calling umockcallrecorder_get_expected_calls on the call recorder created in umock_c_init. ]*/
TEST_FUNCTION(when_the_underlying_call_recorder_get_expected_calls_fails_then_umock_c_get_expected_calls_returns_NULL)
{
    // arrange
    const char* result;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    reset_all_calls();
    umockcallrecorder_get_expected_calls_result = NULL;

    // act
    result = umock_c_get_expected_calls();

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_get_expected_calls, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[0].u.umockcallrecorder_get_expected_calls.umock_call_recorder);
}

/* Tests_SRS_UMOCK_C_01_016: [ If the module is not initialized, umock_c_get_expected_calls shall return NULL. ]*/
TEST_FUNCTION(umock_c_get_expected_calls_when_the_module_is_not_initialized_fails)
{
    // arrange

    // act
    const char* result = umock_c_get_expected_calls();

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);
}

/* umock_c_get_last_expected_call */

/* Tests_SRS_UMOCK_C_01_017: [ umock_c_get_last_expected_call shall return the last expected call by calling umockcallrecorder_get_last_expected_call on the call recorder created in umock_c_init. ]*/
TEST_FUNCTION(umock_c_get_last_expected_call_calls_the_underlying_call_recorder_get_last_expected_call)
{
    // arrange
    UMOCKCALL_HANDLE result;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    reset_all_calls();
    umockcallrecorder_get_last_expected_call_result = test_expected_call;

    // act
    result = umock_c_get_last_expected_call();

    // assert
    ASSERT_ARE_EQUAL(void_ptr, test_expected_call, result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_get_last_expected_call, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[0].u.umockcallrecorder_get_last_expected_call.umock_call_recorder);
}

/* Tests_SRS_UMOCK_C_01_017: [ umock_c_get_last_expected_call shall return the last expected call by calling umockcallrecorder_get_last_expected_call on the call recorder created in umock_c_init. ]*/
TEST_FUNCTION(when_the_underlying_call_recorder_get_last_expected_call_fails_then_umock_c_get_last_expected_call_returns_NULL)
{
    // arrange
    UMOCKCALL_HANDLE result;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    reset_all_calls();
    umockcallrecorder_get_last_expected_call_result = NULL;

    // act
    result = umock_c_get_last_expected_call();

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_get_last_expected_call, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[0].u.umockcallrecorder_get_last_expected_call.umock_call_recorder);
}

/* Tests_SRS_UMOCK_C_01_018: [ If the module is not initialized, umock_c_get_last_expected_call shall return NULL. ]*/
TEST_FUNCTION(umock_c_get_last_expected_call_when_the_module_is_not_initialized_fails)
{
    // arrange

    // act
    UMOCKCALL_HANDLE result = umock_c_get_last_expected_call();

    // assert
    ASSERT_IS_NULL(result);
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);
}

/* umock_c_add_expected_call */

/* Tests_SRS_UMOCK_C_01_019: [ umock_c_add_expected_call shall add an expected call by calling umockcallrecorder_add_expected_call on the call recorder created in umock_c_init. ]*/
TEST_FUNCTION(umock_c_add_expected_call_calls_the_underlying_call_recorder_add_expected_call)
{
    // arrange
    int result;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    reset_all_calls();
    umockcallrecorder_add_expected_call_result = 0;

    // act
    result = umock_c_add_expected_call(test_expected_call);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_add_expected_call, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[0].u.umockcallrecorder_add_expected_call.umock_call_recorder);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_call, mocked_calls[0].u.umockcallrecorder_add_expected_call.mock_call);
}

/* Tests_SRS_UMOCK_C_01_019: [ umock_c_add_expected_call shall add an expected call by calling umockcallrecorder_add_expected_call on the call recorder created in umock_c_init. ]*/
TEST_FUNCTION(when_the_underlying_call_recorder_add_expected_call_fails_then_umock_c_add_expected_call_returns_NULL)
{
    // arrange
    int result;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    reset_all_calls();
    umockcallrecorder_add_expected_call_result = 1;

    // act
    result = umock_c_add_expected_call(test_expected_call);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_add_expected_call, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[0].u.umockcallrecorder_add_expected_call.umock_call_recorder);
    ASSERT_ARE_EQUAL(void_ptr, test_expected_call, mocked_calls[0].u.umockcallrecorder_add_expected_call.mock_call);
}

/* Tests_SRS_UMOCK_C_01_020: [ If the module is not initialized, umock_c_add_expected_call shall return a non-zero value. ]*/
TEST_FUNCTION(umock_c_add_expected_call_when_the_module_is_not_initialized_fails)
{
    // arrange

    // act
    int result = umock_c_add_expected_call(test_expected_call);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);
}

/* umock_c_add_actual_call */

/* Tests_SRS_UMOCK_C_01_021: [ umock_c_add_actual_call shall add an actual call by calling umockcallrecorder_add_actual_call on the call recorder created in umock_c_init. ]*/
TEST_FUNCTION(umock_c_add_actual_call_calls_the_underlying_call_recorder_add_actual_call)
{
    // arrange
    int result;
    UMOCKCALL_HANDLE matched_call;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    reset_all_calls();
    umockcallrecorder_add_actual_call_result = 0;

    // act
    result = umock_c_add_actual_call(test_actual_call, &matched_call);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_add_actual_call, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[0].u.umockcallrecorder_add_actual_call.umock_call_recorder);
    ASSERT_ARE_EQUAL(void_ptr, test_actual_call, mocked_calls[0].u.umockcallrecorder_add_actual_call.mock_call);
    ASSERT_ARE_EQUAL(void_ptr, &matched_call, mocked_calls[0].u.umockcallrecorder_add_actual_call.matched_call);
}

/* Tests_SRS_UMOCK_C_01_021: [ umock_c_add_actual_call shall add an actual call by calling umockcallrecorder_add_actual_call on the call recorder created in umock_c_init. ]*/
TEST_FUNCTION(when_the_underlying_call_recorder_add_actual_call_fails_then_umock_c_add_actual_call_returns_NULL)
{
    // arrange
    int result;
    UMOCKCALL_HANDLE matched_call;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    reset_all_calls();
    umockcallrecorder_add_actual_call_result = 1;

    // act
    result = umock_c_add_actual_call(test_actual_call, &matched_call);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_add_actual_call, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[0].u.umockcallrecorder_add_actual_call.umock_call_recorder);
    ASSERT_ARE_EQUAL(void_ptr, test_actual_call, mocked_calls[0].u.umockcallrecorder_add_actual_call.mock_call);
    ASSERT_ARE_EQUAL(void_ptr, &matched_call, mocked_calls[0].u.umockcallrecorder_add_actual_call.matched_call);
}

/* Tests_SRS_UMOCK_C_01_022: [** If the module is not initialized, umock_c_add_actual_call shall return a non-zero value. ]*/
TEST_FUNCTION(umock_c_add_actual_call_when_the_module_is_not_initialized_fails)
{
    // arrange
    UMOCKCALL_HANDLE matched_call;

    // act
    int result = umock_c_add_actual_call(test_actual_call, &matched_call);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);
}

/* umock_c_get_call_recorder */

/* Tests_SRS_UMOCK_C_01_026: [ umock_c_get_call_recorder shall return the handle to the currently used call recorder. ]*/
TEST_FUNCTION(umock_c_get_call_recorder_returns_a_non_NULL_call_recorder)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    reset_all_calls();

    // act
    result = umock_c_get_call_recorder();

    // assert
    ASSERT_IS_NOT_NULL(result);
}

/* Tests_SRS_UMOCK_C_01_027: [ If the module is not initialized, umock_c_get_call_recorder shall return NULL. ]*/
TEST_FUNCTION(umock_c_get_call_recorder_when_not_initialized_fails)
{
    // arrange
    UMOCKCALLRECORDER_HANDLE result;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    umock_c_deinit();
    reset_all_calls();

    // act
    result = umock_c_get_call_recorder();

    // assert
    ASSERT_IS_NULL(result);
}

/* umock_c_set_call_recorder */

/* Tests_SRS_UMOCK_C_01_028: [ umock_c_set_call_recorder shall replace the currently used call recorder with the one identified by the call_recorder argument. ]*/
/* Tests_SRS_UMOCK_C_01_029: [ On success, umock_c_set_call_recorder shall return 0. ]*/
/* Tests_SRS_UMOCK_C_01_031: [ umock_c_set_call_recorder shall make a copy of call_recorder by calling umockcallrecorder_clone and use the copy for future actions. ]*/
/* Tests_SRS_UMOCK_C_01_034: [ The previously used call recorder shall be destroyed by calling umockcallrecorder_destroy. ]*/
TEST_FUNCTION(umock_c_set_call_recorder_replaces_the_recorder)
{
    // arrange
    int result;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    reset_all_calls();

    // act
    result = umock_c_set_call_recorder(test_call_recorder);

    // assert
    ASSERT_ARE_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 2, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_clone, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[0].u.umockcallrecorder_clone.umock_call_recorder);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_destroy, mocked_calls[1].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[1].u.umockcallrecorder_destroy.umock_call_recorder);
}

/* Tests_SRS_UMOCK_C_01_030: [ If call_recorder is NULL, umock_c_set_call_recorder shall return a non-zero value. ]*/
TEST_FUNCTION(umock_c_set_call_recorder_with_NULL_call_recorder_fails)
{
    // arrange
    int result;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    reset_all_calls();

    // act
    result = umock_c_set_call_recorder(NULL);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);
}

/* Tests_SRS_UMOCK_C_01_032: [ If umockcallrecorder_clone fails, umock_c_set_call_recorder shall return a non-zero value. ]*/
TEST_FUNCTION(when_cloning_the_call_recorder_fails_umock_c_set_call_recorder_fails)
{
    // arrange
    int result;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    reset_all_calls();
    umockcallrecorder_clone_result = NULL;

    // act
    result = umock_c_set_call_recorder(test_call_recorder);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 1, mocked_call_count);
    ASSERT_ARE_EQUAL(TEST_MOCK_CALL_TYPE, TEST_MOCK_CALL_TYPE_umockcallrecorder_clone, mocked_calls[0].call_type);
    ASSERT_ARE_EQUAL(void_ptr, test_call_recorder, mocked_calls[0].u.umockcallrecorder_clone.umock_call_recorder);
}

/* Tests_SRS_UMOCK_C_01_033: [ If the module is not initialized, umock_c_set_call_recorder shall return a non-zero value. ]*/
TEST_FUNCTION(when_the_module_is_not_initialize_umock_c_set_call_recorder_fails)
{
    // arrange
    int result;
    ASSERT_ARE_EQUAL(int, 0, umock_c_init(test_on_umock_c_error));
    umock_c_deinit();
    reset_all_calls();

    // act
    result = umock_c_set_call_recorder(test_call_recorder);

    // assert
    ASSERT_ARE_NOT_EQUAL(int, 0, result);
    ASSERT_ARE_EQUAL(size_t, 0, mocked_call_count);
}

END_TEST_SUITE(umock_c_unittests)
