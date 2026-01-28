#include <chrono>
#include <cstdint>
#include <future>
#include <iostream>
#include <string>
#include <thread>

#include "factory.h"
#include "logger.h"

void daily();
void rotating();
void async();

int main() {
    // LogConfig cfg;
    // cfg.fileName = "logs/app.log";
    // cfg.maxFiles = 2;
    // cfg.maxFileSize = 2 * 1024 * 1024;
    // cfg.logLevel = LogLevel::info;

    // cfg.asyncThreads = 1;

    // auto l = LoggerFactory::createLogger(LoggerType::Console, cfg);
    // l->info("This is an info message.");
    // l->warn("This is a warning message.");
    // l->error("This is an error message.");

    // auto s = LoggerFactory::createLogger(LoggerType::Spdlog, cfg);
    // s->info("This is an info message.");
    // s->warn("This is a warning message.");
    // s->error("This is an error message.");

    int a = 0;
    std::cout << "daily : 1 , rotating: 2, async: 3\n";
    std::cin >> a;
    switch (a) {
        case 1:
            daily();
            break;
        case 2:
            rotating();
            break;
        case 3:
            async();
            break;
        default:
            std::cout << "The input value is incorrect.\n";
    }

    return 0;
}

void daily() {
    LogConfig cfg;
    cfg.general_config.fileName = "logs/app.log";
    cfg.rotate_config.max_count = 200;
    cfg.rotate_config.max_size = 1024;
    cfg.general_config.logLevel = LogLevel::info;
    cfg.workering_mode.mode = WorkingMode::SYNC;
    cfg.rotate_config.type = SinkType::Daily;

    auto s = LoggerFactory::createLogger(LoggerType::Spdlog, cfg);
    // uint64_t n = UINT64_MAX;

    while (true) {
        s->info("This is an info message.");
        s->warn("This is a warning message.");
        s->error("This is an error message.");
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        s->info("hello name:{} double:{} int:{} from isiran", "majid", 1.258, 123);
    }
}

void rotating() {
    LogConfig cfg;
    cfg.general_config.fileName = "logs/app.log";
    cfg.rotate_config.max_count = 200;
    cfg.rotate_config.max_size = 1024;
    cfg.general_config.logLevel = LogLevel::info;
    cfg.workering_mode.mode = WorkingMode::SYNC;
    cfg.rotate_config.type = SinkType::Hourly;

    auto s = LoggerFactory::createLogger(LoggerType::Spdlog, cfg);

    while (true) {
        s->info("This is an info message.");
        s->warn("This is a warning message.");
        s->error("This is an error message.");
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void async() {
    LogConfig cfg;
    cfg.general_config.fileName = "logs/app.log";
    cfg.rotate_config.max_count = 200;
    cfg.rotate_config.max_size = 1024 * 1024;
    cfg.general_config.logLevel = LogLevel::info;
    cfg.workering_mode.mode = WorkingMode::ASYNC;
    cfg.rotate_config.type = SinkType::Daily;

    auto s = LoggerFactory::createLogger(LoggerType::Spdlog, cfg);

    uint64_t n = 0;

    while (true) {
        s->info("This is an info message.");
        s->warn("This is a warning message.");
        s->error("This is an error message.");
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << n++ << "\n";
    }
}
