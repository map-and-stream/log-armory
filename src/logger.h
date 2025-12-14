#pragma once

#include <iostream>
#include <string>

enum class LogLevel { info, warn, error };
enum class WorkingMode { SYNC, ASYNC };  // write log in main thread or in a separate thread
enum class LoggerType { Console, Spdlog };
enum class SinkType { NoRotate, Daily };

struct LogConfig {
    std::string fileName;                        // Log file name
    LogLevel logLevel = LogLevel::info;          // Default log level
    WorkingMode workerMode = WorkingMode::SYNC;  // Default working mode
    SinkType sinkType = SinkType::NoRotate;      // NoRotate = no rotation, Daily/Hourly for rotation types
    int maxFileSize = 5 * 1024 * 1024;           // 5 MB default, used with rotating_file_sink
    int maxFiles = 3;                            // How many rotated files to keep (for rotating_file_sink)

    bool useAsync = false;
    int asyncThreads = 1;
};

// --- Abstract Logger Interface ---
class ILogger {
  public:
    virtual ~ILogger() = default;
    ILogger(LogConfig cfg) {}

    virtual void info(const std::string& message) = 0;
    virtual void warn(const std::string& message) = 0;
    virtual void error(const std::string& message) = 0;

    virtual void setLogLevel(LogLevel level) = 0;
    virtual LogLevel logLevel() { return currentLogLevel; };

  protected:
    LogLevel currentLogLevel = LogLevel::warn;
};
