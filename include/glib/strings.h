// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "glib/types.h"

namespace glib::strings {

    /**
     * Splits a string by the delimiter into a vector of strings.
     *
     * @param str String to split.
     * @param delimiter Delimiter to split the string.
     * @return A vector of strings.
     */
    [[nodiscard]]
    std::vector<std::string> split(const std::string& str, const std::string& delimiter) noexcept;

    /**
     * Unindents a multiline block of text by removing all common spaces or tabs
     * from the beginning of the lines. Empty lines are left alone.
     *
     * <p>This function is specifically designed to use with raw string literals.
     * And it will remove indentation created to align the string with the rest
     * of the surrounding code.
     *
     * @param str String to unindent.
     * @return The unindented string.
     */
    [[nodiscard]]
    std::string unindent(const std::string& str) noexcept;

    /**
     * Joins a string representation of all elements into a string.
     * Each item is separate by a comma and a space.
     *
     * @tparam T The type of item.
     * @param vector Vector of items to join.
     * @return A joined string of all items.
     */
    template <typename T>
    [[nodiscard]]
    std::string fromVector(const std::vector<T>& vector);
}

#include "strings.inl"
