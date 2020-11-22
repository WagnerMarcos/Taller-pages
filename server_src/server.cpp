#include "server.h"
Server::Server(const char *service, const std::string& fileName):
    acceptor(service, resources)
{
    readRootFile(fileName);
}
void Server::readRootFile(std::string fileName){
    std::ifstream f;
    f.open(fileName);
    Resource r;
    std::stringstream s;
    s << f.rdbuf();
    r.set_resource_path("/");
    r.set_body(s);
    resources.post_resource(r);
}

void Server::run(){
    std::string input;
    bool keep_accepting = true;

    acceptor.start();
    while (keep_accepting){
        std::cin >> input;
        if (input == "q"){
            keep_accepting = false;
            acceptor.stop_accepting();    
        }
    }

    acceptor.join();
}
