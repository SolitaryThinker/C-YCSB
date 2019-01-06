cmake_minimum_required(VERSION 3.10)
project(C-YCSB LANGUAGES CXX)

# This project requires C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Setup the options that CMake can take in
option(PEBBLESDB "Compile in PebblesDB's client and library" OFF)

message(STATUS "CMAKE_SOURCE_DIR:    " ${CMAKE_SOURCE_DIR})

set(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
message(STATUS "PROJECT_SOURCE_DIR:  " ${PROJECT_SOURCE_DIR})

include_directories(
    "${PROJECT_SOURCE_DIR}"
)

add_subdirectory("${PROJECT_SOURCE_DIR}/clients/pebblesdb")

add_executable(cycsb
    "${PROJECT_SOURCE_DIR}/cycsb.cc"

    "${PROJECT_SOURCE_DIR}/core/db_factory.cc"
    "${PROJECT_SOURCE_DIR}/core/workload.cc"
    "${PROJECT_SOURCE_DIR}/core/workload_factory.cc"

    "${PROJECT_SOURCE_DIR}/generator/zipfian_generator.cc"

    "${PROJECT_SOURCE_DIR}/util/status.cc"

    "${PROJECT_SOURCE_DIR}/workloads/core_workload.cc"
)

target_link_libraries(cycsb pebblesdb)
