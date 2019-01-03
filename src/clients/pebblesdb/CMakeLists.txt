project(pebblesdb)

add_library(pebblesdb
    pebblesdb_client.cc
)

find_library(PEBBLESDB_LIB pebblesdb)
message(STATUS "PebblesDB Lib: " ${PEBBLESDB_LIB})

target_link_libraries(pebblesdb ${PEBBLESDB_LIB})
