#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

set(theseTestsName umock_lock_factory_pthread_ut)

set(${theseTestsName}_test_files
umock_lock_factory_pthread_ut.c
)

set(${theseTestsName}_c_files
umock_lock_factory_pthread_mocked.c
../../src/
)

set(${theseTestsName}_h_files
)

umockc_build_test_artifacts(${theseTestsName} ON pthread)
