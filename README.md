# grun

![Version](https://img.shields.io/badge/Version-1.0.0-blue)

This is a Gradle project runner. It builds, unpacks, and runs a Gradle project on the current console.
Also allows `SIGINT` (Ctrl+C) to be captured by your application.
As opposed to Gradle's run task which doesn't attach a proper console and simply kills your app immediately on `SIGINT`.

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

    ./build MinSizeRel clean

On Windows:

*Windows hasn't been tested. If you try it, let me know if there are any issues.*

    cmake -DCMAKE_BUILD_TYPE=MinSizeRel -B build.cmake -S .
    cmake --build build.cmake --config MinSizeRel

#### Binary

Binary should be in `bin` directory. It is small enough to be committed as part of your solution.
