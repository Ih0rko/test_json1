#pragma once

#include <string>
#include <cstdint>
#include <istream>
#include <boost/json.hpp>

class Config {
public:
    /**
     * Constructor that parses JSON from std::istream
     * @param json_stream Stream object to rread JSON from
     * @throws std::exception if file read failed, JSON is invalid or required fields are missing
     */
    explicit Config(std::istream& json_stream);

    /**
     * Constructor that parses JSON from a string
     * @param json_str JSON string containing configuration
     * @throws std::exception if JSON is invalid or required fields are missing
     */
    explicit Config(const std::string& json_str);

    /**
     * Get the host address
     * @return the host string
     */
    [[nodiscard]] const std::string& getHost() const { return host_; }

    /**
     * Get the port number
     * @return the port number
     */
    [[nodiscard]] uint16_t getPort() const { return port_; }

    /**
     * Check if logging is enabled
     * @return true if logging is enabled, false otherwise
     */
    [[nodiscard]] bool isLoggingEnabled() const { return enable_logging_; }

private:
    std::string host_;
    uint16_t port_;
    bool enable_logging_;
};
