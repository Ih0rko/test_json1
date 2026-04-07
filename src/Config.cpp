#include "Config.h"
#include <boost/json.hpp>
#include <stdexcept>

void Config::validateFieldExists(const boost::json::object& json_obj, const std::string& field_name) {
    if (!json_obj.contains(field_name)) {
        throw std::runtime_error("Missing required field: '" + field_name + "'");
    }
}

std::string Config::validateStringField(const boost::json::object& json_obj, const std::string& field_name) {
    validateFieldExists(json_obj, field_name);
    
    const auto& value = json_obj.at(field_name);
    if (!value.is_string()) {
        throw std::runtime_error("Field '" + field_name + "' must be a string");
    }
    
    return value.as_string().c_str();
}

int64_t Config::validateIntField(const boost::json::object& json_obj, const std::string& field_name) {
    validateFieldExists(json_obj, field_name);
    
    const auto& value = json_obj.at(field_name);
    if (!value.is_int64()) {
        throw std::runtime_error("Field '" + field_name + "' must be an integer");
    }
    
    return value.as_int64();
}

bool Config::validateBoolField(const boost::json::object& json_obj, const std::string& field_name) {
    validateFieldExists(json_obj, field_name);
    
    const auto& value = json_obj.at(field_name);
    if (!value.is_bool()) {
        throw std::runtime_error("Field '" + field_name + "' must be a boolean");
    }
    
    return value.as_bool();
}

void Config::validatePortRange(int64_t port) {
    if (port < 0 || port > 65535) {
        throw std::runtime_error("Port must be between 0 and 65535");
    }
}

Config::Config(const std::string& json_str) {
    // Parse JSON
    auto json_value = boost::json::parse(json_str);

    // Validate JSON is an object
    if (!json_value.is_object()) {
        throw std::runtime_error("Configuration must be a JSON object");
    }

    auto json_obj = json_value.as_object();

    // Parse and validate host
    host_ = validateStringField(json_obj, "host");

    // Parse and validate port
    auto port_value = validateIntField(json_obj, "port");
    validatePortRange(port_value);
    port_ = static_cast<uint16_t>(port_value);

    // Parse and validate enable_logging
    enable_logging_ = validateBoolField(json_obj, "enable_logging");
}
