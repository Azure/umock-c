// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

/*
 * Enables umock_c mocks and immediately refreshes the production macros.
 * Include this instead of manually defining ENABLE_MOCKS.
 */
#if defined(ENABLE_MOCKS)
#error "umock_c_ENABLE_MOCKS.h included while ENABLE_MOCKS is already defined"
#endif

#define ENABLE_MOCKS

#include "umock_c/umock_c_prod.h"

