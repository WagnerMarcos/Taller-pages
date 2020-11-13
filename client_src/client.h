#ifndef CLIENT__T
#define CLIENT__T

#include <string>
#include <sstream>
#include <iostream>
#include "../common_src/socket.h"
class Client{
public:
    void send_petition();
    void read_petition();
    void shutdown_writing();
    void get_server_response();
    void connect(const char *host_name, const char *port);

private:
    std::stringstream petition;
    Socket s;
};

#endif
