#include "Config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

constexpr const char* DEFAULT_CONFIG_FILE = "config.json";

std::string readJsonFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) {
    try {
        // Determine which config file to use
        std::string config_file = DEFAULT_CONFIG_FILE;
        
        if (argc > 1) {
            config_file = argv[1];
        }

        std::cout << "=== Configuration Parser ===" << std::endl;
        std::cout << "Loading configuration from: " << config_file << std::endl;

        // Read JSON from file
        std::string json_content = readJsonFromFile(config_file);

        // Parse configuration using Config class
        Config config(json_content);

        // Display parsed configuration
        std::cout << "\nParsed Configuration:" << std::endl;
        std::cout << "  Host: " << config.getHost() << std::endl;
        std::cout << "  Port: " << config.getPort() << std::endl;
        std::cout << "  Logging: " << (config.isLoggingEnabled() ? "Enabled" : "Disabled") << std::endl;

        std::cout << "\n✓ Configuration loaded successfully!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "✗ Error: " << e.what() << std::endl;
        std::cerr << "\nUsage: " << argv[0] << " [config_file]" << std::endl;
        std::cerr << "Default config file: " << DEFAULT_CONFIG_FILE << std::endl;
        return 1;
    }

    return 0;
}
