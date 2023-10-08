// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include "glib/gcollections.h"

namespace glib::collections {

    std::vector<std::string> createVectorFromCArray(const int argc, const char* argv[]) {
        std::vector<std::string> args(argc);
        for (unsigned int i = 0; i < argc; ++i) {
            const std::string arg(argv[i]);
            args[i] = arg;
        }
        return args;
    }
}
