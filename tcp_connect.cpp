#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <regex>
#include <fcntl.h>

using namespace std;

int isconnected( int _s, fd_set *rd, fd_set *wr, fd_set *ex)
{
    int err;
    socklen_t len = sizeof( err );
    errno = 0; /*предполагаем, что ошибки нет*/
    if( !FD_ISSET( _s, rd ), !FD_ISSET( _s, wr ) )
        return 0;
    if(getsockopt(_s, SOL_SOCKET, SO_ERROR, (void*)(&err), &len) < 0 )
        return 0;
    errno = err; /* если мы не соединились */
    return err == 0;
}


void tcp_connect(const char* ip, const int port)
{
   int _socket;
   do {
       _socket = socket(AF_INET, SOCK_STREAM, 0);
       usleep(100000);

   }while(_socket < 0 && errno == EMFILE);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);


    int flags = fcntl( _socket, F_GETFL, 0 );
    if( flags < 0 )
    {
        close(_socket);
        return; //"Error calling fcntl(F_GETFL)" );
    }

    if( fcntl( _socket, F_SETFL, flags | O_NONBLOCK ) < 0 )
    {
        close(_socket);
        return; //"Error calling fcntl(F_SETFL)"
    }

    int res;
    do{
        res = connect(_socket, (struct sockaddr *)&addr, sizeof(addr));
        usleep(100000);

    }while(res < 0 && errno != EINPROGRESS);// || errno != EADDRNOTAVAIL);



    if( res == 0 ) // вдруг уже не надо ждать
    {
        if( fcntl( _socket, F_SETFL, flags ) < 0 )
        {
            close(_socket);
            return; //"Error calling fcntl (flags recovery)");

        }

        cout<<"PORT "<< port << " IS OPEN"<< endl;
        close(_socket);
        return;
    }

    /* Если ждать надо, ждем с помощью select'а*/
    fd_set rdevents;
    fd_set wrevents;
    fd_set exevents;
    FD_ZERO( &rdevents );
    FD_SET( _socket, &rdevents );
    wrevents = rdevents;
    exevents = rdevents;
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    res = select( _socket + 1, &rdevents, &wrevents, &exevents, &tv );
    if( res < 0 )
    {
        close(_socket);
        return;//"Error calling select"
    }

    else if( res == 0 )
    {
        close(_socket);
        return;// "Connection timeout"
    }

    else if( isconnected( _socket, &rdevents, &wrevents, &exevents ) )
    {
        if( fcntl( _socket, F_SETFL, flags ) < 0 )
        {
            close(_socket);
            return;//"Error calling fcntl (flags recovery)"
        }

        cout << "PORT "<< port << " IS OPEN" << endl;
        close(_socket);
        return;
    }
    else
    {
        close(_socket);
        return;//"Error calling connect";
    }

}