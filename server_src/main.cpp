#include "server.h"

int main(int argc, char* argv[]){
    try {
        Server server(argv[1], argv[2]);
        server.run();
    } catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }
    return 0;
}
