// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include "glib/console.h"

namespace glib::console {

    std::string coloredText(const std::string& str, const color_t color) noexcept {
        const std::string startColor = glib::ReplaceableVars()
                .addIntegral("code", color)
                .replace(csiColorForeground);
        std::ostringstream ss;
        ss << startColor << str << csiColorReset;
        return ss.str();
    }
}
