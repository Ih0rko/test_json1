#include "Config.h"
#include <boost/json.hpp>
#include <stdexcept>

Config::Config(const std::string& json_str) {
    // Parse JSON
    auto json_value = boost::json::parse(json_str);

    // Validate JSON is an object
    if (!json_value.is_object()) {
        throw std::runtime_error("Configuration must be a JSON object");
    }

    auto json_obj = json_value.as_object();

    // Parse and validate host
    if (!json_obj.contains("host")) {
        throw std::runtime_error("Missing required field: 'host'");
    }
    if (!json_obj.at("host").is_string()) {
        throw std::runtime_error("Field 'host' must be a string");
    }
    host_ = json_obj.at("host").as_string().c_str();

    // Parse and validate port
    if (!json_obj.contains("port")) {
        throw std::runtime_error("Missing required field: 'port'");
    }
    if (!json_obj.at("port").is_int64()) {
        throw std::runtime_error("Field 'port' must be an integer");
    }
    auto port_value = json_obj.at("port").as_int64();
    if (port_value < 0 || port_value > 65535) {
        throw std::runtime_error("Port must be between 0 and 65535");
    }
    port_ = static_cast<uint16_t>(port_value);

    // Parse and validate enable_logging
    if (!json_obj.contains("enable_logging")) {
        throw std::runtime_error("Missing required field: 'enable_logging'");
    }
    if (!json_obj.at("enable_logging").is_bool()) {
        throw std::runtime_error("Field 'enable_logging' must be a boolean");
    }
    enable_logging_ = json_obj.at("enable_logging").as_bool();
}
