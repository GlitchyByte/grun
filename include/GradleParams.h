// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <iostream>

class GradleParams {
public:
    explicit GradleParams(const std::vector<std::string>& args) noexcept;

    [[nodiscard]]
    std::string getGradleRoot() const noexcept;

    [[nodiscard]]
    std::string getGradleProject() const noexcept;

    [[nodiscard]]
    std::vector<std::string> getProjectArgs() const noexcept;

    [[nodiscard]]
    bool isValid() const noexcept;

    [[nodiscard]]
    std::string string() const noexcept;

private:
    std::string gradleRoot;
    std::string gradleProject;
    std::vector<std::string> projectArgs;
    bool valid;
};
