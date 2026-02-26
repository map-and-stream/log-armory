#include "spd_logger.h"

#include <spdlog/async_logger.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <vector>

#include "logger.h"
#include "spdlog/sinks/hourly_file_sink.h"

std::shared_ptr<spdlog::logger> SpdLogger::s_Logger = nullptr;
std::shared_ptr<spdlog::details::thread_pool> SpdLogger::m_thread_pool = nullptr;

constexpr size_t asyncQueueSize = 10000;

SpdLogger::SpdLogger(LogConfig cfg) : ILogger(cfg) {
    std::vector<spdlog::sink_ptr> sinks;

    // Set spdlog pattern up front, applies globally (not per-sink)
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");

    // Create sinks depending on fileName and rotation type
    if (cfg.general_config.fileName.empty()) {
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    } else {
        switch (cfg.rotate_config.type) {
            case SinkType::Daily:
                sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_mt>(cfg.general_config.fileName, 0, 0));
                break;
            case SinkType::Hourly:
                sinks.push_back(std::make_shared<spdlog::sinks::hourly_file_sink_mt>(cfg.general_config.fileName));
                break;
            case SinkType::Rotating:
                sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                    cfg.general_config.fileName, cfg.rotate_config.max_size, cfg.rotate_config.max_count));
                break;
            default:
                sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(cfg.general_config.fileName, true));
                break;
        }
    }

    // Create the logger (async or sync) as a unique instance (not global static/shared!)
    if (cfg.workering_mode.mode == WorkingMode::ASYNC) {
        if (!m_thread_pool) {
            size_t threads =
                cfg.workering_mode.thread_count > 0 ? static_cast<size_t>(cfg.workering_mode.thread_count) : 1;
            m_thread_pool = std::make_shared<spdlog::details::thread_pool>(asyncQueueSize, threads);
        }
        // generator for unique logger name in case of multi-instance use
        std::string logger_name = cfg.workering_mode.logger_name.empty() ? "SpdLogger" : cfg.workering_mode.logger_name;

        s_Logger = std::make_shared<spdlog::async_logger>(logger_name, sinks.begin(), sinks.end(), m_thread_pool,
                                                          spdlog::async_overflow_policy::block);

        // Don't use register_logger unless you want global registration
        // spdlog::register_logger(s_Logger);
    } else {
        std::string logger_name = cfg.workering_mode.logger_name.empty() ? "SpdLogger" : cfg.workering_mode.logger_name;
        s_Logger = std::make_shared<spdlog::logger>(logger_name, sinks.begin(), sinks.end());

        // spdlog::register_logger(s_Logger);
    }

    // Set logger level according to config
    switch (cfg.general_config.logLevel) {
        case LogLevel::info:
            s_Logger->set_level(spdlog::level::info);
            break;
        case LogLevel::warn:
            s_Logger->set_level(spdlog::level::warn);
            break;
        case LogLevel::error:
            s_Logger->set_level(spdlog::level::err);
            break;
        default:
            s_Logger->set_level(spdlog::level::info);
            break;
    }
    // Optional: flush every log
    s_Logger->flush_on(s_Logger->level());
}

SpdLogger::~SpdLogger() {
    // flush and shutdown spdlog (drops registered loggers and stops async threads)
    spdlog::shutdown();
    s_Logger.reset();
    // keep m_thread_pool intact if you plan to reuse across instances; clear if not needed:
    // m_thread_pool.reset();
}

void SpdLogger::info(const std::string& message) const {
    if (s_Logger)
        s_Logger->info(message);
}

void SpdLogger::warn(const std::string& message) const {
    if (s_Logger)
        s_Logger->warn(message);
}

void SpdLogger::error(const std::string& message) const {
    if (s_Logger)
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
