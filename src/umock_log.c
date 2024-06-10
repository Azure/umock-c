
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>
#include <stdarg.h>

#include "macro_utils/macro_utils.h"

#include "c_logging/logger.h"
#include "c_logging/log_level.h"

#include "umock_c/umock_log.h"
#include "umock_c/umock_c.h"

void UMOCK_LOG(const char* format, ...)
{
    va_list params;
    va_start(params, format);
    LOGGER_LOG(LOG_LEVEL_ERROR, NULL, format, params);
    va_end(params);
    umock_c_indicate_error(UMOCK_C_ERROR);
}
