// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "umock_c/umock_c_v2.h"

#undef MOCKABLE_FUNCTION

#define MOCKABLE_FUNCTION(modifiers, result, function, ...) \
    DEFINE_MOCKABLE_FUNCTION(modifiers, result, function, __VA_ARGS__)
