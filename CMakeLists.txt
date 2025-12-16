cmake_minimum_required(VERSION 3.10)
project(log_armory)

set(CMAKE_CXX_STANDARD 20)
set(LIB_ALIAS isiran::log_armory)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Option to treat warnings as errors
option(WARNINGS_AS_ERRORS "Treat all compiler warnings as errors" ON)

if(WARNINGS_AS_ERRORS)
    message(STATUS "Treating warnings as errors")
    if(MSVC)
        add_compile_options(/W4 /WX)
    else()
        add_compile_options(-Wall -Wextra -Werror)
    endif()
else()
    if(MSVC)
        add_compile_options(/W4)
    else()
        add_compile_options(-Wall -Wextra)
    endif()
endif()

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

