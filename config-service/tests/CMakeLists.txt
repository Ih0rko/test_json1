add_executable(config_tests test_config.cpp)
target_link_libraries(config_tests PRIVATE service_config GTest::gtest_main)

add_test(NAME config_tests COMMAND config_tests)
