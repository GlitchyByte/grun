// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "glib.h"
#ifdef GLIB_CONSOLE

#include <string>

namespace glib::console {

    typedef uint32_t color_t;

    #define CODE "@"
    #define CSI "\u001b["
    #define CSI_COLOR_RESET CSI "0m"
    #define CSI_COLOR_FOREGROUND CSI "38;5;" CODE "m"

    /**
     * Converts rgb values into a single color code.
     *
     * @param r Red value between [0, 6).
     * @param g Green value between [0, 6).
     * @param b Blue value between [0, 6).
     * @return The color code.
     */
    [[nodiscard]]
    extern color_t rgb(const color_t r, const color_t g, const color_t b) noexcept;

    /**
     * Converts a grey step into a color code.
     *
     * @param step Grey step between [0, 24).
     * @return The color code.
     */
    [[nodiscard]]
    extern color_t grey(const color_t step) noexcept;

    /**
     * Returns a string that represents the given string in the given color.
     *
     * @param str String to apply color.
     * @param color Color.
     * @return The string in color.
     */
    [[nodiscard]]
    std::string colorText(const std::string_view& str, const color_t color) noexcept;
}

#endif // GLIB_CONSOLE
