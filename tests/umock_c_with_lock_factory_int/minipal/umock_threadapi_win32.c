// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stddef.h>

#include "windows.h"

#include "macro_utils/macro_utils.h"

#include "c_logging/xlogging.h"

#include "umock_threadapi.h"

MU_DEFINE_ENUM_STRINGS(UMOCK_THREADAPI_RESULT, UMOCK_THREADAPI_RESULT_VALUES);

UMOCK_THREADAPI_RESULT umock_threadapi_create(UMOCK_THREAD_HANDLE* thread_handle, UMOCK_THREAD_START_FUNC func, void* arg)
{
    UMOCK_THREADAPI_RESULT result;
    if ((thread_handle == NULL) ||
        (func == NULL))
    {
        result = UMOCK_THREADAPI_INVALID_ARG;
        LogError("(result = %" PRI_MU_ENUM ")", MU_ENUM_VALUE(UMOCK_THREADAPI_RESULT, result));
    }
    else
    {
        *thread_handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, arg, 0, NULL);
        if(*thread_handle == NULL)
        {
            result = (GetLastError() == ERROR_OUTOFMEMORY) ? UMOCK_THREADAPI_NO_MEMORY : UMOCK_THREADAPI_ERROR;

            LogError("(result = %" PRI_MU_ENUM ")", MU_ENUM_VALUE(UMOCK_THREADAPI_RESULT, result));
        }
        else
        {
            result = UMOCK_THREADAPI_OK;
        }
    }

    return result;
}

UMOCK_THREADAPI_RESULT umock_threadapi_join(UMOCK_THREAD_HANDLE thread_handle, int *res)
{
    UMOCK_THREADAPI_RESULT result = UMOCK_THREADAPI_OK;

    if (thread_handle == NULL)
    {
        result = UMOCK_THREADAPI_INVALID_ARG;
        LogError("(result = %" PRI_MU_ENUM ")", MU_ENUM_VALUE(UMOCK_THREADAPI_RESULT, result));
    }
    else
    {
        DWORD returnCode = WaitForSingleObject(thread_handle, INFINITE);

        if( returnCode != WAIT_OBJECT_0)
        {
            result = UMOCK_THREADAPI_ERROR;
            LogLastError("Error waiting for Single Object. Return Code: %lu. Error Code: %" PRI_MU_ENUM "", returnCode, MU_ENUM_VALUE(UMOCK_THREADAPI_RESULT, result));
        }
        else
        {
            if (res != NULL)
            {
                DWORD exit_code;
                if (!GetExitCodeThread(thread_handle, &exit_code)) //If thread end is signaled we need to get the Thread Exit Code;
                {
                    result = UMOCK_THREADAPI_ERROR;
                    LogError("Error Getting Exit Code. Error Code: %u.", (unsigned int)GetLastError());
                }
                else
                {
                    *res = (int)exit_code;
                }
            }
        }
        CloseHandle(thread_handle);
    }

    return result;
}

void umock_threadapi_sleep(unsigned int milliseconds)
{
    Sleep(milliseconds);
}
