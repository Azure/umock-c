#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

set(theseTestsName umock_c_windows_types_int)

set(${theseTestsName}_test_files
    umock_c_windows_types_int.c
)

set(${theseTestsName}_c_files
)

set(${theseTestsName}_h_files
    test_dependency.h
)

build_test_artifacts(${theseTestsName} "tests/umockc_tests" umock_c)
