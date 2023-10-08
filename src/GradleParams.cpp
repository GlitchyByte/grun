// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include <filesystem>
#include "glib/strings.h"
#include "GradleParams.h"

GradleParams::GradleParams(const std::vector<std::string>& args) noexcept {
    const size_t size = args.size();
    if (size < 3) {
        gradleRoot = std::string();
        gradleProject = std::string();
        projectArgs = std::vector<std::string>(0);
        valid = false;
        return;
    }
    try {
        gradleRoot = std::filesystem::canonical(args[1]).string();
    } catch (const std::exception& e) {
        gradleRoot = std::string();
        gradleProject = std::string();
        projectArgs = std::vector<std::string>(0);
        valid = false;
        return;
    }
    gradleProject = args[2];
    projectArgs = std::vector<std::string>(size - 3);
    for (size_t i = 3; i < size; ++i) {
        projectArgs[i - 3] = args[i];
    }
    valid = true;
}

std::string GradleParams::getGradleRoot() const noexcept {
    return gradleRoot;
}

std::string GradleParams::getGradleProject() const noexcept {
    return gradleProject;
}

std::vector<std::string> GradleParams::getProjectArgs() const noexcept {
    return projectArgs;
}

bool GradleParams::isValid() const noexcept {
    return valid;
}

std::string GradleParams::string() const noexcept {
    return "{ gradleRoot: " + gradleRoot +
        ", gradleProject: " + gradleProject +
        ", projectArgs: " + glib::strings::fromVector(projectArgs) +
        " }";
}
