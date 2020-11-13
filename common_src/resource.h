#ifndef RESOURCE__T
#define RESOURCE__T

#include <string>
#include <sstream>
#include <iostream>
class Resource{
public:
    Resource(){}
    ~Resource(){}

        // Busca el recurso a partir de su nombre.
    std::istringstream getResource(std::string);
    std::string get_resource_path();
    void set_method_name(const std::string method);
    void set_resource_path(const std::string path);
    void set_protocol(const std::string protocol);

    void set_content_length(const std::string value);
    void set_body(std::stringstream& buf);
	std::string get_body();
    void print();
    Resource& operator=(const Resource& r);
private:
    std::string method;
    std::string path;
    std::string protocol;
    std::string body;
    std::string content_length;
};

#endif
