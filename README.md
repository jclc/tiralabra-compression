# tiralabra-compression

This repository holds a data structures-related university project. Course-related documentation is in Finnish, but documentation pertaining to its usage will also be in English.

## Requirements

* GCC 4.4/Clang 3.3 or newer
* Little-endian CPU architecture (for now)
* CMake 3.1 or newer
* Google Test for tests (optional)

## Building

Use `cmake` or `cmake-gui` to generate makefiles. Run `make` to build.

### Example

```
mkdir build; cd build
cmake ..
make
```

## Usage

`tl-compression [options] <input file> [output file]`

Uncompressed files will be compressed and compressed files are detected as such and are uncompressed.

If output file is not given, output will be printed to stdout.

### Options

`-h` Print help message

`-v` Verbose output - Print file information and progress (don't use when writing to stdout)

`-b` Benchmark mode - Print execution time in nanoseconds

`-i` Print file info - Do not operate on the file, only print info

`-n` Null output - Discard output, useful for benchmarking without file I/O

Options can be entered separately `-v -b -n`, together `-vbn` or both `-vb -n`. They can also be entered before or after other arguments.

## Running unit tests

If you created makefiles with `MAKE_TESTS` enabled, tests should have been compiled in the build/tests directory. Run tests with `ctest --output-on-failure` or equivalent in the build/tests directory.

Note that the tests require the test-resources directory located in the source directory to be present. The tests will fail if the directory and files within are not present.

## Projektin dokumentaatio

Projektin dokumentaatio sijaitsee project-docs/-hakemistossa.
