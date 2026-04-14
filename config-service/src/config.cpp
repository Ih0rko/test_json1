#include "service/config.hpp"
#include "service/logger.hpp"

#include <boost/json.hpp>
#include <boost/json/src.hpp>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace json = boost::json;
namespace service {

namespace {

template <typename T>
T get_required(const json::object& obj, const char* key) {
    if (!obj.contains(key)) {
        throw std::runtime_error(std::string("Missing required field: ") + key);
    }

    try {
        return json::value_to<T>(obj.at(key));
    } catch (const std::exception&) {
        throw std::runtime_error(std::string("Invalid type for field: ") + key);
    }
}

} // namespace

Config Config::load_from_file(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs) {
        throw std::runtime_error("Failed to open config file: " + path);
    }

    std::stringstream buffer;
    buffer << ifs.rdbuf();

    json::value root;
    try {
        root = json::parse(buffer.str());
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("JSON parse error: ") + e.what());
    }

    if (!root.is_object()) {
        throw std::runtime_error("Config root must be a JSON object");
    }

    const auto& obj = root.as_object();

    Config cfg;
    cfg.host = get_required<std::string>(obj, "host");

    int port = get_required<int>(obj, "port");
    if (port <= 0 || port > 65535) {
        throw std::runtime_error("Port out of valid range (1–65535)");
    }
    cfg.port = static_cast<uint16_t>(port);

    cfg.enable_logging = get_required<bool>(obj, "enable_logging");

    Logger::enable(cfg.enable_logging);
    Logger::info("Configuration loaded successfully");

    return cfg;
}

} // namespace service
