#ifndef REQUESTPROCESSOR__T
#define REQUESTPROCESSOR__T

#include <iostream>
#include <string>
#include <sstream>
#include "protectedResources.h"
#include "request.h"
#include "requestGet.h"
#include "requestPost.h"
#include "requestUnknown.h"

class RequestProcessor {
private:
    Request *request;


    void setRequestMethod(ProtectedResources& resources,
                        std::string& method,
                        std::string& resource_name,
                        std::string& protocol,
                        std::stringstream& petition);
    void parse_first_petition_line(std::stringstream& petition,
                                    std::string& method,
                                    std::string& resource_name,
                                    std::string& protocol);
public:
    RequestProcessor(std::stringstream& petition,
                    ProtectedResources& resources);
    ~RequestProcessor();
    std::string getResponse();
};

#endif 
