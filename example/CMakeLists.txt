project(log_armory_example)

add_executable(${PROJECT_NAME} main.cpp log.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_ALIAS})
