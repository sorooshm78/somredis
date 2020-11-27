cmake_minimum_required(VERSION 3.16)

project(somredis)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_library(somredis src/SomRedis.cpp)
target_link_libraries(somredis hiredis)

include_directories(src)

add_executable(simple-main Main.cpp)
target_link_libraries(simple-main hiredis)
target_link_libraries(simple-main somredis)

add_executable(test test/Test.cpp)
target_link_libraries(test gtest)
target_link_libraries(test gtest_main)
target_link_libraries(test somredis)
target_link_libraries(test hiredis)
target_link_libraries(test pthread)

add_executable(performance performance/performance.cpp)
target_link_libraries(performance somredis)
target_link_libraries(performance hiredis)
target_link_libraries(performance pthread)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/memory/memory_leak
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
