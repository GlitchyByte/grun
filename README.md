# grun

![Version](https://img.shields.io/badge/Version-1.1.0-blue)

This is a Gradle project runner. It builds, unpacks, and runs a Gradle project on the current terminal.
Also allows `SIGINT` (Ctrl+C) to be captured by your application.

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

It is highly recommended that you build it yourself on your platform.

If you want a pre-compiled binary for macOS, Windows, or Ubuntu, check the [latest release](https://github.com/GlitchyByte/grun/releases).
These are built using GitHub Actions on GitHub Runners.

## Build it!

Clone this repo. Then:

    ./build MinSizeRel clean

### Receive your tasty binary!

After building, `grun` executable is in the `code/bin` directory.
