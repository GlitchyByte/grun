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
        FILE* pipe = popen(redirectedCommand.str().c_str(), "r");
        if (!pipe) {
            std::filesystem::current_path(originalDir);
            return false;
        }
        const char *line;
        size_t lineLen;
        std::string_view lineView;
        do {
            line = fgetln(pipe, &lineLen);
            if ((line == NULL) || ((lines == nullptr) && (filter == nullptr))) {
                continue;
            }
            if (lineLen == 0) {
                lineView = "";
            } else if (line[lineLen - 1] == '\n') {
                lineView = std::string_view { line, lineLen - 1 };
            } else {
                lineView = std::string_view { line, lineLen };
            }
            if ((filter == nullptr) || filter(lineView)) {
                if (lines != nullptr) {
                    lines->emplace_back(lineView);
                }
            }
        } while (line != NULL);
        const int closeCode = pclose(pipe);
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
