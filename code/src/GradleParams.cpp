// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include <filesystem>
#include "GradleParams.h"

GradleParams::GradleParams(const std::vector<std::string_view>& args) noexcept {
    const size_t size { args.size() };
    if (size < 3) {
        gradleRoot = std::filesystem::path {};
        gradleProject = std::string {};
        projectArgs = std::vector<std::string>(0);
        valid = false;
        return;
    }
    try {
        const std::string& rawRoot { args[1] };
        const std::string param { rawRoot.starts_with('~') ? std::getenv("HOME") + rawRoot.substr(1) : rawRoot };
        gradleRoot = std::filesystem::canonical(param);
    } catch (const std::exception& e) {
        gradleRoot = std::filesystem::path {};
        gradleProject = std::string {};
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

std::filesystem::path GradleParams::getGradleRoot() const noexcept {
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
    std::ostringstream ss;
    ss << "{ gradleRoot: " << gradleRoot
        << ", gradleProject: " << gradleProject
        << ", projectArgs: " << glib::strings::fromVector(projectArgs)
        << " }";
    return ss.str();
}
