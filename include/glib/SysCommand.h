// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <filesystem>
#include <utility>

namespace glib {

    class SysCommand {
    public:
        class Builder {
        public:
            Builder(const std::string& _command) noexcept : command(_command) {};

            [[nodiscard]]
            Builder& setArgs(const std::vector<std::string>& _args) noexcept;

            [[nodiscard]]
            Builder& setWorkDir(const std::filesystem::path& _workDir) noexcept;

            [[nodiscard]]
            std::unique_ptr<SysCommand> build() const noexcept;

        private:
            std::string command;
            std::vector<std::string> args;
            std::filesystem::path workDir;
        };

        SysCommand(std::string _command, std::vector<std::string> _args, std::filesystem::path _workDir) noexcept :
            command(std::move(_command)), args(std::move(_args)), workDir(std::move(_workDir)) {}

    private:
        const std::string command;
        const std::vector<std::string> args;
        const std::filesystem::path workDir;
    };
}
