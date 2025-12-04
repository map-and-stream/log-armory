#include "spd_logger.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "logger.h"
#include "spdlog/common.h"


std::shared_ptr<spdlog::logger> SpdLogger::s_Logger;

SpdLogger::SpdLogger(LogConfig cfg) : ILogger(cfg) {
    // INSERT_YOUR_CODE
    if (cfg.fileName.empty()) {
        s_Logger = spdlog::stdout_color_mt("AppLogger");
    } else {
        switch (cfg.sinkType) {
            case SinkType::NoRotate:
                s_Logger = spdlog::basic_logger_mt("AppLogger", cfg.fileName, true);
                break;

            case SinkType::Daily:
                s_Logger = spdlog::rotating_logger_mt("AppLogger", cfg.fileName, cfg.maxFileSize,
                                                      cfg.maxFiles);
                break;
        }
    }

    s_Logger->set_level(spdlog::level::info);

    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
}

SpdLogger::~SpdLogger() {
    spdlog::drop_all();
}

void SpdLogger::info(const std::string& message) {
    s_Logger->info(message);
}

void SpdLogger::warn(const std::string& message) {
    s_Logger->warn(message);
}

void SpdLogger::error(const std::string& message) {
    s_Logger->error(message);
}

void SpdLogger::setLogLevel(LogLevel level) {
    switch (level) {
        case LogLevel::info:
            spdlog::set_level(spdlog::level::info);
            break;
        case LogLevel::warn:
            spdlog::set_level(spdlog::level::warn);
            break;
        case LogLevel::error:
            spdlog::set_level(spdlog::level::err);
            break;
        default:
            spdlog::set_level(spdlog::level::info);
    }
    currentLogLevel = level;
}