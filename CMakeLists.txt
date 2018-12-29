cmake_minimum_required(VERSION 3.10)
project(C-YCSB LANGUAGES CXX)

# This project requires C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "CMAKE_SOURCE_DIR:    " ${CMAKE_SOURCE_DIR})

set(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
message(STATUS "PROJECT_SOURCE_DIR:  " ${PROJECT_SOURCE_DIR})

add_executable(cycsb
    "${PROJECT_SOURCE_DIR}/main.cc"
    "${PROJECT_SOURCE_DIR}/db.cc"
    #"${PROJECT_SOURCE_DIR}/generator/generator.cc"
    )
