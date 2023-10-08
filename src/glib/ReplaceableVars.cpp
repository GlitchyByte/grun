// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include <sstream>
#include "glib/ReplaceableVars.h"

namespace glib {

    void ReplaceableVars::insertThousandSeparators(std::string& str) noexcept {
        const size_t period = str.find('.');
        const size_t start = period == std::string::npos ? str.length() : period;
        const size_t finish = str.starts_with('-') ? 4 : 3;
        size_t index = start;
        while (index > finish) {
            index -= 3;
            str.insert(index, ",");
        }
    }

    ReplaceableVars& ReplaceableVars::addString(const std::string& name, const std::string& value) noexcept {
        const std::string decoratedName = "${" + name + "}";
        vars[decoratedName] = value;
        return *this;
    }

    std::string ReplaceableVars::replace(const std::string& str) noexcept {
        std::string replaced = str;
        for (const auto& entries: vars) {
            const std::string& name = entries.first;
            const std::string& value = entries.second;
            size_t pos = replaced.find(name);
            while (pos != std::string::npos) {
                replaced.replace(pos, name.length(), value);
                pos = replaced.find(name, pos + value.length());
            }
        }
        return replaced;
    }
}
