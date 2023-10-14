// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include "glib/process.h"

namespace glib::process {

    bool execute(const std::string& command, const std::optional<std::filesystem::path>& workDir,
            std::vector<std::string>* lines, int* exitCode,
            std::function<bool(const std::string_view&)> filter) {
        const auto& originalDir = std::filesystem::current_path();
        if (workDir.has_value()) {
            std::filesystem::current_path(workDir.value());
        }
        FILE* pipe = popen(command.c_str(), "r");
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
