// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include "gb.h"
#include "App.h"

int main(const int argc, const char* argv[]) {
    const auto& args = gb::strings::createVectorStringViewFromCArray(argc, argv);
    return App::run(args);
}
