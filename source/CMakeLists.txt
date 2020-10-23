cmake_minimum_required(VERSION 3.16)

project(test_redis)

find_library(redlib  libhiredis.a PATHS /usr/lib/x86_64-linux-gnu)

add_executable(test_redis Main.cpp)

target_link_libraries(test_redis ${redlib})
