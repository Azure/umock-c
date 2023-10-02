#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

#unit tests
if(${run_unittests})
endif()

#int tests
if(${run_int_tests})
    if((WIN32) OR (UNIX))
        build_test_folder(umock_c_pch_int)
    endif()
endif()