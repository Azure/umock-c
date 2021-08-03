#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

if(NOT DEFINED CMAKE_MINIMUM_REQUIRED_VERSION)
    cmake_minimum_required(VERSION 3.18)
endif()

# canon way of using umock-c from another repo is below. It assumes the using repo has placed umock-c in "deps"

#if ((NOT TARGET umock_c) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/umock-c/CMakeLists.txt))
#    add_subdirectory(deps/umock-c)
#    include_directories(${UMOCK_C_INC_FOLDER})
#endif() 

if(TARGET umock_c)
    return()
endif()

option(run_unittests "set run_unittests to ON to run unittests (default is OFF)" OFF)
option(run_int_tests "set run_int_tests to ON to run the integration tests (default is OFF)" OFF)
option(run_perf_tests "set run_perf_tests to ON to build performance tests (default is OFF)." OFF)
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

set(run_e2e_tests OFF)
set(run_int_tests OFF)
set(run_perf_tests OFF)
set(run_unittests OFF)
set(run_traceability OFF)

if ((NOT TARGET c_build_tools) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/c-build-tools/CMakeLists.txt))
    add_subdirectory(deps/c-build-tools)
    set_default_build_options()
endif() 

if ((NOT TARGET macro_utils_c) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/macro-utils-c/CMakeLists.txt))
    add_subdirectory(deps/macro-utils-c)
    include_directories(${MACRO_UTILS_INC_FOLDER})
endif() 

if ((NOT TARGET c_logging) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/c-logging/CMakeLists.txt))
    add_subdirectory(deps/c-logging)
    include_directories(deps/c-logging/inc)
endif() 

if ((NOT TARGET ctest) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/ctest/CMakeLists.txt))
    add_subdirectory(deps/ctest)
    include_directories(${CTEST_INC_FOLDER})
endif() 

if ((NOT TARGET testrunnerswitcher) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/deps/c-testrunnerswitcher/CMakeLists.txt))
    add_subdirectory(deps/c-testrunnerswitcher)
    include_directories(${TESTRUNNERSWITCHER_INC_FOLDER})
endif() 

set(run_e2e_tests ${original_run_e2e_tests})
set(run_int_tests ${original_run_int_tests})
set(run_perf_tests ${original_run_perf_tests})
set(run_unittests ${original_run_unittests})
set(run_traceability ${original_run_traceability})

set(umock_c_c_files
    ./src/umock_c.c
    ./src/umock_c_negative_tests.c
    ./src/umock_log.c
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

target_link_libraries(umock_c macro_utils_c)

target_include_directories(umock_c
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(umock_c
               PROPERTIES
               FOLDER "test_tools")

#these are the include folders
#the following "set" statetement exports across the project a global variable called UMOCK_C_INC_FOLDER that expands to whatever needs to included when using umock_c library
set(UMOCK_C_INC_FOLDER ${CMAKE_CURRENT_LIST_DIR}/inc CACHE INTERNAL "this is what needs to be included if using umock_c lib" FORCE)

include_directories(${UMOCK_C_INC_FOLDER} ${SHARED_UTIL_INC_FOLDER})

CHECK_INCLUDE_FILES(stdint.h HAVE_STDINT_H)
CHECK_INCLUDE_FILES(stdbool.h HAVE_STDBOOL_H)

if ((NOT HAVE_STDINT_H) OR (NOT HAVE_STDBOOL_H))
    include_directories(${UMOCK_C_INC_FOLDER}/umock_c/aux_inc)
endif()

if (${run_unittests} OR ${run_int_tests})
    add_subdirectory(tests)
endif()

# Set CMAKE_INSTALL_* if not defined
include(GNUInstallDirs)

if(NOT DEFINED CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR "lib")
endif()

# Install UMock C
set(package_location "cmake")

install(TARGETS umock_c EXPORT umock_cTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}/../bin
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES ${umock_c_h_files} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/umock_c)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${UMOCK_C_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_file("configs/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake"
    COPYONLY
)

install(EXPORT umock_cTargets
    FILE
        "${PROJECT_NAME}Targets.cmake"
    DESTINATION
        ${package_location}
)

install(
    FILES
        "configs/${PROJECT_NAME}Functions.cmake"
        "configs/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION
        ${package_location}
)

