cmake_minimum_required(VERSION 3.16)

project(lib_hiredis)

add_executable(lib_hiredis Main.cpp)

target_link_libraries(lib_hiredis hiredis)

add_library(implement  implementation.cpp)

target_link_libraries(implement  hiredis)

target_link_libraries(lib_hiredis implement)
