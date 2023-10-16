// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include "glib/files.h"
#ifdef GLIB_FILES

namespace glib::files {

    std::filesystem::path canonicalPath(const std::filesystem::path& path) noexcept {
        std::string pathStr { path.string() };
        const std::string fullPath {
            pathStr.starts_with('~') ?
                std::getenv("HOME") + pathStr.substr(1) :
                std::move(pathStr)
        };
        return std::filesystem::weakly_canonical(fullPath);
    }
}

#endif
