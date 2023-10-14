// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include "App.h"
#include "glib/collections.h"

int main(const int argc, const char* argv[]) {
    const auto& args = glib::collections::createVectorFromCArrayWeak(argc, argv);
    return App::run(args);
}
