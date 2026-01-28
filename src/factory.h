#pragma once

#include "logger.h"
#include "console_logger.h"
#include "spd_logger.h"
#include <string.h>
#include <memory>



class LoggerFactory {
public:
    static std::unique_ptr<ILogger> createLogger(LoggerType type, LogConfig cfg) {
        if (type == LoggerType::Console) {
            return std::make_unique<ConsoleLogger>(cfg);
        }
        else if (type == LoggerType::Spdlog) {
            auto spd = std::make_unique<SpdLogger>(cfg);//TODO: using smart pointer
            spd->init();
            return spd;
        }
        else {
            throw std::invalid_argument("Invalid logger type");
        }
    }
};