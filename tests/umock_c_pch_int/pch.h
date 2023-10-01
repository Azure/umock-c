// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef PCH_H
#define PCH_H

#include "testrunnerswitcher.h"

#include "umock_c/umock_c.h"

#define ENABLE_MOCKS
#include "unit_b.h"
#undef ENABLE_MOCKS

#endif // PCH_H
