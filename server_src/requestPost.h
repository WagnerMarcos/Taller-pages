#ifndef REQUESTPOST__T
#define REQUESTPOST__T

#include "request.h"
#include "protectedResources.h"
#include <string>
#include <sstream>
class RequestPost : public Request {
private:
    ProtectedResources& resources;
    std::string body;
    std::string method;
    std::string resource_name;
    std::string protocol;
    std::stringstream response;
    
public:
    RequestPost(ProtectedResources& resources,
                std::string& method,
                std::string& resource_name,
                const std::string& protocol,
                std::stringstream& petition);
    ~RequestPost();
    std::string getResponse() override;
    void parse_header(std::stringstream& petition, Resource& r);
    void parse_body(std::stringstream& buf, Resource& r);
    void process(std::stringstream& petition);
};

#endif
