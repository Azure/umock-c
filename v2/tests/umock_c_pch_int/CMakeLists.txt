#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

set(theseTestsName umock_c_pch_int)

set(${theseTestsName}_test_files
    umock_c_pch_int.c
)

set(${theseTestsName}_c_files
    unit_b_umock.c
    unit_a.c
)

set(${theseTestsName}_h_files
    unit_a.h
    unit_b.h
)

#set_source_files_properties(pch.c PROPERTIES COMPILE_OPTIONS "/Ycpch.h")
#set_source_files_properties(umock_c_pch_int.c PROPERTIES COMPILE_OPTIONS "/Yupch.h")

build_test_artifacts(${theseTestsName} "tests/umockc_tests" umock_c_v2)
