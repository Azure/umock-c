#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

if(NOT DEFINED CMAKE_MINIMUM_REQUIRED_VERSION)
    cmake_minimum_required(VERSION 3.18)
endif()

# canon way of using umock-c from another repo is below. It assumes the using repo has placed umock-c in "deps"

#if ((NOT TARGET umock_c) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/umock-c/CMakeLists.txt))
#    add_subdirectory(deps/umock-c)
#endif()

if(TARGET umock_c)
    return()
endif()

option(run_unittests "set run_unittests to ON to run unittests (default is OFF)" OFF)
option(run_int_tests "set run_int_tests to ON to run the integration tests (default is OFF)" OFF)
option(run_perf_tests "set run_perf_tests to ON to build performance tests (default is OFF)." OFF)
option(run_reals_check "set run_reals_check to ON to run reals check (default is OFF)." OFF)
option(use_installed_dependencies "set use_installed_dependencies to ON to use installed packages instead of building dependencies from submodules" OFF)
option(use_cppunittest "set use_cppunittest to ON to build CppUnitTest tests on Windows (default is OFF)" OFF)

project(umock_c)

set(UMOCK_C_VERSION 1.1.19)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

#Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Build with -fPIC always
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)


include (CTest)
include (CheckIncludeFiles)

#bring in dependencies
#do not add or build any tests of the dependencies
set(original_run_e2e_tests ${run_e2e_tests})
set(original_run_int_tests ${run_int_tests})
set(original_run_perf_tests ${run_perf_tests})
set(original_run_unittests ${run_unittests})
set(original_run_traceability ${run_traceability})
set(original_run_reals_check ${run_reals_check})

set(run_e2e_tests OFF)
set(run_int_tests OFF)
set(run_perf_tests OFF)
set(run_unittests OFF)
set(run_traceability OFF)
set(run_reals_check OFF)

if ((NOT TARGET c_build_tools) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/c-build-tools/CMakeLists.txt))
    add_subdirectory(deps/c-build-tools)
    set_default_build_options()
endif()

if ((NOT TARGET macro_utils_c) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/macro-utils-c/CMakeLists.txt))
    add_subdirectory(deps/macro-utils-c)
endif()

if ((NOT TARGET c_logging) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/c-logging/CMakeLists.txt))
    add_subdirectory(deps/c-logging)
endif()

if ((NOT TARGET ctest) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/ctest/CMakeLists.txt))
    add_subdirectory(deps/ctest)
endif()

if ((NOT TARGET testrunnerswitcher) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/c-testrunnerswitcher/CMakeLists.txt))
    add_subdirectory(deps/c-testrunnerswitcher)
endif()

