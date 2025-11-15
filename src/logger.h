#pragma once

#include <iostream>
#include <string>

enum class LogLevel {
    info,
    warn,
    error
};

enum class LoggerType {
    Console,
    Spdlog
};
enum class SinkType {
    Basic,
    Daily,
    Hourly
};
struct LogConfig {
    std::string filePath; 
    int maxLogRotate; //per days
    LogLevel logLevel;
    std::string fileName = "log.txt";
    std::string logRegexPattern;
    std::string logDateFormat;
    int maxRotateDays = 7;
    int maxRotateHours = 168;
    SinkType sinkType = SinkType::Basic;

    LogConfig() {
        switch (sinkType) {
            case SinkType::Daily:
                logRegexPattern = R"(log\.txt\.(\d{4}-\d{2}-\d{2}))";
                logDateFormat = "%Y-%m-%d";
                break;
            case SinkType::Hourly:
                logRegexPattern = R"(log\.txt\.(\d{4}-\d{2}-\d{2}_\d{2}))";
                logDateFormat = "%Y-%m-%d_%H";
                break;
            case SinkType::Basic:
            default:
                logRegexPattern = "";
                logDateFormat = "";
                break;
        }
    }
};

// --- Abstract Logger Interface ---
class ILogger {
public:
    virtual ~ILogger() = default;
    ILogger(LogConfig cfg){}

    virtual void info(const std::string& message) = 0;
    virtual void warn(const std::string& message) = 0;
    virtual void error(const std::string& message) = 0;

    virtual void setLogLevel(LogLevel level) = 0;
    virtual LogLevel logLevel() {return currentLogLevel;};
protected:
    LogLevel currentLogLevel = LogLevel::warn;
};



// --- Example Usage ---
// int main() {
//     ConsoleLogger logger;

//     logger.Info("Application started.");
//     logger.Warn("Low disk space.");
//     logger.Error("Failed to open file.");

//     return 0;
// }
