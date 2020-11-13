#include "threquest.h"

ThRequest::ThRequest(ProtectedResources& r, Socket socket):
    resources(r),
    s(std::move(socket))
{}

ThRequest::~ThRequest(){
}

void ThRequest::run(){
    std::stringstream response;
    std::stringstream petition;
    receive_petition(petition);
    process_petition(petition, response);
    send_response(response);
    is_running = false;
    s.shutdown_writing();
}

bool ThRequest::is_dead(){
    return !is_running;
}

void ThRequest::process_petition(std::stringstream& petition, 
                                std::stringstream& response){
    Resource r;
    std::string method;
    std::string path;
    std::string protocol;

    parse_first_petition_line(petition, method, path, protocol);
    
    if (method == "GET")
        process_get_method(petition, response, method, path, protocol);
    
    else if (method == "POST")
        process_post_method(petition, response, method, path, protocol);

    else 
        response << "HTTP/1.1 405 NOT ALLOWED\n\n" << method << " es un comando desconocido\n";
}

void ThRequest::process_get_method(std::stringstream& petition,
                                std::stringstream& response,
                                std::string& method,
                                const std::string& resource_name,
                                std::string& protocol){
    std::string body = resources.get_body(resource_name);
    if (body.length() == 0){
        response << "HTTP/1.1 404 NOT FOUND\n\n";
        return; 
    }

    
    if (resource_name == "/"){
        response << "​HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
        response << body;
    } else {
        response << "​HTTP/1.1 200 OK\n\n";
        response << body;
    }
}

void ThRequest::process_post_method(std::stringstream& petition,
                                std::stringstream& response,
                                const std::string& method,
                                const std::string& resource_name,
                                const std::string& protocol){
    if (method == "/"){
        response << "HTTP/1.1 403 FORBIDDEN\n\n";
        return;
    }
    Resource r;
    r.set_method_name(method);
    r.set_resource_path(resource_name);
    r.set_protocol(protocol);

    parse_header(petition, r);

    if (petition.str().length() == 0){
        response << "HTTP/1.1 403 FORBIDDEN\n\n";
        return;
    }

    parse_body(petition, r);
    resources.post_resource(r);

    response << "HTTP/1.1 200 OK\n\n" << r.get_body();
}

void ThRequest::parse_first_petition_line(std::stringstream& petition,
                                    std::string& method,
                                    std::string& resource_name,
                                    std::string& protocol){
    std::string firstLine;
    getline(petition, firstLine);
    std::istringstream firstLineStream(firstLine);

    firstLineStream >> method >> resource_name >> protocol;
    std::cout << method + " " + resource_name + " " + protocol << std::endl;
}

void ThRequest::parse_header(std::stringstream& petition, Resource& r){
    std::string key, value;
    std::string line;

    while (getline(petition, line)){
        if (line.length() == 0){
            break;
        }
        std::istringstream header_line(line);
        header_line >>  key >> value;
        if (key == "Content-Length:"){
            r.set_content_length(value);
        }
    }
}

void ThRequest::parse_body(std::stringstream& petition, Resource& r){
    r.set_body(petition);
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
        s.receive(socket_buffer, buffer_size, &bytes_received, &socket_open);
        petition << socket_buffer;
    }
}
