cmake_minimum_required(VERSION 3.20)
project(JSONParser
    VERSION 1.0.0
    DESCRIPTION "Modern C++17 JSON parsing with Boost"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Boost (Boost.JSON is header-only)
find_package(Boost 1.70 REQUIRED)

find_package(GTest REQUIRED)

enable_testing()

add_library(config_lib
    src/Config.cpp
)

target_link_libraries(config_lib PRIVATE Boost::boost)

target_include_directories(config_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(json_parser
    src/main.cpp
)

target_link_libraries(json_parser PRIVATE config_lib)

# Link filesystem library (C++17)
if(NOT MSVC)
    target_link_libraries(json_parser PRIVATE stdc++fs)
endif()

# Compiler flags for modern C++
if(MSVC)
    target_compile_options(json_parser PRIVATE /W4)
    target_compile_options(config_lib PRIVATE /W4)
else()
    target_compile_options(json_parser PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(config_lib PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(config_tests
    tests/config_tests.cpp
)

target_link_libraries(config_tests PRIVATE
    config_lib
    Boost::boost
    GTest::gtest
    GTest::gtest_main
)

add_test(NAME ConfigTests COMMAND config_tests)
