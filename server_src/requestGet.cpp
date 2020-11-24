#include "requestGet.h"

RequestGet::RequestGet(ProtectedResources& resources,
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

RequestGet::~RequestGet(){}

void RequestGet::process(std::stringstream& petition){
    std::string body;
    resources.get_body(resource_name, body);
 
    if (resource_name == "/"){
        response << "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
        response << body;
        return;
    } else {
        response << "​HTTP/1.1 200 OK\n\n";
        response << body;
    }
}

std::string RequestGet::getResponse(){
    return response.str();
}
