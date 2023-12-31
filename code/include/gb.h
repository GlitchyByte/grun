// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cstdint>

#define GB_STRINGS
    #define GB_CONSOLE
//#define GB_FILES
#define GB_PROCESS
#define GB_REPLACEABLE_VARS
//#define GB_SHUTDOWN_MONITOR

#ifdef GB_STRINGS
    #include "gb/strings.h"
    #ifdef GB_CONSOLE
        #include "gb/console.h"
    #endif
#endif
#ifdef GB_FILES
    #include "gb/files.h"
#endif
#ifdef GB_PROCESS
    #include "gb/process.h"
#endif
#ifdef GB_REPLACEABLE_VARS
    #include "gb/ReplaceableVars.h"
#endif
#ifdef GB_SHUTDOWN_MONITOR
    #include "gb/ShutdownMonitor.h"
#endif
