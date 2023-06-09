cmake_minimum_required(VERSION 3.24)
project(nmap)

set(CMAKE_CXX_STANDARD 14)

add_executable(nmap main.cpp work_with_ip.hpp work_with_ip.cpp task_parallel.hpp task_parallel.cpp tcp_connect.hpp tcp_connect.cpp timer.hpp)
find_package(Threads REQUIRED)
target_link_libraries(nmap PRIVATE Threads::Threads)