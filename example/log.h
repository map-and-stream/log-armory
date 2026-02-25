#pragma once

#include <iostream>
#include <memory>

#include "factory.h"

class Log {
  public:
    static void init();

    // Get function for the logger
    static std::shared_ptr<ILogger> get() { return m_logger; }

  private:
    static std::shared_ptr<ILogger> m_logger;
};
