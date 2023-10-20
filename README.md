# grun

![Version](https://img.shields.io/badge/Version-1.0.0-blue)

This is a Gradle project runner. It builds, unpacks, and runs a Gradle project on the current console.
Also allows `SIGINT` (Ctrl+C) to be captured by your application.
As opposed to Gradle's run task which doesn't attach a proper console and simply kills your app immediately on `SIGINT`.

## Use it!

    ./grun GRADLE_ROOT MY_PROJECT [ARG1 ARG2 ...]

```bash
# For example: my Gradle root is in the "code" directory withing my overall "solution" directory. The project I want to run is "say":
# /solution/
#   /grun
#   /code/
#     /gradlew
#     /say/
./grun code say "Hello, world!"
```

## Get it!

It is highly recommended that you build it yourself on your platform. *On my M1 Mac, the final binary is only 90KB.*

If you want a pre-compiled binary, check the [latest release](https://github.com/GlitchyByte/grun/releases) for your platform.
These are built using GitHub Actions on GitHub Runners and produce larger binaries than if you build locally.

## Build it!

Clone this repo.

Then, on macOS or Linux:

    ./build MinSizeRel clean

On Windows:

    cmake -DCMAKE_BUILD_TYPE=MinSizeRel -B build.cmake -S .
    cmake --build build.cmake --config MinSizeRel

### Receive your tasty binary!

After building, `grun` executable is in the `bin` directory.
