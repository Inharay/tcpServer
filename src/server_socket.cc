#include "server_socket.h"
#include <fcntl.h>
#include <cstring>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <memory>
int setnonblocking(int fd) {
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}

ServerSocket::ServerSocket(int port)
{
    this->port = port;
    listen_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_fd == -1) {
        std::cout << "creat socket error in file <" << __FILE__ << "> "<< "at " << __LINE__ << std::endl;
        exit(0);
    }
    setnonblocking(listen_fd); 
    

}

void ServerSocket::init_socket()
{
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_port = htons(port);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(listen_fd, (const sockaddr *)&serverAddr, sizeof(serverAddr));
}

void ServerSocket::listen()
{
    int ret = ::listen(listen_fd, 1024);
    if (ret == -1) {
        std::cout << "listen error in file <" << __FILE__ << "> "<< "at " << __LINE__ << std::endl;
        exit(0);
    }
    epollCtrl.addfd(listen_fd);
}

int ServerSocket::accept() {

    int clientfd = ::accept(listen_fd, NULL, NULL);
    if (clientfd < 0) {
        if ((errno == EWOULDBLOCK) || (errno == EAGAIN))
            return clientfd;
        std::cout << "accept error in file <" << __FILE__ << "> "<< "at " << __LINE__ << std::endl;
        std::cout << "clientfd:" << clientfd << std::endl;

    }
    epollCtrl.addfd(clientfd);
    return clientfd;
}


ServerSocket::~ServerSocket()
{
    close(listen_fd);
}