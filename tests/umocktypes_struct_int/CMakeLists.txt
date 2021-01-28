#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

set(theseTestsName umocktypes_struct_int)

set(${theseTestsName}_test_files
    umocktypes_struct_int.c
)

set(${theseTestsName}_c_files
)

set(${theseTestsName}_h_files
)

umockc_build_test_artifacts(${theseTestsName} ON umock_c)
