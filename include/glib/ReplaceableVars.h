// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <map>

namespace glib {

    /**
     * Class to hold variable names and their values for string replacement.
     */
    class ReplaceableVars {
    public:
        ReplaceableVars() noexcept = default;

        ReplaceableVars(const ReplaceableVars& other) noexcept;

        ReplaceableVars(ReplaceableVars&& other) noexcept;

        ReplaceableVars& operator=(const ReplaceableVars& other) noexcept;

        ReplaceableVars& operator=(ReplaceableVars&& other) noexcept;

        /**
         * Adds a string value.
         *
         * @param name Variable name.
         * @param value Value.
         * @return This object.
         */
        ReplaceableVars& add(const std::string& name, const std::string& value) noexcept;

        /**
         * Replace inline variables with values.
         *
         * @param str String with variables.
         * @return The replaced string.
         */
        [[nodiscard]]
        std::string replace(const std::string_view& str) const noexcept;

        /**
         * String representation.
         *
         * @return The string representation.
         */
        [[nodiscard]]
        std::string string() const noexcept;

    private:
        std::map<std::string, std::string> vars;
    };
}
