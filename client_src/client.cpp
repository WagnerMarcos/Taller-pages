#include "client.h"

void Client::send_petition(){
    // Send through sockets read bytes.
	s.send(petition.str().data(), petition.str().length());
}

void Client::read_petition(){
	std::string line;
	while(getline(std::cin, line)){
    	petition << line << std::endl;
	}
 }

void Client::connect(const char *host_name, const char *port){
	s.connect(host_name, port);
}

void Client::get_server_response(){
	std::stringstream response;
	char socket_buffer[1024] ={0};
    size_t buffer_size = 1024;
    size_t bytes_received = 0;
    bool socket_open = true;
    std::cout << "Espero respuesta, response: " << response.str() << std::endl;

    while(socket_open){
        s.receive(socket_buffer, buffer_size, &bytes_received, &socket_open);
        response << socket_buffer;
    }
	std::cout << response.str() << std::endl;
}

void Client::shutdown_writing(){
	s.shutdown_writing();
}
void Client::receive_response(){
	char socket_buffer[1024] ={0};
    size_t buffer_size = 1024;
    size_t bytes_received = 0;
	// std::stringstream response;
    bool socket_open = true;
    while(socket_open){
        s.receive(socket_buffer, buffer_size, &bytes_received, &socket_open);
        std::cout << socket_buffer;
    }
}
