#include "factory.h"
#include "logger.h"
#include <cstdint>
#include <future>
#include <string>
#include <thread>
#include <chrono>


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

    // ILogger* l = LoggerFactory::createLogger(LoggerType::Console, cfg);
    // l->info("This is an info message.");
    // l->warn("This is a warning message.");
    // l->error("This is an error message.");

    // ILogger* s = LoggerFactory::createLogger(LoggerType::Spdlog, cfg);
    // s->info("This is an info message.");
    // s->warn("This is a warning message.");
    // s->error("This is an error message.");






    int a = 0;
    std::cout << "daily : 1 , rotating: 2, async: 3\n";
    std::cin >> a;
    switch(a)
    {
        case 1: daily();
        break;
        case 2: rotating();
        break;
        case 3: async();
        break;
        default:
        std::cout << "The input value is incorrect.\n";
    }

    return 0;
}


void daily()
{
    LogConfig cfg;
    cfg.fileName = "logs/app.log";
    cfg.maxFiles = 20;
    cfg.maxFileSize =  1024;
    cfg.logLevel = LogLevel::info;
    cfg.workerMode = WorkingMode::SYNC;
    cfg.dailyHour = 13;
    cfg.dailyMinute = 10;
    cfg.sinkType = SinkType::Daily;

     ILogger* s = LoggerFactory::createLogger(LoggerType::Spdlog, cfg);
    // uint64_t n = UINT64_MAX;
    
    while(true)
    {
        s->info("This is an info message." );
        s->warn("This is a warning message." );
        s->error("This is an error message." );
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        
    }
}


void rotating()
{
    LogConfig cfg;
    cfg.fileName = "logs/app.log";
    cfg.maxFiles = 200;
    cfg.maxFileSize =  1024;
    cfg.logLevel = LogLevel::info;
    cfg.workerMode = WorkingMode::SYNC;
    cfg.sinkType = SinkType::Rotating;
    

     ILogger* s = LoggerFactory::createLogger(LoggerType::Spdlog, cfg);
    
    
    while(true)
    {
        s->info("This is an info message." );
        s->warn("This is a warning message." );
        s->error("This is an error message." );
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        
    }
}

void async()
{
    LogConfig cfg;
    cfg.fileName = "logs/app.log";
    cfg.maxFiles = 200;
    cfg.maxFileSize = 1024* 1024;
    cfg.logLevel = LogLevel::info;
    cfg.workerMode = WorkingMode::ASYNC;
    cfg.sinkType = SinkType::Rotating;

    

     ILogger* s = LoggerFactory::createLogger(LoggerType::Spdlog, cfg);
    
    uint64_t n = 0;

    while(true)
    {
        s->info("This is an info message." );
        s->warn("This is a warning message." );
        s->error("This is an error message." );
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << n++ << "\n";
        
    }
}



