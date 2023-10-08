// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <sstream>

namespace glib::strings {

    template<typename T>
    std::string fromVector(const std::vector<T> &vector) {
        std::ostringstream ss;
        bool first = true;
        for (const T &item: vector) {
            if (first) {
                first = false;
            } else {
                ss << ", ";
            }
            ss << item;
        }
        return ss.str();
    }
}
