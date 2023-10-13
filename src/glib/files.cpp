// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include "glib/files.h"

namespace glib::files {

    std::filesystem::path canonicalPath(const std::filesystem::path& path) {
        std::string pathStr = path.string();
        std::string fullPath = pathStr.starts_with('~') ? std::getenv("HOME") + pathStr.substr(1) : std::move(pathStr);
        return std::filesystem::canonical(std::move(fullPath));
    }
}
