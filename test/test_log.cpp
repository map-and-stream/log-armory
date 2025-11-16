#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include "factory.h"


TEST(SampleTest, BasicAssertion) {
    EXPECT_EQ(1 + 1, 2);
}

TEST(LogTest, InfoOutput) {
    LogConfig cfg;
    cfg.logLevel = LogLevel::error;

    ILogger* l = LoggerFactory::createLogger(LoggerType::Console, cfg);
    testing::internal::CaptureStdout();
    l->info("Hello");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("[INFO] Hello"), std::string::npos);
}
