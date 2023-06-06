cmake_minimum_required(VERSION 3.24)
project(nmap_prev)

set(CMAKE_CXX_STANDARD 14)

add_executable(nmap_prev main.cpp work_with_ip.h work_with_ip.cpp task_parallel.h task_parallel.cpp tcp_connect.h tcp_connect.cpp port_range.h port_range.cpp)
find_package(Threads REQUIRED)
target_link_libraries(nmap_prev PRIVATE Threads::Threads)