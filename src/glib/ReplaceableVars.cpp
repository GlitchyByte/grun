// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include <sstream>
#include "glib/ReplaceableVars.h"

namespace glib {

    ReplaceableVars::ReplaceableVars(const ReplaceableVars& other) noexcept {
        vars = other.vars;
    }

    ReplaceableVars::ReplaceableVars(ReplaceableVars&& other) noexcept {
        vars = std::move(other.vars);
    }

    ReplaceableVars& ReplaceableVars::operator=(const ReplaceableVars& other) noexcept {
        if (this != &other) {
            vars = other.vars;
        }
        return *this;
    }

    ReplaceableVars& ReplaceableVars::operator=(ReplaceableVars&& other) noexcept {
        if (this != &other) {
            vars = std::move(other.vars);
        }
        return *this;
    }

    ReplaceableVars& ReplaceableVars::add(const std::string& name, const std::string& value) noexcept {
        const std::string decoratedName = "${" + name + "}";
        vars[decoratedName] = value;
        return *this;
    }

    std::string ReplaceableVars::replace(const std::string_view& str) const noexcept {
        std::string replaced { str };
        for (const auto& entries: vars) {
            const std::string& name { entries.first };
            const std::string& value { entries.second };
            size_t pos { replaced.find(name) };
            while (pos != std::string::npos) {
                replaced.replace(pos, name.length(), value);
                pos = replaced.find(name, pos + value.length());
            }
        }
        return replaced;
    }

    std::string ReplaceableVars::string() const noexcept {
        std::ostringstream ss;
        ss << "{ ";
        bool first = true;
        for (const auto& entries: vars) {
            if (first) {
                first = false;
            } else {
                ss << ", ";
            }
            ss << entries.first << ": " << entries.second;
        }
        ss << " }";
        return ss.str();
    }
}
