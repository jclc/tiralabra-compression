# tiralabra-compression

This program implements the Lempel-Ziv-Welch compression algorithm and provides an encoder as well as a decoder.

Created as a Univ. of Helsinki TiraLabra 2017 course project.

## Requirements

* GCC 4.4/Clang 3.3 or newer
* CMake 3.1 or newer
* Google Test for tests (optional, untick MAKE_TESTS option in CMake to disable)

## Building

Use `cmake` or `cmake-gui` to generate makefiles. Run `make` or your build system of choice to build.

### Example

#### On \*nix
```
git clone https://github.com/jclc/tiralabra-compression.git
cd tiralabra-compression
mkdir build; cd build
cmake ..
make
```
This will compile the program in tiralabra-compression/build/

## Usage

`tiracomp [options] <input file> [output file]`

Uncompressed files will be compressed and compressed files are detected as such and are uncompressed.

If output file is not given, output will be printed to stdout.

### Options

| Switch | Parameter | Description |
|:------:|:---------:| ----------- |
| `-h`   |           | Print help message |
| `-v`   |           | Verbose output - Print file information and progress (don't use when writing to stdout) |
| `-b`   |           | Benchmark mode - Print execution time in milliseconds |
| `-w`   | word size | Define code word size in bits when encoding (either 12 or 16) |
| `-i`   |           | Print file info - Do not operate on the file, only print info |
| `-n`   |           | Null output - Discard output, useful for benchmarking without file I/O |

Options can be entered separately `-v -b -n`, together `-vbn` or both `-vb -n`. They can also be entered before or after other arguments.

## Running unit tests

If you created makefiles with `MAKE_TESTS` enabled, tests should have been compiled in the build/tests directory. Run tests with `ctest --output-on-failure` or equivalent in the build/tests directory.

Note that the tests require the test-resources directory located in the source directory to be present. The tests will fail if the directory and files within are not present.

## Projektin dokumentaatio

Projektin dokumentaatio sijaitsee project-docs/-hakemistossa.
 
