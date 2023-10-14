// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <filesystem>

namespace glib::process {

    bool execute(const std::string& command, const std::optional<std::filesystem::path>& workDir = std::nullopt,
            std::vector<std::string>* lines = nullptr, int* exitCode = nullptr,
            std::function<bool(const std::string_view&)> filter = nullptr);
}
