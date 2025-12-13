#include "factory.h"
#include "logger.h"

int main() {
    LogConfig cfg;
    cfg.fileName = "logs/app.log";
    cfg.maxFiles = 2;
    cfg.maxFileSize = 2 *1024 *1024 ;
    cfg.logLevel = LogLevel::info;
    cfg.useAsync = true;

    ILogger* l = LoggerFactory::createLogger(LoggerType::Console, cfg);
    l->info("This is an info message.");
    l->warn("This is a warning message.");
    l->error("This is an error message.");

    ILogger* s = LoggerFactory::createLogger(LoggerType::Spdlog, cfg);
    s->info("This is an info message.");
    s->warn("This is a warning message.");
    s->error("This is an error message.");

    // INSERT_YOUR_CODE
    // Attempt to create logger with an invalid type and handle possible failure
    // ILogger* invalidLogger = LoggerFactory::createLogger(static_cast<LoggerType>(-1), cfg);
    // if (!invalidLogger) {
    //     std::cout << "Failed to create logger: invalid logger type." << std::endl;
    // } else {
    //     invalidLogger->info("This should not happen.");
    // }

    return 0;
}
