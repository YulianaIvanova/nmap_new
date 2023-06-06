#include <iostream>
#include "work_with_ip.h"
#include "task_parallel.h"
#include "port_range.h"
using namespace std;



int main(int argc, char** argv) {

    string ip = argv[1];
    if (!ip_validator(ip.c_str())) {
        cout << "Invalid IP!" << endl;
        return 0;
    }

    vector<string> ip_list = calculation_ip(ip);

    if(argc == 2)
    {
        start(ip_list, 0, 1000);
        return 0;
    }

    string tmp = argv[2];
    if(tmp=="-p-")
    {
        start_parallel(ip_list);
    }
    else if (tmp=="-p")
    {
        if(argc != 4)
        {
            cout << "Port\'s range doesn\'t entered!" << endl;
            return 0;
        }
        string s_line = argv[3];
        char buffer[6];
        s_line.copy(buffer, s_line.find('-'), 0);
        s_line.erase(0, s_line.find('-')+1);
        int left = stoi(buffer);
        int right = stoi(s_line);
        if (left < 0 || right > PORT_LIMIT || left > right)
        {
            cout << "Invalid port\'s range!" << endl;
            return 0;
        }
        start(ip_list, left, right);
        // проверит порты в определенном диапазоне
    }
    else if(tmp=="-f")
    {
        //быстрая проверка портов из списка nmap
    }


    return 0;
}