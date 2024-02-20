cmake_minimum_required(VERSION 3.0.0)
project(cp VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_custom_target(
    format
    COMMAND clang-format -i ${CMAKE_SOURCE_DIR}/ds/*
    COMMAND clang-format -i ${CMAKE_SOURCE_DIR}/math/*
    COMMAND clang-format -i ${CMAKE_SOURCE_DIR}/graph/*
    COMMAND clang-format -i ${CMAKE_SOURCE_DIR}/geometry/*
    COMMAND clang-format -i ${CMAKE_SOURCE_DIR}/misc/*
    COMMAND clang-format -i ${CMAKE_SOURCE_DIR}/string/*
    COMMENT "Formatting code using Clang-Format"
)

