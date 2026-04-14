#include <gtest/gtest.h>
#include "service/config.hpp"

/**
 * @brief Verifies successful loading of a valid configuration file.
 */
TEST(ConfigTest, LoadsValidConfig) {
    auto cfg = service::Config::load_from_file("config/config.json");

    EXPECT_EQ(cfg.host, "127.0.0.1");
    EXPECT_EQ(cfg.port, 8080);
    EXPECT_TRUE(cfg.enable_logging);
}

/**
 * @brief Missing required field must produce a runtime error.
 */
TEST(ConfigTest, MissingFieldThrows) {
    const char* path = "tests/missing_field.json";
    std::ofstream(path) << R"({"host":"localhost","port":80})";

    EXPECT_THROW(
        service::Config::load_from_file(path),
        std::runtime_error
    );
}

/**
 * @brief Port values outside valid TCP range are rejected.
 */
TEST(ConfigTest, InvalidPortThrows) {
    const char* path = "tests/bad_port.json";
    std::ofstream(path)
        << R"({"host":"localhost","port":70000,"enable_logging":true})";

    EXPECT_THROW(
        service::Config::load_from_file(path),
        std::runtime_error
    );
}
