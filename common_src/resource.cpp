#include "resource.h"

Resource& Resource::operator=(const Resource& r){
    method = r.method.data();
    path = r.path.data();
    protocol = r.protocol.data();
    body = r.body.data();
    content_length = r.content_length.data();
    return *this;
}

std::string Resource::get_body(){
    return body;
}
void Resource::set_method_name(std::string m){
    method = m;
}
void Resource::set_resource_path(std::string pa){
    path = pa;
}
void Resource::set_protocol(std::string p){
    protocol = p;
}
void Resource::set_content_length(std::string v){
    content_length = v;
}
void Resource::set_body(std::stringstream& b){
    body = b.str();
}

std::string Resource::get_resource_path(){
    return path;
}
