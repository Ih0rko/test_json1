# JSON Parser - Modern C++17 with Boost

A modern C++17 CMake project demonstrating JSON parsing using Boost.JSON with comprehensive unit tests using Google Test.

## Features

- **C++17 Standard** - Modern C++ with structured bindings and other C++17 features
- **CMake 3.20+** - Professional build configuration
- **Boost.JSON** - Header-only JSON parsing library
- **Google Test** - Modern unit testing framework with comprehensive test coverage
- **Config Class** - Dedicated JSON configuration parser with validation
- **Cross-platform** - Works on Linux, macOS, and Windows

## Requirements

- CMake 3.20 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- Boost 1.70 or higher
- Google Test (libgtest-dev on Ubuntu/Debian)

## Building

### Linux/macOS

```bash
mkdir build
cd build
cmake ..
make
./json_parser
```

### Running the Program

```bash
# Run with default config file (config.json)
./json_parser

# Run with custom config file
./json_parser /path/to/custom_config.json
```

### Running Tests

```bash
make
make test
# or with verbose output:
./config_tests
```

### Windows (with Visual Studio)

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
.\Release\json_parser.exe
```

## Installing Dependencies

### Ubuntu/Debian

```bash
sudo apt-get install libboost-all-dev libgtest-dev
```

### macOS (with Homebrew)

```bash
brew install boost googletest
```

### Windows (with vcpkg)

```bash
vcpkg install boost:x64-windows googletest:x64-windows
```

## Project Structure

```
├── CMakeLists.txt           # CMake configuration
├── config.json              # Default configuration file
├── src/
│   ├── main.cpp             # Main program (reads config from file)
│   └── Config.cpp           # Config class implementation
├── include/
│   └── Config.h             # Config class header
├── tests/
│   └── config_tests.cpp     # Unit tests (25+ test cases)
├── README.md
└── LICENSE
```

## Config Class

The `Config` class parses JSON configuration strings with the following fields:

```json
{
  "host": "localhost",
  "port": 8080,
  "enable_logging": true
}
```

### Features:
- **Type validation** - Ensures correct types for all fields
- **Port validation** - Validates port range (0-65535)
- **Error handling** - Clear error messages for missing or invalid fields
- **Modern C++** - Uses const-correctness and `[[nodiscard]]` attributes

## Unit Tests

The test suite includes 25+ comprehensive test cases covering:

- ✓ Valid configuration parsing
- ✓ Different configuration values
- ✓ Port boundary conditions (0, 65535)
- ✓ Missing required fields
- ✓ Invalid data types
- ✓ Port out-of-range validation
- ✓ Malformed JSON handling
- ✓ Extra fields (gracefully ignored)
- ✓ Special characters and whitespace handling
- ✓ Common port values

### Run tests:
```bash
cd build
./config_tests
# or with cmake:
ctest --output-on-failure
```

## License

See LICENSE file for details.
