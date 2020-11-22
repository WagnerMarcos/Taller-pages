#ifndef PROTECTEDRESOURCES__T
#define PROTECTEDRESOURCES__T

// #include "lock.h"
#include <mutex>
#include "../common_src/resource.h"
#include <map>
#include <string>
class ProtectedResources{
private:
    std::map<std::string, Resource> resources;      
    std::mutex m;    

public:
    ProtectedResources(){}
    ~ProtectedResources(){}
    void post_resource(Resource& r);
    std::string get_body(std::string resource_name);
};

#endif
