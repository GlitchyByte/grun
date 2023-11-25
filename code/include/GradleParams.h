// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>
#include "gb.h"

class GradleParams {
public:
    explicit GradleParams(std::vector<std::string_view> const& args) noexcept;

    [[nodiscard]]
    std::filesystem::path getGradleRoot() const noexcept;

    [[nodiscard]]
    std::string getGradleProject() const noexcept;

    [[nodiscard]]
    std::vector<std::string> getProjectArgs() const noexcept;

    [[nodiscard]]
    bool isValid() const noexcept;

    [[nodiscard]]
    std::string string() const noexcept;

private:
    std::filesystem::path gradleRoot;
    std::string gradleProject;
    std::vector<std::string> projectArgs;
    bool valid;
};
