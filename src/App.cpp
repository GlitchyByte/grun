// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include <map>
#include <thread>
#include "glib/strings.h"
#include "GradleParams.h"
#include "App.h"
#include "glib/ReplaceableVars.h"

void sayHi() {
    std::cout << "Heyas!" << std::endl;
}

int App::run(const std::vector<std::string>& args) {
    const GradleParams gradleParams(args);
    if (!gradleParams.isValid()) {
        printUsage();
        return 1;
    }
    std::cout << "params: " << gradleParams.string() << std::endl;
    std::cout << "Here we go..." << std::endl;
    std::thread thread(sayHi);
    std::cout << "Waiting..." << std::endl;
    thread.join();
    std::cout << "We out!" << std::endl;
    return 0;
}

void App::printUsage() {
    const std::string text = glib::strings::unindent(R"===(
        Run a Gradle project.
        Usage:
          ${app} ${param1} ${param2}

          ${param1} Directory of your main project Gradle root (e.g., "some/sub/dir" or ".")
          ${param2}             Project name (e.g., "glib")
        )===");
    const std::string usage = glib::ReplaceableVars()
        .addString("app", glib::console::coloredText("grun", cmdColor))
        .addString("param1", glib::console::coloredText("PROJECT_GRADLE_ROOT", argColor))
        .addString("param2", glib::console::coloredText("PROJECT", argColor))
        .replace(text);
    std::cout << usage;
}
