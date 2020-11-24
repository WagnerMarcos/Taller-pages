#ifndef REQUESTGET__T
#define REQUESTGET__T

#include "request.h"
#include <string>
#include "protectedResources.h"
class RequestGet : public Request {
private:    
    ProtectedResources& resources;
    std::string body;
    std::string method;
    std::string resource_name;
    std::string protocol;
    std::stringstream response;
    
public:
    RequestGet(ProtectedResources& resources,
            std::string& method,
            std::string& resource_name,
            const std::string& protocol,
            std::stringstream& petition);
    ~RequestGet();

    void process(std::stringstream& petition);
    std::string getResponse() override;
};

#endif
