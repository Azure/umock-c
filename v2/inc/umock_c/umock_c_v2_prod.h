// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UMOCK_C_V2_PROD_H
#define UMOCK_C_V2_PROD_H

#include "macro_utils/macro_utils.h"

#ifndef MOCKABLE_FUNCTION
#define MOCKABLE_FUNCTION_SIGNATURE(modifiers, result, function, ...) \
    result modifiers function(MU_IF(MU_COUNT_ARG(__VA_ARGS__),,void) MU_FOR_EACH_2_COUNTED(UMOCK_C_PROD_ARG_IN_SIGNATURE, __VA_ARGS__))

#define MOCKABLE_FUNCTION(modifiers, result, function, ...) \
    MOCKABLE_FUNCTION_SIGNATURE(modifiers, result, function, __VA_ARGS__)
#endif

#endif // UMOCK_C_V2_PROD_H
