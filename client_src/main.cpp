#include "client.h"

int main(int argc, char* argv[]){
    Client client;

    client.connect(argv[1], argv[2]);

    client.read_petition();

    client.send_petition();
    client.shutdown_writing();
    client.get_server_response();
    return 0;
}
