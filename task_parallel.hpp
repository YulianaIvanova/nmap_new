#ifndef NMAP_PREV_TASK_PARALLEL_HPP
#define NMAP_PREV_TASK_PARALLEL_HPP

#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cmath>
#include <string>
#include <vector>
#include <fcntl.h>
#include <cstring>
#include "tcp_connect.hpp"
using namespace std;
const int PORT_LIMIT = 65535;
#define THREAD_COUNT 100


struct args_for_scan
{
    int start_port;
    int end_port;
    string ip;
};

void *task_scan(void* args);

void tcp_scan_parallel(string ip, int count_ports);

void start_parallel(vector<string>& ip_list, int count_ports);

#endif //NMAP_PREV_TASK_PARALLEL_HPP