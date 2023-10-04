// Copyright 2023 GlitchyByte
// SPDX-License-Identifier: Apache-2.0

#include <iostream>
#include <thread>

void sayHi() {
    std::cout << "Heyas!" << std::endl;
}

int main() {
    std::cout << "Here we go..." << std::endl;
    std::thread thread(sayHi);
    std::cout << "Waiting..." << std::endl;
    thread.join();
    std::cout << "We out!" << std::endl;
    return 0;
}
