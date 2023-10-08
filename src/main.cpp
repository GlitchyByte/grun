// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include "glib/collections.h"
#include "App.h"

int main(const int argc, const char* argv[]) {
    const std::vector<std::string> args = glib::collections::createVectorFromCArray(argc, argv);
    return App::run(args);
}
