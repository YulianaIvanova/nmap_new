#include <iostream>
#include "work_with_ip.hpp"
#include "task_parallel.hpp"
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
        start_parallel(ip_list, 1000);//проверка первой 1000 портов
        return 0;
    }

    string tmp = argv[2];
    if(tmp=="-p-")
    {
        start_parallel(ip_list, PORT_LIMIT);//проверка всех портов
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
        start_parallel(ip_list, right-left); // проверка диапазона портов
    }

    return 0;
}