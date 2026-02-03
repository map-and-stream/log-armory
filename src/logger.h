#pragma once

#include <spdlog/fmt/bundled/format.h>

#include <string>

enum class LogLevel { info, warn, error };
enum class WorkingMode { SYNC, ASYNC };  // write log in main thread or in a separate thread
enum class LoggerType { Console, Spdlog };
enum class SinkType { Rotating, NoRotate, Daily, Hourly, SizeBase };

struct RotateConfig {
    SinkType type = SinkType::Daily;        // hourly-daily,...
    int max_count = 30;                     // -1 => no rotate
    int max_size = 1 * 1000 * 1000 * 1000;  // no limit size
};

struct WorkingModeConfig {
    WorkingMode mode = WorkingMode::SYNC;
    int thread_count = 2;  // sync mode ignore this config
    std::string logger_name = "AppLogger";
};

struct GeneralConfig {
    std::string fileName = "";           // example: "logs/app.log"
    LogLevel logLevel = LogLevel::info;  // Default log level
};

struct LogConfig {
    // std::string filePath = "~/log/";     // Log file name
    // LogLevel logLevel = LogLevel::info;  // Default log level
    // WorkingMode workerMode = WorkingMode::SYNC;  // Default working mode
    GeneralConfig general_config;
    RotateConfig rotate_config;  // How many rotated files to keep (for rotating_file_sink)
    WorkingModeConfig workering_mode;

    // int asyncThreads = 1;

    // int dailyHour = 0;
    // int dailyMinute = 0;
};

// --- Abstract Logger Interface ---
class ILogger {
  public:
    virtual ~ILogger() = default;
    ILogger(LogConfig cfg) : config(cfg) {}

    // Abstract interface for variadic template-based logging supporting formatting and multiple data types

    // Pure virtual methods for non-format string logging (mandatory in concrete logger)
    virtual void info(const std::string& message) = 0;
    virtual void warn(const std::string& message) = 0;
    virtual void error(const std::string& message) = 0;

    // Default variadic template methods for formatting and type-safe logging
    template <typename... Args>
    void info(fmt::format_string<Args...> fmt_str, Args&&... args) {
        this->info(fmt::format(fmt_str, std::forward<Args>(args)...));
    }
    template <typename... Args>
    void warn(fmt::format_string<Args...> fmt_str, Args&&... args) {
        this->warn(fmt::format(fmt_str, std::forward<Args>(args)...));
    }
    template <typename... Args>
    void error(fmt::format_string<Args...> fmt_str, Args&&... args) {
        this->error(fmt::format(fmt_str, std::forward<Args>(args)...));
    }

    virtual void setLogLevel(LogLevel level) = 0;
    virtual LogLevel logLevel() { return currentLogLevel; };

  protected:
    LogLevel currentLogLevel = LogLevel::warn;
    LogConfig config;
};
