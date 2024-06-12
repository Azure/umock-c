// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef UMOCK_LOG_H
#define UMOCK_LOG_H

#include "c_logging/logger.h"
#include "c_logging/log_level.h"

#ifdef __cplusplus
extern "C" {
#endif

    #define UMOCK_LOG(format, ...) \
        LOGGER_LOG(LOG_LEVEL_ERROR, NULL, format, __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* UMOCK_LOG_H */
