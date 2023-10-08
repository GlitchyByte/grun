// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <iostream>
#include "glib/ReplaceableVars.h"

namespace glib::console {

    typedef uint32_t color_t;

    const std::string csi = "\u001b[";
    const std::string csiColorReset = csi + "0m";
    const std::string csiColorForeground = csi + "38;5;${code}m";

    /**
     * Converts rgb values into a single color code.
     *
     * @param r Red value between [0, 6).
     * @param g Green value between [0, 6).
     * @param b Blue value between [0, 6).
     * @return The color code.
     */
    [[nodiscard]]
    consteval color_t rgb(const color_t r, const color_t g, const color_t b) noexcept {
        const color_t _r = std::min(r, static_cast<color_t>(6));
        const color_t _g = std::min(g, static_cast<color_t>(6));
        const color_t _b = std::min(b, static_cast<color_t>(6));
        return 16 + (36 * _r) + (6 * _g) + _b;
    }

    /**
     * Converts a grey step into a color code.
     *
     * @param step Grey step between [0, 24).
     * @return The color code.
     */
    [[nodiscard]]
    consteval color_t grey(const color_t step) noexcept {
        const color_t _step = std::min(step, static_cast<color_t>(24));
        return 232 + _step;
    }

    [[nodiscard]]
    std::string coloredText(const std::string& str, const color_t color) noexcept;
}
