#ifndef REQUESTUNKNOWN__T
#define REQUESTUNKNOWN__T

#include "request.h"
#include "protectedResources.h"
#include <string>
#include <sstream>

class RequestUnknown : public Request {
private:
    std::string method;
    std::stringstream response;
    
public:
    explicit RequestUnknown(const std::string& method);
    ~RequestUnknown();
    std::string getResponse() override;
};

#endif
