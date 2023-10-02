#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

set(umock_c_v2_h_files
    ./inc/umock_c/umock_c_v2.h
    ./inc/umock_c/umock_c_v2_prod.h
    ./inc/umock_c/declare_mocks.h
    ./inc/umock_c/define_mocks.h
    ./inc/umock_c/no_mocks.h
    )

set(umock_c_v2_c_files
    ./src/umock_c_v2.c
    )

FILE(GLOB umock_c_v2_md_files "devdoc/*.md")
SOURCE_GROUP(devdoc FILES ${umock_c_v2_md_files})

add_library(umock_c_v2 ${umock_c_v2_c_files} ${umock_c_v2_h_files} ${umock_c_v2_md_files})

target_include_directories(umock_c_v2 PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/inc>)
include_directories(${CMAKE_CURRENT_LIST_DIR}/inc)

set_target_properties(umock_c_v2
               PROPERTIES
               FOLDER "test_tools")

if((CMAKE_GENERATOR MATCHES "Visual Studio") AND (${run_traceability}))
    #add traceability custom target
    add_custom_target(umock_c_v2_traceability ALL
        COMMAND traceabilitytool -buildcheck -e ${CMAKE_CURRENT_LIST_DIR}/deps -i ${CMAKE_CURRENT_LIST_DIR})
    add_dependencies(umock_c_v2_traceability traceabilitytool)
endif()

add_subdirectory(tests)

