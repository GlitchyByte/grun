// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <iostream>
#include "glib/console.h"

class App {
public:
    static constexpr glib::console::color_t textColor = glib::console::rgb(1, 1, 1);
    static constexpr glib::console::color_t cmdColor = glib::console::rgb(3, 5, 3);
    static constexpr glib::console::color_t argColor = glib::console::rgb(0, 2, 0);

    static int run(const std::vector<std::string>& args);

private:
    static void printUsage();
};
