#include "log.h"

inline std::shared_ptr<ILogger> Log::m_logger = nullptr;

void Log::init() {
    LogConfig cfg_log;
    cfg_log.general_config.fileName = "/var/log/shaham/server.log";
    cfg_log.general_config.logLevel = LogLevel::info;
    cfg_log.rotate_config.type = SinkType::Daily;
    cfg_log.workering_mode.logger_name = "ShahamServer";
    try {
        m_logger = std::make_unique<SpdLogger>(cfg_log);
    } catch (const std::exception& ex) {
        std::cout << "Failed to initialize SpdLogger:" << ex.what();
        // Optionally fallback to a console logger or handle differently
        m_logger = std::make_unique<ConsoleLogger>(cfg_log);
    }
}