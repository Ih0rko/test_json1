#include "service/config.hpp"
#include "service/logger.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    try {
        const std::string config_path =
            argc > 1 ? argv[1] : "config/config.json";

        auto cfg = service::Config::load_from_file(config_path);

        service::Logger::info(
            "Starting service on " + cfg.host + ":" + std::to_string(cfg.port));

        std::cout << "Service running\n";
    } catch (const std::exception& ex) {
        service::Logger::error(ex.what());
        return 1;
    }
}