#this function takes as arguments a LIBRARY_NAME followed by a list of HEADER_FILES
#it builds a separate header file which includes all the HEADER_FILES under the ENABLE_MOCKS_DECL #define
#it builds a separate source file which is build under the ENABLE_MOCKS #define
#it adds the header file and the source file to a library called ${LIBRARY_NAME}_mocks
#it adds the headers as precompiles headers for the ${LIBRARY_NAME}_mocks library
function(add_mock_library LIBRARY_NAME)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs HEADER_FILES)
    cmake_parse_arguments(ARG "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    string(TOUPPER ${LIBRARY_NAME} LIBRARY_NAME_UPPER)

    set(MOCKS_HEADER_FILE ${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}_mocks.h)
    set(MOCKS_SOURCE_FILE ${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}_mocks.c)

    set(MOCKS_HEADER_CONTENT "// Copyright (c) Microsoft. All rights reserved.\n")
    set(MOCKS_HEADER_CONTENT "${MOCKS_HEADER_CONTENT}// Licensed under the MIT license. See LICENSE file in the project root for full license information.\n")
    set(MOCKS_HEADER_CONTENT "${MOCKS_HEADER_CONTENT}// THIS IS A GENERATED FILE, DO NOT EDIT. It was generated using function add_mock_library_2 from CMakeLists.txt in umock-c.\n\n")
    set(MOCKS_HEADER_CONTENT "${MOCKS_HEADER_CONTENT}#ifndef ${LIBRARY_NAME_UPPER}_MOCKS_H\n")
    set(MOCKS_HEADER_CONTENT "${MOCKS_HEADER_CONTENT}#define ${LIBRARY_NAME_UPPER}_MOCKS_H\n\n")

    set(MOCKS_HEADER_CONTENT "${MOCKS_HEADER_CONTENT}#define ENABLE_MOCKS\n")
    set(MOCKS_HEADER_CONTENT "${MOCKS_HEADER_CONTENT}#define ENABLE_MOCKS_DECL\n")

    foreach(HEADER_FILE ${ARG_HEADER_FILES})
        set(MOCKS_HEADER_CONTENT "${MOCKS_HEADER_CONTENT}#include \"${HEADER_FILE}\"\n")
    endforeach()

    set(MOCKS_HEADER_CONTENT "${MOCKS_HEADER_CONTENT}#undef ENABLE_MOCKS_DECL\n")
    set(MOCKS_HEADER_CONTENT "${MOCKS_HEADER_CONTENT}#undef ENABLE_MOCKS\n\n")

    set(MOCKS_HEADER_CONTENT "${MOCKS_HEADER_CONTENT}#endif // ${LIBRARY_NAME_UPPER}_MOCKS_H\n")

    file(WRITE ${MOCKS_HEADER_FILE} ${MOCKS_HEADER_CONTENT})

    set(MOCKS_SOURCE_CONTENT "// Copyright (c) Microsoft. All rights reserved.\n")
    set(MOCKS_SOURCE_CONTENT "${MOCKS_SOURCE_CONTENT}// Licensed under the MIT license. See LICENSE file in the project root for full license information.\n")
    set(MOCKS_SOURCE_CONTENT "${MOCKS_SOURCE_CONTENT}// THIS IS A GENERATED FILE, DO NOT EDIT. It was generated using function add_mock_library_2 from CMakeLists.txt in umock-c.\n\n")
    set(MOCKS_SOURCE_CONTENT "${MOCKS_SOURCE_CONTENT}#define ENABLE_MOCKS\n")
    foreach(HEADER_FILE ${ARG_HEADER_FILES})
        set(MOCKS_SOURCE_CONTENT "${MOCKS_SOURCE_CONTENT}#include \"${HEADER_FILE}\"\n")
    endforeach()
    set(MOCKS_SOURCE_CONTENT "${MOCKS_SOURCE_CONTENT}#undef ENABLE_MOCKS\n")

    file(WRITE ${MOCKS_SOURCE_FILE} ${MOCKS_SOURCE_CONTENT})

    set_source_files_properties(${MOCKS_SOURCE_FILE} PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

    add_library(${LIBRARY_NAME}_mocks ${MOCKS_SOURCE_FILE} ${MOCKS_HEADER_FILE})
    target_include_directories(${LIBRARY_NAME}_mocks PUBLIC $<TARGET_PROPERTY:${LIBRARY_NAME},INTERFACE_INCLUDE_DIRECTORIES>)
    target_link_libraries(${LIBRARY_NAME}_mocks PUBLIC umock_c)

    target_precompile_headers(${LIBRARY_NAME}_mocks PUBLIC ${MOCKS_HEADER_FILE})
endfunction()

set(run_e2e_tests ${original_run_e2e_tests})
set(run_int_tests ${original_run_int_tests})
set(run_perf_tests ${original_run_perf_tests})
set(run_unittests ${original_run_unittests})
set(run_traceability ${original_run_traceability})
set(run_reals_check ${original_run_reals_check})

set(umock_c_c_files
    ./src/umock_c.c
    ./src/umock_c_negative_tests.c
    ./src/umockalloc.c
    ./src/umockautoignoreargs.c
    ./src/umockcall.c
    ./src/umockcallpairs.c
    ./src/umockcallrecorder.c
    ./src/umockstring.c
    ./src/umocktypename.c
    ./src/umocktypes.c
    ./src/umocktypes_bool.c
    ./src/umocktypes_c.c
    ./src/umocktypes_stdint.c
    ./src/umocktypes_charptr.c
    ./src/umocktypes_wcharptr.c
)

set(umock_c_h_files
    ./inc/umock_c/umock_c.h
    ./inc/umock_c/umock_c_internal.h
    ./inc/umock_c/umock_c_negative_tests.h
    ./inc/umock_c/umock_c_prod.h
    ./inc/umock_c/umock_lock_factory.h
    ./inc/umock_c/umock_lock_factory_default.h
    ./inc/umock_c/umock_lock_if.h
    ./inc/umock_c/umock_log.h
    ./inc/umock_c/umockalloc.h
    ./inc/umock_c/umockautoignoreargs.h
    ./inc/umock_c/umockcall.h
    ./inc/umock_c/umockcallpairs.h
    ./inc/umock_c/umockcallrecorder.h
    ./inc/umock_c/umockstring.h
    ./inc/umock_c/umocktypename.h
    ./inc/umock_c/umocktypes.h
    ./inc/umock_c/umocktypes_bool.h
    ./inc/umock_c/umocktypes_c.h
    ./inc/umock_c/umocktypes_stdint.h
    ./inc/umock_c/umocktypes_charptr.h
    ./inc/umock_c/umocktypes_struct.h
    ./inc/umock_c/umocktypes_wcharptr.h
)

if(WIN32)
set(umock_c_c_files ${umock_c_c_files}
    ./src/umocktypes_windows.c
    ./src/umock_lock_factory_windows.c
)

set(umock_c_h_files ${umock_c_h_files}
    ./inc/umock_c/umocktypes_windows.h
)
endif()

if(UNIX)
set(umock_c_c_files ${umock_c_c_files}
    ./src/umock_lock_factory_pthread.c
)
endif()

FILE(GLOB umock_c_md_files "devdoc/*.md")
SOURCE_GROUP(devdoc FILES ${umock_c_md_files})

add_library(umock_c ${umock_c_c_files} ${umock_c_h_files} ${umock_c_md_files})

target_link_libraries(umock_c c_logging_v2 macro_utils_c)

target_include_directories(umock_c
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(umock_c
               PROPERTIES
               FOLDER "test_tools")

CHECK_INCLUDE_FILES(stdint.h HAVE_STDINT_H)
CHECK_INCLUDE_FILES(stdbool.h HAVE_STDBOOL_H)

if (${run_unittests} OR ${run_int_tests})
    add_subdirectory(tests)
endif()

# make an install target so we can produce a Linux native client package.
# only the header files are required for the native client.
install_library_includes(umock_c umock_c ${umock_c_h_files})

if(${run_reals_check})
    add_reals_check_target()
endif()

#Insert vld in all executables if so required
add_vld_if_defined(${CMAKE_CURRENT_SOURCE_DIR})