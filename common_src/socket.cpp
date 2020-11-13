#include "socket.h"

Socket::Socket(){
    fd = -1;
}
Socket::~Socket(){
    if (fd != -1)
        close();
    fd = -1;
}
Socket::Socket(Socket&& socket): fd(socket.fd) {
    socket.fd = -1;
}
Socket::Socket(int fd): fd(fd) {}

void Socket::shutdown_read(){
    shutdown(fd, SHUT_RD);
}
void Socket::shutdown_writing(){
    shutdown(fd, SHUT_WR);
}

void Socket::close(){
    ::close(fd);
}

int Socket::bind_and_listen(const char *service){
    struct addrinfo hints, *results, *rp;
    int status = 0;
    hints.ai_family = AF_INET;    
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE;
    int val = 1;

    status = getaddrinfo(0, service, &hints, &results);  
    if (status != 0) { 
        return ERROR;
    }
    for (rp = results; rp != NULL; rp = rp->ai_next){
        fd = ::socket(AF_INET, SOCK_STREAM, 0);
        int s = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
        if (s == -1) {
            close();
            return 1;
        }
        if (bind(fd, rp->ai_addr, rp->ai_addrlen) == 0){
            break;               
        }
        close();
    }
    freeaddrinfo(results); // libero lista de direcciones
    if (listen(fd, 10) == -1){ 
        close();
        return ERROR;
    }
    return 0;
}


// Averiguar si sería mejor 
// devolver fd
// pasar por referencia un socket invalido
int Socket::accept(){
    int accepted_fd = 0;
    accepted_fd = ::accept(fd, NULL, NULL);
    if (accepted_fd == -1){
        return -1;
    }
    return accepted_fd;
}

int Socket::connect(const char *host_name, const char *service){
    struct addrinfo hints, *result, *rp;
    int skt = 0;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;    
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_protocol = 0;
    hints.ai_flags = 0;
    skt = getaddrinfo(host_name, service, &hints, &result);

    if (skt != 0) {
        close();
        return ERROR;
    }
    for (rp = result; rp != NULL; rp = rp->ai_next){
        fd = ::socket(AF_INET, SOCK_STREAM, 0);
        if (::connect(fd, rp->ai_addr, rp->ai_addrlen) == 0){      
            break; 
        }  
        close();
    }
    if (rp == NULL){              
        return ERROR;
    }
    freeaddrinfo(result); 
    return 0;          
}

int Socket::send(const char *buffer, size_t buf_l){
    size_t bytes_sent;
    bytes_sent = 0;

    while (bytes_sent < buf_l){
        int s = 0;
        s = ::send(fd, &buffer[bytes_sent], buf_l - bytes_sent, MSG_NOSIGNAL);
        if (s <= 0){ 
            return ERROR;
        }
        bytes_sent += s;
    }

    return 0;
}
 
int Socket::receive(char *buffer, size_t buf_l, 
                size_t *bytes_recv, bool *sckt_open){
    *bytes_recv = 0;

    while (*bytes_recv < buf_l && *sckt_open == true){
        int r = 0;
        r = ::recv(fd, &buffer[*bytes_recv], buf_l - *bytes_recv, 0);
        if (r < 0){
            *sckt_open = false;
            return ERROR;
        }else if (r == 0){
            *sckt_open = false;
        }else{
            *bytes_recv += r;
        }
    }
    return 0;
}
