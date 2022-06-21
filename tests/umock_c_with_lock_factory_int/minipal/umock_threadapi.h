// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UMOCK_THREADAPI_H
#define UMOCK_THREADAPI_H

#include "macro_utils/macro_utils.h"


typedef int(*UMOCK_THREAD_START_FUNC)(void *);

#define UMOCK_THREADAPI_RESULT_VALUES \
    UMOCK_THREADAPI_OK,               \
    UMOCK_THREADAPI_INVALID_ARG,      \
    UMOCK_THREADAPI_NO_MEMORY,        \
    UMOCK_THREADAPI_ERROR

MU_DEFINE_ENUM(UMOCK_THREADAPI_RESULT, UMOCK_THREADAPI_RESULT_VALUES);

typedef void* UMOCK_THREAD_HANDLE;

UMOCK_THREADAPI_RESULT umock_threadapi_create(UMOCK_THREAD_HANDLE* thread_handle, UMOCK_THREAD_START_FUNC func, void* arg);
UMOCK_THREADAPI_RESULT umock_threadapi_join(UMOCK_THREAD_HANDLE thread_handle, int* res);
void umock_threadapi_sleep(unsigned int milliseconds);


#endif /* UMOCK_THREADAPI_H */
