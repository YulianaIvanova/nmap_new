#ifndef NMAP_PREV_TCP_CONNECT_HPP
#define NMAP_PREV_TCP_CONNECT_HPP

#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <regex>
#include <fcntl.h>
#include <map>

using namespace std;

int isconnected( int s, fd_set *rd, fd_set *wr, fd_set *ex);

void tcp_connect(const char* ip, const int port);

#endif //NMAP_PREV_TCP_CONNECT_HPP