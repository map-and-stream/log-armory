#include "factory.h"
#include "logger.h"

int main() {
    LogConfig cfg;
    cfg.fileName = "logs/app.log";
    cfg.maxFiles = 2;
    cfg.maxFileSize = 2 * 1024 * 1024;
    cfg.logLevel = LogLevel::info;
    cfg.useAsync = true;
    cfg.asyncQueueSize = 10000;
    cfg.asyncThreads = 1;

    ILogger* l = LoggerFactory::createLogger(LoggerType::Console, cfg);
    l->info("This is an info message.");
    l->warn("This is a warning message.");
    l->error("This is an error message.");

    ILogger* s = LoggerFactory::createLogger(LoggerType::Spdlog, cfg);
    s->info("This is an info message.");
    s->warn("This is a warning message.");
    s->error("This is an error message.");

    return 0;
}
