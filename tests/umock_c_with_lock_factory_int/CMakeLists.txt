#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

cmake_minimum_required(VERSION 2.8.11)

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
../../src/umock_c.c
../../src/umock_log.c
../../src/umockalloc.c
../../src/umockautoignoreargs.c
../../src/umockcall.c
../../src/umockcallrecorder.c
../../src/umockstring.c
../../src/umocktypes.c
../../src/umocktypes_charptr.c
../../src/umocktypes_c.c
../../src/umocktypename.c
${test_platform_c_files}
)

set(${theseTestsName}_h_files
./minipal/umock_threadapi.h
)

if(UNIX)
    build_test_artifacts(${theseTestsName} ON "tests/umockc_tests" ADDITIONAL_LIBS pthread)
else()
    build_test_artifacts(${theseTestsName} ON "tests/umockc_tests")
endif()
