#include "resource.h"

Resource& Resource::operator=(const Resource& r){
    if (this == &r)
        return *this;
    method = r.method.data();
    path = r.path.data();
    protocol = r.protocol.data();
    body = r.body.data();
    content_length = r.content_length.data();
    return *this;
}

const std::string& Resource::get_body(){
    return body;
}
void Resource::set_method_name(const std::string& m){
    method = m;
}
void Resource::set_resource_path(const std::string& pa){
    path = pa;
}
void Resource::set_protocol(const std::string& p){
    protocol = p;
}
void Resource::set_content_length(const std::string& v){
    content_length = v;
}
void Resource::set_body(std::stringstream& b){
    std::string line;
    while (getline(b, line)){
        if (line.length() > 0)
            body += line + "\n";
    }
}

std::string Resource::get_resource_path(){
    return path;
}
