#ifndef NMAP_PREV_PORT_RANGE_H
#define NMAP_PREV_PORT_RANGE_H
#include <iostream>
#include <string>
#include <vector>
#include "tcp_connect.h"
using namespace std;

void start(vector<string> ip_list, const int start_port, const int end_port);
#endif //NMAP_PREV_PORT_RANGE_H
