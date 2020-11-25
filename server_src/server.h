#ifndef SERVER__T
#define SERVER__T

#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <atomic>
#include "thacceptor.h"
#include "../common_src/socket.h"
#include "thread.h"
#include "threquest.h"
#include "../common_src/resource.h"
#include "protectedResources.h"
class Server{
private:
    ThAcceptor acceptor;
    ProtectedResources resources;
                // Guardo los recursos agregados con POST
                // Comienza con el archivo guardado con /
                // Clave nombre de recurso. Valor es el 
                // buffer con lo que se devuelve al cliente
public:
    Server(const char *service, const std::string& fileName);

            // Solo lee de stdin para dejar de aceptar req
            // Al leer q cierra socket aceptador.
    void readRootFile(std::string fileName);

    void run();
};

#endif
