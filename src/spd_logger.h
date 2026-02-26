#pragma once

#include <spdlog/async.h>
#include <spdlog/async_logger.h>
#include <spdlog/details/thread_pool.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>

#include <memory>
#include <string>

#include "logger.h"
#include "spdlog/details/thread_pool.h"

class SpdLogger : public ILogger {
  public:
    SpdLogger(LogConfig cfg);
    ~SpdLogger();
    void info(const std::string& message) const override;
    void warn(const std::string& message) const override;
    void error(const std::string& message) const override;

    void setLogLevel(LogLevel level) override;

    bool init() { return true; }

  private:
    static std::shared_ptr<spdlog::logger> s_Logger;
    static std::shared_ptr<spdlog::details::thread_pool> m_thread_pool;
};