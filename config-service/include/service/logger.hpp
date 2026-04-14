#pragma once

#include <string>

namespace service {

/**
 * @brief Minimal process-wide logger.
 *
 * Logging output is enabled or disabled at runtime
 * based on configuration.
 */
class Logger {
public:
    /// Enable or disable informational logging
    static void enable(bool enabled) noexcept;

    /// Emit informational message if enabled
    static void info(const std::string& msg);

    /// Emit error message (always printed)
    static void error(const std::string& msg);
};

} // namespace service
