#include "requestPost.h"

RequestPost::RequestPost(ProtectedResources& resources,
                        std::string& method,
                        std::string& resource_name,
                        const std::string& protocol,
                        std::stringstream& petition):
    resources(resources),
    method(method),
    resource_name(resource_name),
    protocol(protocol)
{
    process(petition);
}

RequestPost::~RequestPost(){}

void RequestPost::process(std::stringstream& petition){
    if (resource_name == "/"){
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

void RequestPost::parse_header(std::stringstream& petition, Resource& r){
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

void RequestPost::parse_body(std::stringstream& petition, Resource& r){
    r.set_body(petition);
}

std::string RequestPost::getResponse(){
    return response.str();
}
