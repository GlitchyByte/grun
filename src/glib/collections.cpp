// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include "glib/collections.h"

namespace glib::collections {

    std::vector<std::string_view> createVectorFromCArrayWeak(const int argc, const char* argv[]) noexcept {
        const size_t argsSize = argc;
        std::vector<std::string_view> args { argsSize };
        for (size_t i = 0; i < argsSize; ++i) {
            args[i] = std::string_view { argv[i] };
        }
        return args;
    }

    std::vector<std::string> createVectorFromCArray(const int argc, const char* argv[]) noexcept {
        const size_t argsSize = argc;
        std::vector<std::string> args { argsSize };
        for (size_t i = 0; i < argsSize; ++i) {
            args[i] = std::string { argv[i] };
        }
        return args;
    }
}
