// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include "glib/process.h"
#ifdef GLIB_PROCESS

#include <cstdio>
#include <sstream>

namespace glib::process {

    bool execute(const std::string_view& command, const std::optional<std::filesystem::path>& workDir,
            std::deque<std::string>* lines, int* exitCode,
            const std::function<bool(const std::string_view&)>& filter) {
        const auto& originalDir { std::filesystem::current_path() };
        if (workDir.has_value()) {
            std::filesystem::current_path(workDir.value());
        }
        std::ostringstream redirectedCommand;
        redirectedCommand << command << " 2>&1";
        FILE* file { popen(redirectedCommand.str().c_str(), "r") };
        if (!file) {
            std::filesystem::current_path(originalDir);
            return false;
        }
        char* line { NULL };
        size_t lineLen { 0 };
        std::string_view lineView;
        do {
            lineLen = getline(&line, &lineLen, file);
            if ((lineLen == -1) || ((lines == nullptr) && (filter == nullptr))) {
                continue;
            }
            if (lineLen == 0) {
                lineView = "";
            } else if (line[lineLen - 1] == '\n') {
                #ifdef _WIN32
                lineView = std::string_view { line, lineLen - 2 };
                #else
                lineView = std::string_view { line, lineLen - 1 };
                #endif
            } else {
                lineView = std::string_view { line, lineLen };
            }
            if ((filter == nullptr) || filter(lineView)) {
                if (lines != nullptr) {
                    lines->emplace_back(lineView);
                }
            }
        } while (lineLen != -1);
        if (line != NULL) {
            free(line);
        }
        const int closeCode = pclose(file);
        std::filesystem::current_path(originalDir);
        if (WIFEXITED(closeCode)) {
            if (exitCode != nullptr) {
                *exitCode = WEXITSTATUS(closeCode);
            }
            return true;
        }
        return false;
    }
}

#endif // GLIB_PROCESS
