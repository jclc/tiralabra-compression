# tiralabra-compression

This repository holds a data structures-related university project. Course-related documentation is in Finnish, but documentation pertaining to its usage will also be in English.

## Requirements

* GCC 4.4/Clang 3.3 or newer
* Little-endian CPU architecture (for now)
* CMake 3.1 or newer
* Google Test for tests (optional)

## Building

Use `cmake` or `cmake-gui` to generate makefiles. Run `make` to build.

## Usage

`tl-compression [-v] <input file> [output file]`

If output file is not given, output will be printed to stdout.

Use the `-v` option for verbose output.

## Running unit tests

If you compiled with `MAKE_TESTS` enabled, tests should have been compiled in the build directory. Run tests with `ctest --output-on-failure` or equivalent. Tests require the "test-resources" directory and all the filew within to be present in the source directory.

## Projektin dokumentaatio

Projektin dokumentaatio sijaitsee project-docs/-hakemistossa.
