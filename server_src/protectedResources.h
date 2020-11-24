#ifndef PROTECTEDRESOURCES__T
#define PROTECTEDRESOURCES__T

#include <mutex>
#include "../common_src/resource.h"
#include <map>
#include <string>
#include <utility>
class ProtectedResources{
private:
    std::map<std::string, Resource> resources;      
    std::mutex m;    

public:
    ProtectedResources(){}
    ~ProtectedResources(){}
    void post_resource(Resource& r);
    void get_body(const std::string &resource_name, std::string& body);
};

#endif
