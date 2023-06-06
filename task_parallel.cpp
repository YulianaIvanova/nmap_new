#include <iostream>
#include <sys/socket.h>
#include <string>
#include <vector>
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

void *TaskMultiply(void* args) {
    ArgMultiply *argMultiply = (ArgMultiply *) args;
    string ip = argMultiply->ip;
    for (int port = argMultiply->start_port; port < argMultiply->end_port; port++) {
        tcp_connect(ip.c_str(), port);
    }
    //cout<<"Check port: "<<  argMultiply->end_port <<endl;
}

void MultiplyParallel(string ip)
{
    pthread_t threads[THREAD_COUNT];
    int chunk_size = PORT_LIMIT/THREAD_COUNT;
    for (int i=0; i<THREAD_COUNT; i++)
    {
        ArgMultiply *argMultiply = new ArgMultiply();
        argMultiply->start_port = i*chunk_size;
        argMultiply->end_port = (i+1)*chunk_size;
        argMultiply->ip = ip;
        pthread_create(&threads[i], 0, TaskMultiply, argMultiply);

    }

    for (int i=0; i<THREAD_COUNT; i++)
        pthread_join(threads[i], NULL);
}

void start_parallel(vector<string> ip_list) {
    for (const string &ip_element: ip_list) {
        cout << "|---- " << ip_element << endl;
        MultiplyParallel(ip_element);
        //cout<< "Close port: " << CLOSEPORT<<endl;
    }
}