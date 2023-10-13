// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include "glib/SysCommand.h"

namespace glib {

    SysCommand::Builder& SysCommand::Builder::setArgs(const std::vector<std::string>& _args) noexcept {
        args = _args;
        return *this;
    }

    SysCommand::Builder& SysCommand::Builder::setWorkDir(const std::filesystem::path& _workDir) noexcept {
        workDir = _workDir;
        return *this;
    }

    std::unique_ptr<SysCommand> SysCommand::Builder::build() const noexcept {
        return std::make_unique<SysCommand>(command, args, workDir);
    }
}
