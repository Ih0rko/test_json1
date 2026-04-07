#include "Config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

constexpr const char* DEFAULT_CONFIG_FILE = "config.json";

int main(int argc, char* argv[]) {
    try {
        // Determine which config file to use
        std::string config_file = argc > 1 ? argv[1] : DEFAULT_CONFIG_FILE;
        
        std::cout << "Loading configuration from: " << config_file << std::endl;
        std::ifstream json_stream{config_file};

        if (!json_stream.is_open()) {
            throw std::runtime_error("Failed to open file " + config_file);
        }

        Config config{json_stream};

        std::cout << "Result:" << std::endl
            << "  Host: " << config.getHost() << std::endl
            << "  Port: " << config.getPort() << std::endl
            << "  Logging: " << std::boolalpha << config.isLoggingEnabled() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl
            << "Usage: " << argv[0] << " [config_file]" << std::endl
            << "Default config file: " << DEFAULT_CONFIG_FILE << std::endl;
        return 1;
    }

    return 0;
}
