#include "spd_logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/async.h>
#include <spdlog/details/thread_pool.h>

std::shared_ptr<spdlog::logger> SpdLogger::s_Logger;
std::shared_ptr<spdlog::details::thread_pool> SpdLogger::m_thread_pool;

SpdLogger::SpdLogger(LogConfig cfg) : ILogger(cfg) 
{
    // set pattern & default level from cfg
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");

    // create sinks based on cfg
    std::vector<spdlog::sink_ptr> sinks;
    if (cfg.fileName.empty()) 
    {
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    } 
    else 
    {
        if (cfg.sinkType == SinkType::Basic) 
        {
            sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(cfg.fileName, true));
        } 
        else if (cfg.sinkType == SinkType::Daily) 
        {
            sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_mt>(cfg.fileName, 0, 0));
        } 
        else 
        { // SinkType::Hourly or default — use rotating as example
            sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
                cfg.fileName, static_cast<size_t>(cfg.maxFileSize), cfg.maxFiles));
        }
    }

    // create logger (sync or async)
    if (cfg.useAsync) 
    {
        // create or reuse thread_pool
        if (!m_thread_pool) 
        {
            m_thread_pool = std::make_shared<spdlog::details::thread_pool>(cfg.asyncQueueSize, cfg.asyncThreads);
        }
        // choose overflow policy
        spdlog::async_overflow_policy policy = spdlog::async_overflow_policy::block;
        if (cfg.asyncOverflowPolicy == 1) policy = spdlog::async_overflow_policy::overrun_oldest;

        // construct async_logger with multiple sinks
        s_Logger = std::make_shared<spdlog::async_logger>(
            "AppLogger",
            sinks.begin(),
            sinks.end(),
            m_thread_pool,
            policy
        );
        spdlog::register_logger(s_Logger);
    } 
    else 
    {
        // sync combined logger
        s_Logger = std::make_shared<spdlog::logger>("AppLogger", sinks.begin(), sinks.end());
        spdlog::register_logger(s_Logger);
    }

    // set level from cfg
    switch (cfg.logLevel) 
    {
        case LogLevel::info: s_Logger->set_level(spdlog::level::info); break;
        case LogLevel::warn: s_Logger->set_level(spdlog::level::warn); break;
        case LogLevel::error: s_Logger->set_level(spdlog::level::err); break;
        default: s_Logger->set_level(spdlog::level::info); break;
    }
    currentLogLevel = cfg.logLevel;
}

SpdLogger::~SpdLogger() {
    // flush and shutdown async threadpool safely
    if (s_Logger) 
    {
        s_Logger->flush();
    }
    spdlog::shutdown(); // drops all loggers and stops async thread pools
    s_Logger.reset();
    m_thread_pool.reset();
}

void SpdLogger::info(const std::string& message)
{
    if (currentLogLevel <= LogLevel::info) s_Logger->info(message);
}

void SpdLogger::warn(const std::string& message) 
{
    if (currentLogLevel <= LogLevel::warn) s_Logger->warn(message);
}

void SpdLogger::error(const std::string& message) 
{
    if (currentLogLevel <= LogLevel::error) s_Logger->error(message);
}

void SpdLogger::setLogLevel(LogLevel level) 
{
    switch (level)
     {
        case LogLevel::info: s_Logger->set_level(spdlog::level::info); break;
        case LogLevel::warn: s_Logger->set_level(spdlog::level::warn); break;
        case LogLevel::error: s_Logger->set_level(spdlog::level::err); break;
        default: s_Logger->set_level(spdlog::level::info); break;
    }
    currentLogLevel = level;
}
