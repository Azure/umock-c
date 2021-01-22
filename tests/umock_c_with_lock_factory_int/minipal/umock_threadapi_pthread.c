// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#define _DEFAULT_SOURCE

#include "macro_utils/macro_utils.h"

#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

#include <pthread.h>
#include <time.h>
#include "c_logging/xlogging.h"

#include "umock_threadapi.h"


MU_DEFINE_ENUM_STRINGS(UMOCK_THREADAPI_RESULT, UMOCK_THREADAPI_RESULT_VALUES);

typedef struct THREAD_INSTANCE_TAG
{
    pthread_t Pthread_handle;
    UMOCK_THREAD_START_FUNC ThreadStartFunc;
    void* Arg;
} THREAD_INSTANCE;

static void* ThreadWrapper(void* threadInstanceArg)
{
    THREAD_INSTANCE* threadInstance = (THREAD_INSTANCE*)threadInstanceArg;
    int result = threadInstance->ThreadStartFunc(threadInstance->Arg);
    return (void*)(intptr_t)result;
}

UMOCK_THREADAPI_RESULT umock_threadapi_create(UMOCK_THREAD_HANDLE* threadHandle, UMOCK_THREAD_START_FUNC func, void* arg)
{
    UMOCK_THREADAPI_RESULT result;

    if ((threadHandle == NULL) ||
        (func == NULL))
    {
        result = UMOCK_THREADAPI_INVALID_ARG;
        LogError("(result = %" PRI_MU_ENUM ")", MU_ENUM_VALUE(UMOCK_THREADAPI_RESULT, result));
    }
    else
    {
        THREAD_INSTANCE* threadInstance = malloc(sizeof(THREAD_INSTANCE));
        if (threadInstance == NULL)
        {
            result = UMOCK_THREADAPI_NO_MEMORY;
            LogError("(result = %" PRI_MU_ENUM ")", MU_ENUM_VALUE(UMOCK_THREADAPI_RESULT, result));
        }
        else
        {
            threadInstance->ThreadStartFunc = func;
            threadInstance->Arg = arg;
            int createResult = pthread_create(&threadInstance->Pthread_handle, NULL, ThreadWrapper, threadInstance);
            switch (createResult)
            {
            default:
                free(threadInstance);

                result = UMOCK_THREADAPI_ERROR;
                LogError("(result = %" PRI_MU_ENUM ")", MU_ENUM_VALUE(UMOCK_THREADAPI_RESULT, result));
                break;

            case 0:
                *threadHandle = threadInstance;
                result = UMOCK_THREADAPI_OK;
                break;

            case EAGAIN:
                free(threadInstance);

                result = UMOCK_THREADAPI_NO_MEMORY;
                LogError("(result = %" PRI_MU_ENUM ")", MU_ENUM_VALUE(UMOCK_THREADAPI_RESULT, result));
                break;
            }
        }
    }

    return result;
}

UMOCK_THREADAPI_RESULT umock_threadapi_join(UMOCK_THREAD_HANDLE threadHandle, int* res)
{
    UMOCK_THREADAPI_RESULT result;

    THREAD_INSTANCE* threadInstance = (THREAD_INSTANCE*)threadHandle;
    if (threadInstance == NULL)
    {
        result = UMOCK_THREADAPI_INVALID_ARG;
        LogError("(result = %" PRI_MU_ENUM ")", MU_ENUM_VALUE(UMOCK_THREADAPI_RESULT, result));
    }
    else
    {
        void* threadResult;
        if (pthread_join(threadInstance->Pthread_handle, &threadResult) != 0)
        {
            result = UMOCK_THREADAPI_ERROR;
            LogError("(result = %" PRI_MU_ENUM ")", MU_ENUM_VALUE(UMOCK_THREADAPI_RESULT, result));
        }
        else
        {
            if (res != NULL)
            {
                *res = (int)(intptr_t)threadResult;
            }

            result = UMOCK_THREADAPI_OK;
        }

        free(threadInstance);
    }

    return result;
}

void umock_threadapi_sleep(unsigned int milliseconds)
{
    time_t seconds = milliseconds / 1000;
    long nsRemainder = (milliseconds % 1000) * 1000000;
    struct timespec timeToSleep = { seconds, nsRemainder };
    (void)nanosleep(&timeToSleep, NULL);
}
