#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

set(theseTestsName umocktypes_windows_ut)

set(${theseTestsName}_test_files
umocktypes_windows_ut.c
)

set(${theseTestsName}_c_files
umocktypes_windows_mocked.c
)

set(${theseTestsName}_h_files
)

umockc_build_test_artifacts(${theseTestsName} ON)
