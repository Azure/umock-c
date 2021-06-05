#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

set(theseTestsName umockalloc_ut)

set(${theseTestsName}_test_files
umockalloc_ut.c
)

set(${theseTestsName}_c_files
umockalloc_mocked.c
)

set(${theseTestsName}_h_files
)

build_test_artifacts(${theseTestsName} "tests/umockc_tests")
