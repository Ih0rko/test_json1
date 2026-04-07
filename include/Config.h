#pragma once

#include <string>
#include <cstdint>
#include <boost/json.hpp>

class Config {
public:
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

    // Validation helper methods
    
    /**
     * Validates that a field exists in the JSON object
     * @param json_obj The JSON object to check
     * @param field_name The name of the field
     * @throws std::runtime_error if field doesn't exist
     */
    static void validateFieldExists(const boost::json::object& json_obj, const std::string& field_name);

    /**
     * Validates and extracts a string field
     * @param json_obj The JSON object to check
     * @param field_name The name of the field
     * @return The string value of the field
     * @throws std::runtime_error if field doesn't exist or has wrong type
     */
    static std::string validateStringField(const boost::json::object& json_obj, const std::string& field_name);

    /**
     * Validates and extracts an integer field
     * @param json_obj The JSON object to check
     * @param field_name The name of the field
     * @return The integer value of the field
     * @throws std::runtime_error if field doesn't exist or has wrong type
     */
    static int64_t validateIntField(const boost::json::object& json_obj, const std::string& field_name);

    /**
     * Validates and extracts a boolean field
     * @param json_obj The JSON object to check
     * @param field_name The name of the field
     * @return The boolean value of the field
     * @throws std::runtime_error if field doesn't exist or has wrong type
     */
    static bool validateBoolField(const boost::json::object& json_obj, const std::string& field_name);

    /**
     * Validates that a port number is within valid range (0-65535)
     * @param port The port number to validate
     * @throws std::runtime_error if port is out of range
     */
    static void validatePortRange(int64_t port);
};
