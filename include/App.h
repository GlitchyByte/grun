// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <map>
#include <filesystem>
#include "glib.h"
#include "GradleParams.h"

class App {
public:
    static int run(const std::vector<std::string_view>& args) noexcept;
};
