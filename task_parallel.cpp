#include <iostream>
#include <sys/socket.h>
#include <string>
#include <vector>
#include <cstring>
#include "tcp_connect.hpp"
#include "timer.hpp"

using namespace std;
const int PORT_LIMIT = 65535;
#define THREAD_COUNT 100


struct args_for_scan
{
    int start_port;
    int end_port;
    string ip;
};

void *task_scan(void* args) {
    args_for_scan *args_scan = (args_for_scan *) args;
    string ip = args_scan->ip;
    for (int port = args_scan->start_port; port < args_scan->end_port; port++) {
        tcp_connect(ip.c_str(), port);
    }
    delete args_scan;
}

void tcp_scan_parallel(string ip, int count_ports)
{
    pthread_t threads[THREAD_COUNT];
    int chunk_size = count_ports/THREAD_COUNT;
    for (int i=0; i<THREAD_COUNT; i++)
    {
        args_for_scan *args_scan = new args_for_scan();
        args_scan->start_port = i*chunk_size;
        args_scan->end_port = (i+1)*chunk_size;
        args_scan->ip = ip;
        if (i == THREAD_COUNT - 1)
            args_scan->end_port = count_ports;
        pthread_create(&threads[i], 0, task_scan, args_scan);
    }

    for (int i=0; i<THREAD_COUNT; i++)
        pthread_join(threads[i], NULL);
}

void start_parallel(vector<string>& ip_list, int count_ports) {
    scope_timer t{"TCP scanning"};
    for (const string &ip_element: ip_list) {
        cout << "|---- " << ip_element << endl;
        tcp_scan_parallel(ip_element, count_ports);
    }
}