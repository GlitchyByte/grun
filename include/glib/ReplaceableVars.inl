// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <sstream>
#include <iomanip>

namespace glib {

    template <std::integral T>
    ReplaceableVars& ReplaceableVars::addIntegral(const std::string& name, const T value, const bool humanReadable) noexcept {
        std::string str = std::to_string(value);
        if (humanReadable) {
            insertThousandSeparators(str);
        }
        return addString(name, str);
    }

    template <std::floating_point T>
    ReplaceableVars& ReplaceableVars::addFloatingPoint(const std::string& name, const T value, const int precision,
                                               const bool humanReadable) noexcept {
        std::ostringstream ss;
        if (precision != DefaultPrecision) {
            ss << std::fixed << std::setprecision(precision);
        }
        ss << value;
        if (humanReadable) {
            std::string str = ss.str();
            insertThousandSeparators(str);
            return addString(name, str);
        }
        return addString(name, ss.str());
    }
}
