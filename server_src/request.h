#ifndef REQUEST__T
#define REQUEST__T

#include <sstream>
#include <string>

class Request {
public:
    virtual std::string getResponse() = 0;
    virtual ~Request(){}
};

#endif
