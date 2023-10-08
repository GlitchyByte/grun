// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include <sstream>
#include "glib/gstrings.h"

namespace glib::strings {

    std::vector<std::string> split(const std::string& str, const std::string& delimiter) noexcept {
        const size_t delimiterSize = delimiter.size();
        if (delimiterSize == 0) {
            return std::vector<std::string> { str };
        }
        size_t pos = str.find(delimiter);
        if (pos == std::string::npos) {
            return std::vector<std::string> { str };
        }
        size_t start = 0;
        std::vector<std::string> lines;
        while (pos != std::string::npos) {
            const auto line = str.substr(start, pos - start);
            lines.push_back(line);
            start = pos + delimiterSize;
            pos = str.find(delimiter, start);
        }
        const auto line = str.substr(start);
        lines.push_back(line);
        return lines;
    }

    std::string unindent(const std::string& str) noexcept {
        if (str.empty()) {
            return str;
        }
        std::vector<std::string> lines = split(str, "\n");
        if (lines.size() == 1) {
            return str;
        }
        if (lines[0].empty()) {
            // We allow a 1st new line so that it looks good in code.
            // We remove that extra first line.
            lines.erase(lines.begin());
        }
        // Find indentation.
        size_t indent = std::string::npos;
        bool foundDifference = false;
        while (!foundDifference) {
            char ch;
            for (size_t index = 0; index < lines.size(); ++index) {
                const std::string line = lines[index];
                if (line.empty()) {
                    continue;
                }
                if (index == 0) {
                    if ((indent != -1) && (indent >= line.size())) {
                        foundDifference = true;
                        break;
                    }
                    if (indent == std::string::npos) {
                        indent = 0;
                    } else {
                        ++indent;
                    }
                    ch = line[index];
                    if ((ch == ' ') || (ch == '\t')) {
                        continue;
                    }
                    foundDifference = true;
                    break;
                }
                foundDifference = (indent >= line.size()) ||
                        (line[indent] != ch);
                if (foundDifference) {
                    break;
                }
            }
        }
        // Reassemble while removing indentation.
        if (indent == std::string::npos) {
            indent = 0;
        }
        std::ostringstream ss;
        bool first = true;
        for (const std::string& line: lines) {
            if (first) {
                first = false;
            } else {
                ss << '\n';
            }
            if (line.empty()) {
                continue;
            }
            if (indent == 0) {
                ss << line;
            } else {
                ss << line.substr(indent);
            }
        }
        return ss.str();
    }
}
