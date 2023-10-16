// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#define GLIB_STRINGS
    #define GLIB_CONSOLE
#define GLIB_FILES
#define GLIB_PROCESS
#define GLIB_REPLACEABLE_VARS
//#define GLIB_SHUTDOWN_MONITOR

#ifdef GLIB_STRINGS
    #include "glib/strings.h"
    #ifdef GLIB_CONSOLE
        #include "glib/console.h"
    #endif
#endif
#ifdef GLIB_FILES
    #include "glib/files.h"
#endif
#ifdef GLIB_PROCESS
    #include "glib/process.h"
#endif
#ifdef GLIB_REPLACEABLE_VARS
    #include "glib/ReplaceableVars.h"
#endif
#ifdef GLIB_SHUTDOWN_MONITOR
    #include "glib/ShutdownMonitor.h"
#endif
