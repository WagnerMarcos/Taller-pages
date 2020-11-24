#include "requestUnknown.h"

RequestUnknown::RequestUnknown(const std::string& method){        
    response << "HTTP/1.1 405 METHOD NOT ALLOWED\n\n" << method 
            << " es un comando desconocido\n";
}

RequestUnknown::~RequestUnknown(){}

std::string RequestUnknown::getResponse(){
    return response.str();
}
