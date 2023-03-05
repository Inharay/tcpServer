class ClintConn
{
public:
    int fd;
    ClintConn(int fd = -1): fd(fd){};
    ~ClintConn();
};