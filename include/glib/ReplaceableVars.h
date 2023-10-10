// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "glib/types.h"

namespace glib {

    /**
     * Class to hold variable names and their values for string replacement.
     */
    class ReplaceableVars {
    public:
        /**
         * Default precision for numeric values.
         */
        static const int DefaultPrecision = -1;

        /**
         * Adds a string value.
         *
         * @param name Variable name.
         * @param value Value.
         * @return This object.
         */
        ReplaceableVars& addString(const std::string& name, const std::string& value) noexcept;

        /**
         * Adds an integer value.
         *
         * @tparam T Integer type.
         * @param name Variable name.
         * @param value Value.
         * @param humanReadable True to add thousand separators.
         * @return This object.
         */
        template <std::integral T>
        ReplaceableVars& addIntegral(const std::string& name, const T value, const bool humanReadable = false) noexcept;

        /**
         * Adds a floating point value.
         *
         * @tparam T Floating point type.
         * @param name Variable name.
         * @param value Value.
         * @param precision Number of decimals to show. Default shows all needed.
         * @param humanReadable True to add thousand separators.
         * @return This object.
         */
        template <std::floating_point T>
        ReplaceableVars& addFloatingPoint(const std::string& name, const T value, const int precision = DefaultPrecision,
                                  const bool humanReadable = false) noexcept;

        /**
         * Replace inline variables with values.
         *
         * @param str String with variables.
         * @return The replaced string.
         */
        [[nodiscard]]
        std::string replace(const std::string& str) noexcept;

        /**
         * String representation.
         *
         * @return The string representation.
         */
        [[nodiscard]]
        std::string string() const noexcept;

    private:
        glib::mapStringString vars;

        static void insertThousandSeparators(std::string& str) noexcept;
    };
}

#include "glib/ReplaceableVars.inl"
