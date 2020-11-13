#include "protectedResources.h"

void ProtectedResources::post_resource(Resource& r){
	Lock l(m);
	resources[r.get_resource_path()] = r;
}

std::string ProtectedResources::get_body(std::string resource_name){
    Lock l(m);
	std::map<std::string, Resource>::iterator it;
	it = resources.find(resource_name);
    if (it == resources.end())
		return "";
	
	return it->second.get_body();
}
