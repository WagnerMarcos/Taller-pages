#ifndef THREQUEST__T
#define THREQUEST__T
#include <map>
#include "resource.h"
#include "socket.h"
#include "thread.h"
#include "protectedResources.h"
#include <string>
#include <sstream>
#include <fstream>
#include <utility>
class ThRequest : public Thread{
private:
    ProtectedResources& resources;
    Socket s;
    bool is_running = true;
    
public:
    ThRequest(ProtectedResources& resources, Socket socket);
    ~ThRequest();
    void operator()();
    virtual void run() override;

            // Recibe una peticion por un recurso
            // busca en el recursos map
            // Si no lo encuentra tiene que devolver algun error
    void receive_petition(std::stringstream& petition);

    bool is_dead();
    void process_petition(std::stringstream& buf, std::stringstream& response);
    void print_resources();
    void send_response(std::stringstream& buf);
    void parse_method(std::stringstream& petition, Resource& r);
    void parse_header(std::stringstream& petition, Resource& r);
    void parse_body(std::stringstream& buf, Resource& r);

	void parse_first_petition_line(std::stringstream& petition,
                                        std::string& method,
                                        std::string& resource_name,
                                        std::string& protocol);

	void process_get_method(std::stringstream& petition,
									std::stringstream& response,
                                    std::string& method,
                                    const std::string& resource_name,
                                    std::string& protocol);
	void process_post_method(std::stringstream& petition,
									std::stringstream& response,
                                    const std::string& method,
                                    const std::string& resource_name,
                                    const std::string& protocol);
};

#endif
