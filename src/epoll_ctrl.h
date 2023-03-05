#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

constexpr int maxEventNum = 1000;
class EpollCtrl
{
public:
    int epoll_fd;
    epoll_event events[maxEventNum];
    int addfd(int fd);
    int delfd(int fd);
    EpollCtrl();
    ~EpollCtrl();
};




