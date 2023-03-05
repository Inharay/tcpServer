#pragma once
#include "socket.h"
class server
{
private:
    ServerSocket socket;
public:
    int port;
    server():port(80){};
    ~server();
};

server::server(/* args */)
{
}

server::~server()
{
}
