#include "server.h"

int main(int argc, char* argv[]){
    Server server;
    try{
        server.run(argv[1], argv[2]);
    }catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
