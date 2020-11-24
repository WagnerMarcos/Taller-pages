#ifndef THREQUEST__T
#define THREQUEST__T
#include <map>
#include "../common_src/resource.h"
#include "../common_src/socket.h"
#include "thread.h"
#include "protectedResources.h"
#include <string>
#include <sstream>
#include <fstream>
#include <utility>
#include <atomic>
#include "requestProcessor.h"

class ThRequest : public Thread{
private:
    ProtectedResources& resources;
    Socket s;
    std::atomic<bool> is_running;
    
public:
    ThRequest(ProtectedResources& resources, Socket socket);
    ~ThRequest();
    void operator()();
    virtual void run() override;

            // Recibe una peticion por un recurso
            // busca en el recursos map
            // Si no lo encuentra tiene que devolver algun error

    bool is_dead();
    void process_petition(std::stringstream& buf, std::stringstream& response);
    void receive_petition(std::stringstream& petition);
    void send_response(std::stringstream& buf);
    void parse_method(std::stringstream& petition, Resource& r);
};

#endif
