// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UMOCK_C_V2_H
#define UMOCK_C_V2_H

#include "macro_utils/macro_utils.h"

#define UMOCK_C_ERROR_CODE_VALUES \
        UMOCK_C_ARG_INDEX_OUT_OF_RANGE, \
        UMOCK_C_MALLOC_ERROR, \
        UMOCK_C_INVALID_ARGUMENT_BUFFER, \
        UMOCK_C_COMPARE_CALL_ERROR, \
        UMOCK_C_RESET_CALLS_ERROR, \
        UMOCK_C_CAPTURE_RETURN_ALREADY_USED, \
        UMOCK_C_NULL_ARGUMENT, \
        UMOCK_C_INVALID_PAIRED_CALLS, \
        UMOCK_C_REGISTER_TYPE_FAILED, \
        UMOCK_C_ERROR

MU_DEFINE_ENUM(UMOCK_C_ERROR_CODE, UMOCK_C_ERROR_CODE_VALUES);

#define MOCKABLE_FUNCTION_SIGNATURE(modifiers, result, function, ...) \
    result modifiers function(MU_IF(MU_COUNT_ARG(__VA_ARGS__),,void) MU_FOR_EACH_2_COUNTED(UMOCK_C_PROD_ARG_IN_SIGNATURE, __VA_ARGS__))

#define DECLARE_MOCKABLE_FUNCTION(modifiers, result, function, ...) \
    MOCKABLE_FUNCTION_SIGNATURE(modifiers, result, function, __VA_ARGS__); \
    MOCKABLE_FUNCTION_SIGNATURE(modifiers, result, MU_C2(umock_c_strict_expected_, function), __VA_ARGS__);

#define DEFINE_MOCKABLE_FUNCTION(modifiers, result, function, ...) \
    MOCKABLE_FUNCTION_SIGNATURE(modifiers, result, function, __VA_ARGS__) \
    { \
    } \
    MOCKABLE_FUNCTION_SIGNATURE(modifiers, result, MU_C2(umock_c_strict_expected_, function), __VA_ARGS__) \
    { \
    }

#define MOCKABLE_FUNCTION(modifiers, result, function, ...) \
    DECLARE_MOCKABLE_FUNCTION(modifiers, result, function, __VA_ARGS__)

/* This is the type for the error callback by which umock_c shall indicate errors to the user */
typedef void(*ON_UMOCK_C_ERROR)(UMOCK_C_ERROR_CODE error_code);

int umock_c_init(ON_UMOCK_C_ERROR on_umock_c_error);
void umock_c_deinit(void);
void umock_c_reset_all_calls(void);

#define STRICT_EXPECTED_CALL(call) \
    MU_C2(umock_c_strict_expected_,call)

#endif // UMOCK_C_V2_H
