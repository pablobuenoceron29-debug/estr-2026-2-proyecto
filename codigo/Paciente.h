// Autores: Pablo Andres Bueno Ceron 9038949, Juan Eduardo Gomez Aguilar 9024217
#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>

struct Paciente {
    std::string nombre;
    int urgencia;
    int tiempoLlegada;

    Paciente() : nombre(""), urgencia(1), tiempoLlegada(0) {}
    Paciente(std::string n, int u, int t) : nombre(n), urgencia(u), tiempoLlegada(t) {}
};

#endif
