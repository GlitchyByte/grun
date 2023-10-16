// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <filesystem>

namespace glib::process {

    /**
     * Executes a command and optionally captures it's output.
     *
     * <p>Output can be filtered before capture, allowing the caller to even process the lines
     * as they come and not capture. It is advised that the filter lambda be as fast as possible
     * so as to not hold the executed process.
     *
     * @param command Full command line as it would be on a terminal.
     * @param workDir Directory to run the command on.
     * @param lines Optional vector to accumulate lines into.
     * @param exitCode Optional exit code from command.
     * @param filter Optional lambda to filter or process each line.
     *              filter must return true to add the line to lines, false to skip.
     * @return True if command execution was successful.
     */
    bool execute(const std::string_view& command, const std::optional<std::filesystem::path>& workDir = std::nullopt,
            std::vector<std::string>* lines = nullptr, int* exitCode = nullptr,
            const std::function<bool(const std::string_view&)>& filter = nullptr);
}
