// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <iostream>

namespace glib::collections {

    /**
     * Converts a C string array into a vector.
     *
     * <p>This function is specifically designed to convert main function args
     * into a string vector.
     *
     * @param argc String array size.
     * @param argv Array of C strings.
     * @return A string vector of the arguments.
     */
    std::vector<std::string> createVectorFromCArray(const int argc, const char* argv[]);
}
