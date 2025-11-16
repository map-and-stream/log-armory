cmake_minimum_required(VERSION 3.10)
project(log_armory)

set(CMAKE_CXX_STANDARD 20)
set(LIB_ALIAS isiran::log_armory)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)
if(LOG_ARMORY_BUILD_TESTS)
    add_subdirectory(test)
else()
    message("-- LOG_ARMORY_BUILD_TESTS is not set")
endif()
if(LOG_ARMORY_BUILD_EXAMPLE)
    add_subdirectory(example)
else()
    message("-- LOG_ARMORY_BUILD_EXAMPLE is not set")
endif()

