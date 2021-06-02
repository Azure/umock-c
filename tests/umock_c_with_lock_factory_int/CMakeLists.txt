#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

set(theseTestsName umock_c_with_lock_factory_int)

set(${theseTestsName}_test_files
    umock_c_with_lock_factory_int.c
)

if(WIN32)
# For Windows use CreateThread et all
set(test_platform_c_files
    ./minipal/umock_threadapi_win32.c
    ../../src/umock_lock_factory_windows.c
)
else()
# For others assume pthreads (this should be a real check for pthreads)
set(test_platform_c_files
    ./minipal/umock_threadapi_pthread.c
    ../../src/umock_lock_factory_pthread.c
)
endif()

set(${theseTestsName}_c_files
    ${test_platform_c_files}
)

set(${theseTestsName}_h_files
    ./minipal/umock_threadapi.h
)

if(UNIX)
    build_test_artifacts(${theseTestsName} "tests/umockc_tests" ADDITIONAL_LIBS pthread)
else()
    build_test_artifacts(${theseTestsName} "tests/umockc_tests")
endif()
