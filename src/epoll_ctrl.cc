#include "epoll_ctrl.h"
#include <iostream>
EpollCtrl::EpollCtrl()
{
    epoll_fd = ::epoll_create(maxEventNum);
    if (epoll_fd == -1) {
        std::cout << "epoll create error" << std::endl;
        exit(-1);
    }
}

int EpollCtrl::addfd(int fd)
{
    epoll_event event;
    event.events = (EPOLLIN|EPOLLET);
    event.data.fd = fd;
    int ret = ::epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
    if (ret < 0) {
        std::cout << "epoll add error" << std::endl;
        // 释放httpData
        return -1;
    }
    return 0;
}

int EpollCtrl::delfd(int fd) {
    epoll_event event;
    event.events = (EPOLLIN|EPOLLET);
    event.data.fd = fd;
    int ret = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &event);
    if (ret < 0) {
        std::cout << "epoll del error" << std::endl;
        return -1;
    }
    return 0;
}