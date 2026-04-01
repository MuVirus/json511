cmake_minimum_required(VERSION 3.10)

project(json511 VERSION 1.0.0 LANGUAGES CXX)

add_library(json511 json511.cpp)

target_include_directories(json511 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(json511 PRIVATE -std=c++11 -O2 -fno-exceptions -fno-rtti -Wall -Wextra -Wpedantic)

install(TARGETS json511 DESTINATION lib)
install(FILES json511.hpp DESTINATION include)