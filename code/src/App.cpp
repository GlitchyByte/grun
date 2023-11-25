// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include <map>
#include <filesystem>
#include <iostream>
#include <regex>
#include "gb.h"
#include "GradleParams.h"
#include "App.h"

gb::console::color_t const textColor { gb::console::rgb(1, 1, 1) };
gb::console::color_t const highlightColor { gb::console::rgb(5, 5, 5) };
gb::console::color_t const cmdColor { gb::console::rgb(3, 5, 3) };
gb::console::color_t const argColor { gb::console::rgb(0, 2, 0) };

void printUsage() noexcept {
    std::string const text { gb::strings::unindent(R"===(
        Run a Gradle project.
        Usage:
          ${app} <${param1}> <${param2}> [${args}]

          ${param1} Directory of your main project Gradle root (e.g., "~/my/app/here" or ".")
          ${param2}             Project name (e.g., "myapp")
          ${args}            Arguments for the running project.
        )===") };
    std::string const usage { gb::ReplaceableVars()
            .add("app", gb::console::colorText("grun", cmdColor))
            .add("param1", gb::console::colorText("project_gradle_root", argColor))
            .add("param2", gb::console::colorText("project", argColor))
            .add("args", gb::console::colorText("args ...", argColor))
            .replace(text) };
    std::cout << usage;
}

std::map<std::string, std::string> buildAndRetrieveGradleProperties(GradleParams const& gradleParams) noexcept {
#ifdef _WIN32
    std::string const gradleCommand { "gradlew.bat" };
#else
    std::string const gradleCommand { "./gradlew" };
#endif
    std::string const command { gb::ReplaceableVars()
            .add("gradle", gradleCommand)
            .add("project", gradleParams.getGradleProject())
            .replace("${gradle} ${project}:build ${project}:properties")
    };
    std::map<std::string, std::string> properties;
    int exitCode;
    std::regex const re { "^([a-zA-Z]+): ([^ ].*)$" };
    std::smatch match;
    gb::process::execute(command, gradleParams.getGradleRoot(), nullptr, &exitCode,
            [&](std::string const& line) {
                if (!std::regex_match(line, match, re) || (match.size() != 3)) {
                    return false;
                }
                std::string const key { match[1] };
                std::string const value { match[2] };
                properties[key] = value;
                return true;
            });
    if (exitCode != 0) {
        properties.clear();
    }
    return properties;
}

void printMessage(std::string_view const& msg, std::string_view const& param) noexcept {
    size_t const pos = msg.find('@');
    std::cerr << gb::console::colorText(msg.substr(0, pos), textColor)
            << gb::console::colorText(param, highlightColor)
            << gb::console::colorText(msg.substr(pos +1), textColor)
            << std::endl;
}

int extractBin(GradleParams const& gradleParams, std::filesystem::path* binPath) noexcept {
    // Capture Gradle properties.
    auto const gradleProperties = buildAndRetrieveGradleProperties(gradleParams);
    if (gradleProperties.empty()) {
        printMessage("Error building and getting properties for '@'.", gradleParams.getGradleProject());
        return 2;
    }
    if (!gradleProperties.contains("buildDir")) {
        printMessage("Property '@' not found!", "buildDir");
        return 2;
    }
    std::string const buildDir { gradleProperties.at("buildDir") };
    if (!gradleProperties.contains("distsDirName")) {
        printMessage("Property '@' not found!", "distsDirName");
        return 2;
    }
    std::string const distsDirName { gradleProperties.at("distsDirName") };
    if (!gradleProperties.contains("applicationName")) {
        printMessage("Property '@' not found!", "applicationName");
        return 2;
    }
    std::string const applicationName { gradleProperties.at("applicationName") };
    std::string const version { gradleProperties.contains("version") ? gradleProperties.at("version") : "" };
    std::string const tarName { (version.empty() ? applicationName : applicationName + '-' + version) + ".tar" };
    std::filesystem::path const distDir { buildDir + '/' + distsDirName };
    std::filesystem::path const tarPath = distDir / tarName;
    if (!std::filesystem::is_regular_file(tarPath)) {
        printMessage("Distribution not found: @", tarPath.string());
        return 2;
    }
    // Untar.
    std::filesystem::path workDir { distDir / tarName.substr(0, tarName.length() - 4) };
    std::filesystem::remove_all(workDir);
    if (!gb::process::execute("tar -xf " + tarName, distDir)) {
        printMessage("Can't untar: @", tarPath.string());
        return 3;
    }
    *binPath = workDir / "bin" / applicationName;
    return 0;
}

int App::run(std::vector<std::string_view> const& args) noexcept {
    GradleParams const gradleParams { args };
    if (!gradleParams.isValid()) {
        printUsage();
        return 1;
    }
    std::filesystem::path binPath;
    int result = extractBin(gradleParams, &binPath);
    if (result != 0) {
        return result;
    }
    std::string const command { binPath.string() + ' ' + gb::strings::fromVector(gradleParams.getProjectArgs(), " ") };
    result = std::system(command.c_str());
    std::cout << gb::console::colorText("Exit code: ", textColor)
            << gb::console::colorText(std::to_string(result), highlightColor)
            << std::endl;
    return 0;
}
