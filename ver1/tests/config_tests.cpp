#include <gtest/gtest.h>
#include "Config.h"
#include <stdexcept>

// Test valid configuration parsing
TEST(ConfigTest, ValidConfigurationParsing) {
    std::string valid_json = R"({
        "host": "localhost",
        "port": 8080,
        "enable_logging": true
    })";

    EXPECT_NO_THROW({
        Config config(valid_json);
        EXPECT_EQ(config.getHost(), "localhost");
        EXPECT_EQ(config.getPort(), 8080);
        EXPECT_TRUE(config.isLoggingEnabled());
    });
}

// Test valid configuration with different values
TEST(ConfigTest, ValidConfigurationWithDifferentValues) {
    std::string valid_json = R"({
        "host": "192.168.1.1",
        "port": 3000,
        "enable_logging": false
    })";

    EXPECT_NO_THROW({
        Config config(valid_json);
        EXPECT_EQ(config.getHost(), "192.168.1.1");
        EXPECT_EQ(config.getPort(), 3000);
        EXPECT_FALSE(config.isLoggingEnabled());
    });
}

// Test minimum valid port
TEST(ConfigTest, MinimumValidPort) {
    std::string valid_json = R"({
        "host": "localhost",
        "port": 0,
        "enable_logging": true
    })";

    EXPECT_NO_THROW({
        Config config(valid_json);
        EXPECT_EQ(config.getPort(), 0);
    });
}

// Test maximum valid port
TEST(ConfigTest, MaximumValidPort) {
    std::string valid_json = R"({
        "host": "localhost",
        "port": 65535,
        "enable_logging": true
    })";

    EXPECT_NO_THROW({
        Config config(valid_json);
        EXPECT_EQ(config.getPort(), 65535);
    });
}

// Test missing host field
TEST(ConfigTest, MissingHostField) {
    std::string invalid_json = R"({
        "port": 8080,
        "enable_logging": true
    })";

    EXPECT_THROW({
        Config config(invalid_json);
    }, std::runtime_error);
}

// Test missing port field
TEST(ConfigTest, MissingPortField) {
    std::string invalid_json = R"({
        "host": "localhost",
        "enable_logging": true
    })";

    EXPECT_THROW({
        Config config(invalid_json);
    }, std::runtime_error);
}

// Test missing enable_logging field
TEST(ConfigTest, MissingLoggingField) {
    std::string invalid_json = R"({
        "host": "localhost",
        "port": 8080
    })";

    EXPECT_THROW({
        Config config(invalid_json);
    }, std::runtime_error);
}

// Test invalid host type (number instead of string)
TEST(ConfigTest, InvalidHostType) {
    std::string invalid_json = R"({
        "host": 12345,
        "port": 8080,
        "enable_logging": true
    })";

    EXPECT_THROW({
        Config config(invalid_json);
    }, std::runtime_error);
}

// Test invalid port type (string instead of integer)
TEST(ConfigTest, InvalidPortType) {
    std::string invalid_json = R"({
        "host": "localhost",
        "port": "8080",
        "enable_logging": true
    })";

    EXPECT_THROW({
        Config config(invalid_json);
    }, std::runtime_error);
}

// Test invalid enable_logging type (string instead of boolean)
TEST(ConfigTest, InvalidLoggingType) {
    std::string invalid_json = R"({
        "host": "localhost",
        "port": 8080,
        "enable_logging": "true"
    })";

    EXPECT_THROW({
        Config config(invalid_json);
    }, std::runtime_error);
}

// Test port out of range (negative)
TEST(ConfigTest, PortNegative) {
    std::string invalid_json = R"({
        "host": "localhost",
        "port": -1,
        "enable_logging": true
    })";

    EXPECT_THROW({
        Config config(invalid_json);
    }, std::runtime_error);
}

// Test port out of range (too large)
TEST(ConfigTest, PortTooLarge) {
    std::string invalid_json = R"({
        "host": "localhost",
        "port": 65536,
        "enable_logging": true
    })";

    EXPECT_THROW({
        Config config(invalid_json);
    }, std::runtime_error);
}

// Test empty host string
TEST(ConfigTest, EmptyHostString) {
    std::string valid_json = R"({
        "host": "",
        "port": 8080,
        "enable_logging": true
    })";

    EXPECT_NO_THROW({
        Config config(valid_json);
        EXPECT_EQ(config.getHost(), "");
    });
}

// Test malformed JSON
TEST(ConfigTest, MalformedJSON) {
    std::string invalid_json = R"({
        "host": "localhost"
        "port": 8080,
        "enable_logging": true
    })";

    EXPECT_THROW({
        Config config(invalid_json);
    }, std::exception);
}

// Test JSON array instead of object
TEST(ConfigTest, JSONArrayInsteadOfObject) {
    std::string invalid_json = R"([
        "localhost",
        8080,
        true
    ])";

    EXPECT_THROW({
        Config config(invalid_json);
    }, std::runtime_error);
}

// Test extra fields in JSON (should be ignored)
TEST(ConfigTest, ExtraFieldsIgnored) {
    std::string valid_json = R"({
        "host": "localhost",
        "port": 8080,
        "enable_logging": true,
        "extra_field": "ignored",
        "another_field": 12345
    })";

    EXPECT_NO_THROW({
        Config config(valid_json);
        EXPECT_EQ(config.getHost(), "localhost");
        EXPECT_EQ(config.getPort(), 8080);
        EXPECT_TRUE(config.isLoggingEnabled());
    });
}

// Test whitespace in host
TEST(ConfigTest, HostWithWhitespace) {
    std::string valid_json = R"({
        "host": "  localhost  ",
        "port": 8080,
        "enable_logging": true
    })";

    EXPECT_NO_THROW({
        Config config(valid_json);
        EXPECT_EQ(config.getHost(), "  localhost  ");
    });
}

// Test special characters in host
TEST(ConfigTest, HostWithSpecialCharacters) {
    std::string valid_json = R"({
        "host": "server-01.example.com",
        "port": 8080,
        "enable_logging": true
    })";

    EXPECT_NO_THROW({
        Config config(valid_json);
        EXPECT_EQ(config.getHost(), "server-01.example.com");
    });
}

// Test common port values
TEST(ConfigTest, CommonPortValues) {
    std::vector<uint16_t> common_ports = {80, 443, 8000, 8443, 8080, 9000};

    for (uint16_t port : common_ports) {
        std::string json = R"({
            "host": "localhost",
            "port": )" + std::to_string(port) + R"(,
            "enable_logging": true
        })";

        EXPECT_NO_THROW({
            Config config(json);
            EXPECT_EQ(config.getPort(), port);
        });
    }
}
