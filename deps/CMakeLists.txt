#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

cmake_minimum_required(VERSION 2.8.11)

#do not add or build any tests of the dependencies
set(original_run_int_tests ${run_int_tests})
set(original_run_unittests ${run_unittests})

set(run_int_tests OFF)
set(run_unittests OFF)

if ((NOT TARGET azure_macro_utils_c) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/azure-macro-utils-c/CMakeLists.txt))
        add_subdirectory(azure-macro-utils-c)
endif()

if (${original_run_unittests} OR ${original_run_int_tests})
        if ((NOT TARGET ctest) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/ctest/CMakeLists.txt))
  		add_subdirectory(ctest)
        endif()
        if ((NOT TARGET testrunnerswitcher) AND (EXISTS ${CMAKE_CURRENT_LIST_DIR}/testrunner/CMakeLists.txt))
		add_subdirectory(testrunner)
        endif()
endif()

set(run_int_tests ${original_run_int_tests})
set(run_unittests ${original_run_unittests})
