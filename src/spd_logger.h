#pragma once

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>

#include <memory>
#include <string>

#include "logger.h"

class SpdLogger : public ILogger {
  public:
    SpdLogger(LogConfig cfg);
    ~SpdLogger();
    void info(const std::string& message) override;
    void warn(const std::string& message) override;
    void error(const std::string& message) override;

    void setLogLevel(LogLevel level) override;

    bool init() { return true; }

  private:
    static std::shared_ptr<spdlog::logger> s_Logger;
};