#include "threquest.h"

ThRequest::ThRequest(ProtectedResources& r, Socket socket):
    resources(r),
    s(std::move(socket)),
    is_running(true)
{}

ThRequest::~ThRequest(){
}

void ThRequest::operator()(){
    this->start();
}

void ThRequest::run(){
    try {
        std::stringstream response;
        std::stringstream petition;
        receive_petition(petition);
        process_petition(petition, response);
        send_response(response);
        is_running = false;
        s.shutdown_writing();
    } catch (const std::exception &e){
        std::cerr << "Excepcion en ThRequest.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }
}

bool ThRequest::is_dead(){
    return !is_running;
}

void ThRequest::process_petition(std::stringstream& petition, 
                                std::stringstream& response){
    RequestProcessor requestProcessor(petition, resources);

    response << requestProcessor.getResponse();
}

void ThRequest::send_response(std::stringstream& response){
	s.send(response.str().data(), response.str().length());
}

void ThRequest::receive_petition(std::stringstream& petition){
    char socket_buffer[1024] ={0};
    size_t buffer_size = 1024;
    size_t bytes_received = 0;
    bool socket_open = true;
    while (socket_open){
        s.receive(socket_buffer, buffer_size, bytes_received, socket_open);
        petition << socket_buffer;
    }
}
