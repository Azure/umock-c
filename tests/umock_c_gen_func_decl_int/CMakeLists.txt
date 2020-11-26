#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

cmake_minimum_required(VERSION 2.8.11)

set(theseTestsName umock_c_gen_func_decl_int)

set(${theseTestsName}_test_files
    umock_c_gen_func_decl_int.c
    umock_c_gen_func_multiple_inc.c
)

set(${theseTestsName}_c_files
)

set(${theseTestsName}_h_files
)

umockc_build_test_artifacts(${theseTestsName} ON umock_c)
