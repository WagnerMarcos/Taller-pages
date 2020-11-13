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
#include "../common_src/thread.h"
#include "../common_src/threquest.h"
#include "../common_src/resource.h"
#include "../common_src/protectedResources.h"
class Server{
private:
    // Metodos conocidos por el servidor
    // std::string allowedMethods[2] = {"GET",
    //                                     "POST"};
    ProtectedResources resources;
                // Guardo los recursos agregados con POST
                // Comienza con el archivo guardado con /
                // Clave nombre de recurso. Valor es el 
                // buffer con lo que se devuelve al cliente
public:
            // Solo lee de stdin para dejar de aceptar req
            // Al leer q cierra socket aceptador.
    void readRootFile(std::string fileName);

    void run(const char *service, const std::string fileName);
};

#endif
