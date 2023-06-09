#ifndef NMAP_PREV_WORK_WITH_IP_HPP
#define NMAP_PREV_WORK_WITH_IP_HPP

#include <string.h>
#include <regex>
#include <iostream>
#include <valarray>
#include <cstdlib>

using namespace std;

bool ip_validator(const char* ip);

int get_mask(const string& ip);

int get_ip_part(const string& ip);

string create_address(unsigned i);

void available_addresses(vector<string>& ip_list,
                         const unsigned a,
                         const unsigned b,
                         const unsigned c,
                         const unsigned d,
                         const unsigned mask);

vector<string> calculation_ip(string& ip);
#endif //NMAP_PREV_WORK_WITH_IP_HPP