#ifndef NMAP_PREV_TCP_CONNECT_H
#define NMAP_PREV_TCP_CONNECT_H

#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <regex>
#include <fcntl.h>


int isconnected( int s, fd_set *rd, fd_set *wr, fd_set *ex);

void tcp_connect(const char* ip, const int port);

#endif //NMAP_PREV_TCP_CONNECT_H