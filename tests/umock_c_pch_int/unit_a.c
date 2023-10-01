// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "unit_a.h"
#include "unit_b.h"

void unit_a_that_calls_unit_b(void)
{
    unit_b_do_something();
}
