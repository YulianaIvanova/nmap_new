#include <iostream>
#include <string>
#include <vector>
#include "tcp_connect.h"

using namespace std;

void start(vector<string> ip_list, const int start_port, const int end_port) {
    for (const string &ip_element: ip_list) {
        cout << "|---- " << ip_element << endl;
        for (int port = start_port; port < end_port; port++) {
            tcp_connect(ip_element.c_str(), port);
        }
    }
}
