cmake_minimum_required(VERSION 3.9)
project(tenhou-wall-reproducer)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)
add_subdirectory(src/openssl-cmake)
add_subdirectory(src/pybind11)
pybind11_add_module(tenhou_wall_reproducer src/tenhou_wall_reproducer.cpp)
target_link_libraries(tenhou_wall_reproducer PRIVATE crypto Threads::Threads)
