# Ejercicio 3

    Alumno: Wagner Marcos
    Padrón: 98607
    github: https://github.com/WagnerMarcos/Taller-pages


## Introducción:

En este trabajo se desarrollará una aplicación servidor que atenderá petitorios HTTP, mediante los cuales podrá acceder y
dar alta a recursos del mismo.

## Estructura:

Se utilizó para el trabajo un servidor que engloba la resolución de petitorios. Contiene una clase aceptadora de clientes y un registro de petitorios disponibles.
El servidor procesa a cada cliente a través de un hilo separado lanzado por la clase aceptadora. Los hilos son guardados en un vector de hilos, y cada vez que un cliente sea aceptado, se consultará a los hilos guardados si alguno ya finalizó su ejecución para ser destruido.
Hay tres tipos de procesos corriendo en simultáneo durante la ejecución del programa. 
    El hilo principal es quien lanza al hilo de clase aceptadora para que solo se encargue de tratar con los clientes que desean conectarse. Luego de lanzar este hilo, se quedará esperando que el usuario ingrese la tecla 'q' para dejar de aceptar nuevos clientes cerrando el socket aceptador. 
    El hilo aceptador corre sobre la clase aceptadora y es la encargada de lanzar nuevos hilos por cada cliente que quiera realizar un petitorio. Al ser ser informada que no debe seguir aceptando, cierra su socket y espera para realizar la destrucción de los hilos que lanzó para cada cliente.
    Los hilos de clientes tratan cada uno un petitorio realizado por un cliente. Reciben por socket lo enviado por el cliente, y consulta en el registro de petitorios para cumplir con lo pedido. Se encarga de recibir, parsear, y almacenar/recuperar lo pedido, para luego enviar una respuesta al cliente. Al ser varios clientes que consultan, almacenan y recuperan información de un mismo registro, se detectó a este registro como zona crítica donde puede darse una race condition.
Para tratar con el problema de la race condition en el registro de petitorios se implimentó una clase Lock dentro del registro de petitorios, y este registro funcionará de monitor bloqueando el acceso a sus métodos mientras haya un hilo accediendo.
La clase cliente recibe por entrada estándar el petitorio y la envía al servidor a través de sockets, para luego esperar e imprimir su respuesta.

### Diagrama de secuencias para creación de ThAcceptor y de ThClient

![Diagrama de secuencia](https://github.com/WagnerMarcos/Taller-pages/blob/master/tp3.png?raw=true)