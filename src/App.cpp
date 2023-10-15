// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include <thread>
#include <sstream>
#include <iostream>
#include <regex>
#include "App.h"
#include "glib/strings.h"
#include "glib/ReplaceableVars.h"
#include "glib/process.h"

const glib::console::color_t App::textColor { glib::console::rgb(1, 1, 1) };
const glib::console::color_t App::cmdColor { glib::console::rgb(3, 5, 3) };
const glib::console::color_t App::argColor { glib::console::rgb(0, 2, 0) };

//void sayHi() {
//    std::cout << "Heyas!" << std::endl;
//    std::cout << "Bye!" << std::endl;
//}

int App::run(const std::vector<std::string_view>& args) noexcept {
    const GradleParams gradleParams { args };
    if (!gradleParams.isValid()) {
        printUsage();
        return 1;
    }
    const auto& gradleProperties = retrieveGradleProperties(gradleParams);
    for (const auto& entry: gradleProperties) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
//    system(R"===(echo "gimme: ";read user_input;echo "u: ${user_input}")===");
//    std::cout << "Here we go..." << std::endl;
//    std::thread thread { sayHi };
//    std::cout << "Waiting..." << std::endl;
//    thread.join();
    std::cout << "We out!" << std::endl;
    return 0;
}

std::map<std::string, std::string> App::retrieveGradleProperties(const GradleParams& gradleParams) noexcept {
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
    const std::regex re { "^([a-zA-Z]+): ([^ ].*)$" };
    std::smatch match;
    glib::process::execute(command, gradleParams.getGradleRoot(), nullptr, nullptr,
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
    return properties;
}

void App::printUsage() noexcept {
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
