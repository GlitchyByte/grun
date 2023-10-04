## *THIS IS A WORK IN PROGRESS*

# grun

![Version](https://img.shields.io/badge/Version-0.1.0-blue)

This is a Gradle project runner. It builds, unpacks, and runs a Gradle project on the current console, also allows you full control of `SIGINT` (Ctrl+C).

As opposed to Gradle's run task which doesn't attach a proper console, and simply kills your app immediately on `SIGINT`.

### To use:

    ./grun GRADLE_ROOT MY_PROJECT [ARG1 ARG2 ...]

```bash
# For example: my Gradle root is in the "code" directory withing my overall "solution" directory. The project I want to run is "say":
# /solution
#   /code
#     /say
#   /run
./grun code say "Hello, world!"
```

### To build:

Clone this repo. On macOS or Linux:

    ./build Release

On Windows:

    cmake -DCMAKE_BUILD_TYPE=Release -B build.cmake -S .
    cmake --build build.cmake --config Release

Binary should be in `bin` directory. It is small enough to be committed as part of your solution.
