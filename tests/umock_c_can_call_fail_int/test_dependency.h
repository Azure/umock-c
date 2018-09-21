// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef TEST_DEPENDENCY_H
#define TEST_DEPENDENCY_H

#include "umock_c_prod.h"

#ifdef __cplusplus
extern "C" {
#endif

    MOCKABLE_FUNCTION(, void, void_function_no_args);
    MOCKABLE_FUNCTION(, void, void_function_with_args, int, x);
    
    MOCKABLE_FUNCTION(, int, function_default_no_args);
    MOCKABLE_FUNCTION(, int, function_default_with_args, int, x);

    MOCKABLE_FUNCTION(, int, function_mark_cannot_fail_no_args);
    MOCKABLE_FUNCTION(, int, function_mark_cannot_fail_with_args, int, x);


#ifdef __cplusplus
}
#endif

#endif /* TEST_DEPENDENCY_H */
