#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

set(theseTestsName umock_c_2_int)

set(${theseTestsName}_test_files
    umock_c_2_int.c
)

set(${theseTestsName}_c_files
    test_dependency_mock.c

)

set(${theseTestsName}_h_files
    test_dependency.h
    test_dependency_mock.h
)

build_test_artifacts(${theseTestsName} "tests/umockc_tests" umock_c)



if(NOT ${build_yet})


    set(${theseTestsName}_pp_files
        test_dependency_mock_pp_c1.c
        test_dependency_mock_pp_h2.c
    )

    set(build_yet TRUE PARENT_SCOPE)

    #get_target_property(INCLUDE_DIRS umock_c_int_lib_umock_c INCLUDE_DIRECTORIES)

    #Create a string with all include directories
    set(INCLUDE_FLAGS "")
    foreach(dir ${INCLUDE_DIRS})
        set(INCLUDE_FLAGS "/I\"${dir}\" ${INCLUDE_FLAGS}")
    endforeach()

    #MESSAGE("include is ${INCLUDE_FLAGS}")

    SET(SOURCE_FILE test_dependency_mock_pp_c1.c)
    SET(PP_FILE     test_dependency_mock_pp_c1_pp.c)

    # Preprocess the source file
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PP_FILE}
        COMMAND ${CMAKE_C_COMPILER} /P /C /EP /std:c17 /Zc:preprocessor ${INCLUDE_FLAGS} ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FILE} /Fi"${CMAKE_CURRENT_BINARY_DIR}/${PP_FILE}"
        COMMAND clang-format -i "${CMAKE_CURRENT_BINARY_DIR}/${PP_FILE}"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FILE}
        COMMENT "Preprocessing ${CMAKE_CURRENT_BINARY_DIR}/${PP_FILE} from  ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FILE} with include directories from umock_c_2_int_lib_umock_c"
    )

    SET(SOURCE_FILE_2 test_dependency_mock_pp_h2.c)
    SET(PP_FILE_2     test_dependency_mock_pp_h2_pp.c)

    # Preprocess the source file
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PP_FILE_2}
        COMMAND ${CMAKE_C_COMPILER} /P /C /EP /std:c17 /Zc:preprocessor ${INCLUDE_FLAGS} ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FILE_2} /Fi"${CMAKE_CURRENT_BINARY_DIR}/${PP_FILE_2}"
        COMMAND clang-format -i "${CMAKE_CURRENT_BINARY_DIR}/${PP_FILE_2}"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FILE_2}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/umock_c/umock_c_internal.h
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/umock_c/umock_c_prod.h
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/umock_c/umock_c.h
        COMMENT "Preprocessing ${CMAKE_CURRENT_BINARY_DIR}/${PP_FILE_2} from  ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FILE_2} with include directories from umock_c_2_int_lib_umock_c"
    )

    # Add the preprocessed file to the library
    add_library(umock_c_2_mock_pp STATIC
        ${SOURCE_FILE}
        ${SOURCE_FILE_2}
        ${CMAKE_CURRENT_BINARY_DIR}/${PP_FILE}
        ${CMAKE_CURRENT_BINARY_DIR}/${PP_FILE_2}
    )

    set_target_properties(umock_c_2_mock_pp
        PROPERTIES
            FOLDER "tests/umockc_tests"
    )

    #target_sources(umock_c_2_mock_pp
    #    PRIVATE
    #
    #)

    set_source_files_properties(${SOURCE_FILE} PROPERTIES HEADER_FILE_ONLY TRUE)
    set_source_files_properties(${SOURCE_FILE_2} PROPERTIES HEADER_FILE_ONLY TRUE)
endif()
