cmake_minimum_required(VERSION 3.16)

project(lib_redis)

add_executable(lib_redis Main.cpp)

target_link_libraries(lib_redis hiredis)

add_library(somredis  implementation.cpp)

target_link_libraries(somredis  hiredis)

target_link_libraries(lib_redis somredis)
