#include "console_logger.h"

#include <iostream>

#include "logger.h"


ConsoleLogger::ConsoleLogger(LogConfig cfg) : ILogger(cfg) {
    currentLogLevel = cfg.general_config.logLevel;
}

ConsoleLogger::~ConsoleLogger() {}

void ConsoleLogger::setLogLevel(LogLevel level) {
    currentLogLevel = level;
}

void ConsoleLogger::info(const std::string& message) const {
    if (currentLogLevel == LogLevel::info) {
        std::cout << "[INFO] " << message << std::endl;
    }
}
void ConsoleLogger::warn(const std::string& message) const {
    if ((currentLogLevel == LogLevel::info) || (currentLogLevel == LogLevel::warn)) {
        std::cout << "[WARN] " << message << std::endl;
    }
}
void ConsoleLogger::error(const std::string& message) const {
    if ((currentLogLevel == LogLevel::info) || (currentLogLevel == LogLevel::warn) ||
        (currentLogLevel == LogLevel::error)) {
        std::cerr << "[ERROR] " << message << std::endl;
    }
}
