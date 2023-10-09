// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <iostream>

class GradleParams {
public:
    explicit GradleParams(const std::vector<std::string>& args) noexcept;

    [[nodiscard]]
    inline std::string getGradleRoot() const noexcept { return gradleRoot; }

    [[nodiscard]]
    inline std::string getGradleProject() const noexcept { return gradleProject; }

    [[nodiscard]]
    inline std::vector<std::string> getProjectArgs() const noexcept { return projectArgs; }

    [[nodiscard]]
    inline bool isValid() const noexcept { return valid; }

    [[nodiscard]]
    std::string string() const noexcept;

private:
    std::string gradleRoot;
    std::string gradleProject;
    std::vector<std::string> projectArgs;
    bool valid;
};
