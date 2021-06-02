#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

set(theseTestsName umock_lock_factory_windows_ut)

set(${theseTestsName}_test_files
umock_lock_factory_windows_ut.c
)

set(${theseTestsName}_c_files
umock_lock_factory_windows_mocked.c
../../src/
)

set(${theseTestsName}_h_files
)

umockc_build_test_artifacts(${theseTestsName})
