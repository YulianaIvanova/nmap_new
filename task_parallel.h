#ifndef NMAP_PREV_TASK_PARALLEL_H
#define NMAP_PREV_TASK_PARALLEL_H

#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cmath>
#include <string>
#include <vector>
#include <fcntl.h>
#include <cstring>
#include "tcp_connect.h"
using namespace std;
const int PORT_LIMIT = 65535;
#define THREAD_COUNT 15


struct ArgMultiply
{
    int start_port;
    int end_port;
    string ip;
};

void *TaskMultiply(void* args);

void MultiplyParallel(string ip);

void start_parallel(vector<string>& ip_list);

#endif //NMAP_PREV_TASK_PARALLEL_H