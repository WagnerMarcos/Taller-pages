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
    std::cout << "djejo de aceptar" << std::endl;

}

void ThAcceptor::bind_and_listen(const char *service){
    acceptor_socket.bind_and_listen(service);
}

void ThAcceptor::run(){
   
    while(keep_accepting){
        std::cout << "Espero coneccion:" << std::endl;
        Socket clSocket(accept());
        std::cout << "Acepte uno" << std::endl;
        ThRequest *t = new ThRequest(resources, std::move(clSocket));
        t -> start();
        
        std::cout << "Empece:" << std::endl;
        threads.push_back(t);

        std::cout << "Agregue:" << std::endl;

        delete_finish_clients(threads);
        std::cout << "Borre:" << std::endl;
    }

    for (size_t i = 0; i < threads.size(); i++){
        threads.at(i)->join();    
        delete(threads.at(i));
    }
}

void ThAcceptor::delete_finish_clients(std::vector<ThRequest*>& threads){
    std::vector <ThRequest*> temp;
    std::vector <ThRequest*>::iterator it = threads.begin();
    for(; it != threads.end() ; ++it){
        if((*it)->is_dead()){
            (*it)->join();
            delete(*it);
        } else {
            temp.push_back(*it);
        }
    }
    threads.swap(temp);
}
