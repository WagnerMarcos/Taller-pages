#ifndef THACCEPTOR__T
#define ThACCEPTOR__T

#include "../common_src/socket.h"
#include "../common_src/threquest.h"
#include "../common_src/thread.h"
#include <map>
#include <vector>
#include <utility>
class ThAcceptor : public Thread{
public:
    ThAcceptor(const char *service, 
        ProtectedResources &resources);
    int accept();
    void stop_accepting();
    void process_requests();
    virtual void run() override;
    void operator()();

private:
    Socket acceptor_socket;
    bool keep_accepting = true;
    std::vector<ThRequest*> threads;
    ProtectedResources& resources;      
    void delete_finish_clients(std::vector<ThRequest*> &threads);

    void bind_and_listen(const char *service);
};


#endif
