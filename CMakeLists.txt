cmake_minimum_required(VERSION 3.20)
project(JSONParser
    VERSION 1.0.0
    DESCRIPTION "Modern C++17 JSON parsing with Boost"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Boost REQUIRED NO_MODULE COMPONENTS json)
find_package(GTest REQUIRED)

enable_testing()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(config_lib SHARED
    src/Config.cpp
)

target_link_libraries(config_lib PRIVATE Boost::json)

target_include_directories(config_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(json_parser
    src/main.cpp
)
target_include_directories(json_parser PRIVATE ${Boost_INCLUDE_DIRS})

add_custom_command(TARGET json_parser POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            "${CMAKE_CURRENT_SOURCE_DIR}/config.json"
            "$<TARGET_FILE_DIR:json_parser>/config.json"
    COMMENT "Copying config file to binary directory"
)

target_link_libraries(json_parser PRIVATE config_lib)

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
target_include_directories(json_parser PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(config_tests PRIVATE
    config_lib
    GTest::gtest
    GTest::gtest_main
)

add_test(NAME ConfigTests COMMAND config_tests)
