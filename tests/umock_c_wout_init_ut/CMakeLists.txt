#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

set(theseTestsName umock_c_wout_init_ut)

set(${theseTestsName}_test_files
umock_c_wout_init_ut.c
)

set(${theseTestsName}_c_files
../../src/umock_c.c
)

build_test_artifacts(${theseTestsName} "tests/umockc_tests")
