// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

/*
 * Disables umock_c mocks and immediately refreshes the production macros.
 * Include this instead of manually undefining ENABLE_MOCKS.
 */
#if !defined(ENABLE_MOCKS)
#error "umock_c_DISABLE_MOCKS.h included while ENABLE_MOCKS is not defined"
#endif

#undef ENABLE_MOCKS // force

#include "umock_c/umock_c_prod.h"

