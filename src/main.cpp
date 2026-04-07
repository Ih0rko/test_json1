#include "Config.h"
#include <iostream>
#include <string>

int main() {
    try {
        // Sample configuration JSON
        std::string config_json = R"({
            "host": "localhost",
            "port": 8080,
            "enable_logging": true
        })";

        std::cout << "=== Configuration Parser ===" << std::endl;
        std::cout << "Parsing configuration..." << std::endl;

        // Parse configuration using Config class
        Config config(config_json);

        // Display parsed configuration
        std::cout << "\nParsed Configuration:" << std::endl;
        std::cout << "  Host: " << config.getHost() << std::endl;
        std::cout << "  Port: " << config.getPort() << std::endl;
        std::cout << "  Logging: " << (config.isLoggingEnabled() ? "Enabled" : "Disabled") << std::endl;

        std::cout << "\n✓ Configuration loaded successfully!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "✗ Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
