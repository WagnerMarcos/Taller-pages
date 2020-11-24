#include "requestProcessor.h"

RequestProcessor::RequestProcessor(std::stringstream& petition,
                                    ProtectedResources& resources){
    std::string method;
    std::string resource_name;
    std::string protocol;
    parse_first_petition_line(petition, method, resource_name, protocol);
    setRequestMethod(resources, method, resource_name, protocol, petition);
}

RequestProcessor::~RequestProcessor(){
    delete request;
}

void RequestProcessor::setRequestMethod(ProtectedResources& resources,
                                    std::string& method,
                                    std::string& resource_name,
                                    std::string& protocol,
                                    std::stringstream& petition){
    if (method == "GET")
        request = new RequestGet(resources, 
                                method, 
                                resource_name, 
                                protocol, 
                                petition);
    else if (method == "POST")
        request = new RequestPost(resources, 
                                method, 
                                resource_name, 
                                protocol, 
                                petition);
    else 
        request = new RequestUnknown(method);
}

std::string RequestProcessor::getResponse(){
    return request->getResponse();
}

void RequestProcessor::parse_first_petition_line(std::stringstream& petition,
                                    std::string& method,
                                    std::string& resource_name,
                                    std::string& protocol){
    std::string firstLine;
    getline(petition, firstLine);
    std::istringstream firstLineStream(firstLine);

    firstLineStream >> method >> resource_name >> protocol;
    std::cout << method;
    if (resource_name.length() > 0)
        std::cout << " " + resource_name;  
    if (protocol.length() > 0){
        std::cout << " " + protocol;
        std::cout << std::endl;
    }
}
