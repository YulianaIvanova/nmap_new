#include <string.h>
#include <regex>
#include <iostream>
#include <valarray>
#include <cstdlib>

using namespace std;

bool ip_validator(const char* ip)
{
    cmatch result;
    regex regular("^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)\\.?\\b){4}(\\/(3[0-2]|[1-2]\\d|\\d)|)$");

    if(regex_match(ip,result, regular))
        return true;
    return false;
}

int get_mask(const string& ip)
{
    if(ip.find('/') < ip.length())
    {
        char buffer[4];
        ip.copy(buffer, 2, ip.find('/')+1);
        return atoi(buffer);
    }
    else
        return -1;
}

int get_ip_part(const string& ip)
{
    char buffer[4];
    ip.copy(buffer, ip.find('.'), 0);
    return atoi(buffer);
}

string create_address(unsigned i) {
    auto value = (1<<8);
    unsigned d = i % value;
    i /= value;
    unsigned c = i % value;
    i /= value;
    unsigned b = i % value;
    i /= value;
    unsigned a = i;
    return to_string(a) + "." + to_string(b) + "." + to_string(c) + "." + to_string(d);
}



void available_addresses(vector<string>& ip_list, const unsigned a, const unsigned b, const unsigned c, const unsigned d, const unsigned mask) {
    unsigned address = (1<<24)*a + (1<<16)*b + (1<<8)*c + d;
    unsigned tail = 1<<(32-mask);
    unsigned network = address/tail*tail;
    unsigned broadcast = (address/tail + 1)*tail - 1;

    for (unsigned i = ++network; i < broadcast; i++) {
        ip_list.push_back(create_address(i));
    }
}


vector<string> calculation_ip(string& ip)
{
    unsigned mask = 0;
    mask = get_mask(ip);
    vector<string> ip_list;

    if(mask == -1)
        ip_list.push_back(ip);
    else
    {
        ip.erase(ip.find('/'), 3);
        unsigned a=0, b=0, c=0, d=0;
        a=get_ip_part(ip);
        ip.erase(0,ip.find('/')+1);

        b=get_ip_part(ip);
        ip.erase(0,ip.find('/')+1);

        c=get_ip_part(ip);
        ip.erase(0,ip.find('/')+1);

        d = stoi(ip);
        available_addresses(ip_list, a, b, c, d, mask);
    }

    return ip_list;
}