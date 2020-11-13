#ifndef SOCKET__T
#define SOCKET__T


#define ERROR 1

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <errno.h>
class Socket{
public:
    Socket();
    ~Socket();
    Socket(Socket&& socket);
    explicit Socket(int fd);
    // int socket_init();
    void shutdown_read();
    void shutdown_writing();
    void close();
    int bind_and_listen(const char *service);
    int accept();
    int connect(const char *host_name, const char *service);
    int send(const char *buffer, size_t buf_l);
    int receive(char *buffer, size_t buf_l, 
            size_t *bytes_recv, bool *sckt_open);
private:
    int fd;
};

#endif
