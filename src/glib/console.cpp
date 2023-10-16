// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include <cassert>
#include <sstream>
#include "glib/console.h"
#include "glib/strings.h"

namespace glib::console {

    color_t rgb(const color_t r, const color_t g, const color_t b) noexcept {
        assert(r < 6);
        assert(g < 6);
        assert(b < 6);
        return 16 + (36 * r) + (6 * g) + b;
    }

    color_t grey(const color_t step) noexcept {
        assert(step < 24);
        return 232 + step;
    }

    std::string colorText(const std::string_view& str, const color_t color) noexcept {
        if (str.empty()) {
            return "";
        }
        const auto startColor { glib::strings::replace(CSI_COLOR_FOREGROUND, CODE, std::to_string(color)) };
        std::ostringstream ss;
        ss << startColor << str << CSI_COLOR_RESET;
        return ss.str();
    }
}
