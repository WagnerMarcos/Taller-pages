#include "thacceptor.h"

ThAcceptor::ThAcceptor(const char *service,
            ProtectedResources &resources):
    resources(resources)
{
    bind_and_listen(service);
}

int ThAcceptor::accept(){
    int fds = acceptor_socket.accept();
    return fds;
}
void ThAcceptor::operator()(){
    this->run();
}
void ThAcceptor::stop_accepting(){
    keep_accepting = false;
    acceptor_socket.shutdown_read();
    acceptor_socket.shutdown_writing();
    acceptor_socket.close();
}

void ThAcceptor::bind_and_listen(const char *service){
    acceptor_socket.bind_and_listen(service);
}

void ThAcceptor::run(){
    try {
        while (keep_accepting){
            Socket clSocket(accept());
            ThRequest *t = new ThRequest(resources, std::move(clSocket));
            t -> start();
            threads.push_back(t);
            delete_finish_clients(threads);
        }
    } catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }

    for (size_t i = 0; i < threads.size(); i++){
        threads.at(i)->join();    
        delete(threads.at(i));
    }
}

void ThAcceptor::delete_finish_clients(std::vector<ThRequest*>& threads){
    std::vector <ThRequest*> temp;
    std::vector <ThRequest*>::iterator it = threads.begin();
    for (; it != threads.end() ; ++it){
        if ((*it)->is_dead()){
            (*it)->join();
            delete(*it);
        } else {
            temp.push_back(*it);
        }
    }
    threads.swap(temp);
}
