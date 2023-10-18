// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include <iostream>
#include <regex>
#include "App.h"

const glib::console::color_t textColor { glib::console::rgb(1, 1, 1) };
const glib::console::color_t highlightColor { glib::console::rgb(5, 5, 5) };
const glib::console::color_t cmdColor { glib::console::rgb(3, 5, 3) };
const glib::console::color_t argColor { glib::console::rgb(0, 2, 0) };

void printUsage() noexcept {
    const std::string text = glib::strings::unindent(R"===(
        Run a Gradle project.
        Usage:
          ${app} <${param1}> <${param2}> [${args}]

          ${param1} Directory of your main project Gradle root (e.g., "~/my/app/here" or ".")
          ${param2}             Project name (e.g., "myapp")
          ${args}            Arguments for the running project.
        )===");
    const std::string usage = glib::ReplaceableVars()
            .add("app", glib::console::colorText("grun", cmdColor))
            .add("param1", glib::console::colorText("project_gradle_root", argColor))
            .add("param2", glib::console::colorText("project", argColor))
            .add("args", glib::console::colorText("args ...", argColor))
            .replace(text);
    std::cout << usage;
}

std::map<std::string, std::string> buildAndRetrieveGradleProperties(const GradleParams& gradleParams) noexcept {
#ifdef _WIN32
    const std::string gradleCommand { "gradlew.bat" };
#else
    const std::string gradleCommand { "./gradlew" };
#endif
    const std::string command { glib::ReplaceableVars()
            .add("gradle", gradleCommand)
            .add("project", gradleParams.getGradleProject())
            .replace("${gradle} ${project}:build ${project}:properties")
    };
    std::map<std::string, std::string> properties;
    int exitCode;
    const std::regex re { "^([a-zA-Z]+): ([^ ].*)$" };
    std::smatch match;
    glib::process::execute(command, gradleParams.getGradleRoot(), nullptr, &exitCode,
            [&](const std::string_view& line) {
                const std::string str { line };
                if (!std::regex_match(str, match, re) || (match.size() != 3)) {
                    return false;
                }
                const std::string key { match[1] };
                const std::string value { match[2] };
                properties[key] = value;
                return true;
            });
    if (exitCode != 0) {
        properties.clear();
    }
    return properties;
}

void printMessage(const std::string_view& msg, const std::string_view& param) noexcept {
    const size_t pos = msg.find('@');
    std::cerr << glib::console::colorText(msg.substr(0, pos), textColor)
            << glib::console::colorText(param, highlightColor)
            << glib::console::colorText(msg.substr(pos +1), textColor)
            << std::endl;
}

int extractBin(const GradleParams& gradleParams, std::filesystem::path* binPath) noexcept {
    // Capture Gradle properties.
    const auto gradleProperties = buildAndRetrieveGradleProperties(gradleParams);
    if (gradleProperties.empty()) {
        printMessage("Error building and getting properties for '@'.", gradleParams.getGradleProject());
        return 2;
    }
    if (!gradleProperties.contains("buildDir")) {
        printMessage("Property '@' not found!", "buildDir");
        return 2;
    }
    const std::string buildDir { gradleProperties.at("buildDir") };
    if (!gradleProperties.contains("distsDirName")) {
        printMessage("Property '@' not found!", "distsDirName");
        return 2;
    }
    const std::string distsDirName { gradleProperties.at("distsDirName") };
    if (!gradleProperties.contains("applicationName")) {
        printMessage("Property '@' not found!", "applicationName");
        return 2;
    }
    const std::string applicationName { gradleProperties.at("applicationName") };
    const std::string version { gradleProperties.contains("version") ? gradleProperties.at("version") : "" };
    const std::string tarName { (version.empty() ? applicationName : applicationName + '-' + version) + ".tar" };
    const std::filesystem::path distDir { buildDir + '/' + distsDirName };
    const std::filesystem::path tarPath = distDir / tarName;
    if (!std::filesystem::is_regular_file(tarPath)) {
        printMessage("Distribution not found: @", tarPath.string());
        return 2;
    }
    // Untar.
    std::filesystem::path workDir { distDir / tarName.substr(0, tarName.length() - 4) };
    std::filesystem::remove_all(workDir);
    if (!glib::process::execute("tar -xf " + tarName, distDir)) {
        printMessage("Can't untar: @", tarPath.string());
        return 3;
    }
    *binPath = workDir / "bin" / applicationName;
    return 0;
}

int App::run(const std::vector<std::string_view>& args) noexcept {
    const GradleParams gradleParams { args };
    if (!gradleParams.isValid()) {
        printUsage();
        return 1;
    }
    std::filesystem::path binPath;
    int result = extractBin(gradleParams, &binPath);
    if (result != 0) {
        return result;
    }
    const std::string command { binPath.string() + ' ' + glib::strings::fromVector(gradleParams.getProjectArgs(), " ") };
    result = std::system(command.c_str());
    std::cout << glib::console::colorText("Exit code: ", textColor)
            << glib::console::colorText(std::to_string(result), highlightColor)
            << std::endl;
    return 0;
}
