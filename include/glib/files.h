// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <filesystem>

namespace glib::files {

    [[nodiscard]]
    std::filesystem::path canonicalPath(const std::filesystem::path& path);
}
