#pragma once

#include <cstdint>
#include <string>

namespace service {

/**
 * @brief Runtime configuration loaded from a JSON file.
 *
 * Fields are required and validated during load.
 * Invalid or missing fields result in a std::runtime_error.
 */
struct Config {
    /// Hostname or IP address the service binds to
    std::string host;

    /// TCP port in range [1, 65535]
    uint16_t port;

    /// Enables informational logging when true
    bool enable_logging;

    /**
     * @brief Load configuration from a JSON file.
     *
     * @param path Path to JSON configuration file
     * @return Validated Config instance
     *
     * @throws std::runtime_error on:
     *  - File I/O failure
     *  - JSON parse errors
     *  - Missing required fields
     *  - Invalid field types or values
     */
    static Config load_from_file(const std::string& path);
};

} // namespace service
