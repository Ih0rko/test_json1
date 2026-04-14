cmake_minimum_required(VERSION 3.16)
project(config_service LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_COVERAGE "Enable code coverage" OFF)

find_package(Boost REQUIRED COMPONENTS json)
find_package(GTest CONFIG REQUIRED)

add_library(service_config
    src/config.cpp
)

target_include_directories(service_config PUBLIC include)
target_link_libraries(service_config PUBLIC Boost::json)

add_executable(config_service src/main.cpp)
target_link_libraries(config_service PRIVATE service_config)

enable_testing()
add_subdirectory(tests)

if(ENABLE_COVERAGE)
    include(cmake/Coverage.cmake)
    append_coverage_compiler_flags()
endif()
