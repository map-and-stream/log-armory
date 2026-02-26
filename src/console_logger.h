#pragma once

#include <string>

#include "logger.h"

class ConsoleLogger : public ILogger {
  public:
    ConsoleLogger(LogConfig cfg);
    ~ConsoleLogger();

    void info(const std::string& message) const override;
    void warn(const std::string& message) const override;
    void error(const std::string& message) const override;

    virtual void setLogLevel(LogLevel level);
    virtual LogLevel logLevel() { return currentLogLevel; };
};
