#include "protectedResources.h"

void ProtectedResources::post_resource(Resource& r){
	std::lock_guard<std::mutex> l(m);
	resources[r.get_resource_path()] = r;
}
std::string ProtectedResources::get_body(const std::string &resource_name){
    std::lock_guard<std::mutex> l(m);
	std::map<std::string, Resource>::iterator it;
	it = resources.find(resource_name);
    if (it == resources.end())
		return std::move("");
	
	return (it->second.get_body());
}
