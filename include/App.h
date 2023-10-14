// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <map>
#include <filesystem>
#include "GradleParams.h"
#include "glib/console.h"

class App {
public:
    static const glib::console::color_t textColor;
    static const glib::console::color_t cmdColor;
    static const glib::console::color_t argColor;

    static int run(const std::vector<std::string_view>& args) noexcept;

private:
    static void printUsage() noexcept;
    static std::map<std::string, std::string> retrieveGradleProperties(const GradleParams& gradleParams) noexcept;
};
