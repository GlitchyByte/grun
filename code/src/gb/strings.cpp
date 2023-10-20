// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include "gb/strings.h"
#ifdef GB_STRINGS

namespace gb::strings {

    std::vector<std::string_view> createVectorStringViewFromCArray(const int argc, const char* argv[]) noexcept {
        const size_t argsSize { static_cast<size_t>(argc) };
        std::vector<std::string_view> args { argsSize };
        for (size_t i = 0; i < argsSize; ++i) {
            args[i] = std::string_view { argv[i] };
        }
        return args;
    }

    std::vector<std::string> createVectorStringFromCArray(const int argc, const char* argv[]) noexcept {
        const size_t argsSize { static_cast<size_t>(argc) };
        std::vector<std::string> args { argsSize };
        for (size_t i = 0; i < argsSize; ++i) {
            args[i] = std::string { argv[i] };
        }
        return args;
    }

    std::string replace(const std::string_view& str, const std::string_view& token, const std::string_view& value) noexcept {
        size_t pos = { str.find(token) };
        if (pos == std::string::npos) {
            return "";
        }
        std::string newStr { str };
        return newStr.replace(pos, token.length(), value);
    }

    std::vector<std::string_view> splitWeak(const std::string_view& str, const std::string_view& delimiter) noexcept {
        const size_t delimiterSize { delimiter.size() };
        size_t pos { str.find(delimiter) };
        if ((delimiterSize == 0) || (pos == std::string::npos)) {
            return std::vector<std::string_view> { std::string { str } };
        }
        size_t start { 0 };
        std::vector<std::string_view> lines;
        while (pos != std::string::npos) {
            lines.emplace_back(str.substr(start, pos - start));
            start = pos + delimiterSize;
            pos = str.find(delimiter, start);
        }
        lines.emplace_back(str.substr(start));
        return lines;
    }

    std::vector<std::string> split(const std::string_view& str, const std::string_view& delimiter) noexcept {
        const std::vector<std::string_view> weak { std::move(splitWeak(str, delimiter)) };
        const size_t weakSize { weak.size() };
        std::vector<std::string> lines { weakSize };
        for (size_t i = 0; i < weakSize; ++i) {
            lines[i] = weak[i];
        }
        return lines;
    }

    std::string unindent(const std::string_view& str) noexcept {
        if (str.empty()) {
            return "";
        }
        auto lines { std::move(splitWeak(str, "\n")) };
        if (lines.size() == 1) {
            return std::string { str };
        }
        if (lines[0].empty()) {
            // We allow a 1st new line so that it looks good in code.
            // We remove that extra first line.
            lines.erase(lines.begin());
        }
        // Find indentation.
        size_t indent { std::string::npos };
        bool foundDifference { false };
        while (!foundDifference) {
            char ch;
            for (size_t index = 0; index < lines.size(); ++index) {
                const auto& line { lines[index] };
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
                foundDifference = (indent >= line.size()) || (line[indent] != ch);
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
        bool first { true };
        for (const auto& line: lines) {
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

    std::string& insertThousandSeparatorsInPlace(std::string& str) noexcept {
        const size_t period { str.find('.') };
        const size_t start { period == std::string::npos ? str.length() : period };
        const size_t finish { static_cast<size_t>(str.starts_with('-') ? 4 : 3) };
        size_t index { start };
        while (index > finish) {
            index -= 3;
            str.insert(index, ",");
        }
        return str;
    }

    std::string insertThousandSeparators(const std::string_view& str) noexcept {
        std::string newStr { str };
        return insertThousandSeparatorsInPlace(newStr);
    }

    constinit int DefaultPrecision { -1 };
}

#endif // GB_STRINGS
