#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "epoll_ctrl.h"

class ServerSocket
{
public:
    int port;
    int listen_fd;
    EpollCtrl epollCtrl;
    sockaddr_in serverAddr;
    ServerSocket(int port = 8080);
    void init_socket();
    void listen();
    int accept();
    ~ServerSocket();
};




