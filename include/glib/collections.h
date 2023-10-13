// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>

namespace glib::collections {

    /**
     * Converts a C string array into a vector of weak strings.
     *
     * <p>The contents of the vector will be valid as long as the original array is valid.
     *
     * <p>This function is specifically designed to convert main function args
     * into a string vector.
     *
     * @param argc String array size.
     * @param argv Array of C strings.
     * @return A string vector of the arguments.
     */
    std::vector<std::string_view> createVectorFromCArrayWeak(const int argc, const char* argv[]) noexcept;

    /**
     * Converts a C string array into a vector of strings.
     *
     * <p>This function is specifically designed to convert main function args
     * into a string vector.
     *
     * @param argc String array size.
     * @param argv Array of C strings.
     * @return A string vector of the arguments.
     */
    std::vector<std::string> createVectorFromCArray(const int argc, const char* argv[]) noexcept;
}
