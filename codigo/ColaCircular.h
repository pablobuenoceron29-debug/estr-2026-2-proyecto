// Autores: Pablo Andres Bueno Ceron 9038949, Juan Eduardo Gomez Aguilar 9024217
#ifndef COLACIRCULAR_H
#define COLACIRCULAR_H

#include "Paciente.h"

class ColaCircular {
private:
    Paciente* arreglo;
    int capacidad;
    int frente;
    int trasero;
    int cantidad;

public:
    ColaCircular(int cap) {
        capacidad = cap;
        arreglo = new Paciente[capacidad];
        frente = 0;
        trasero = -1;
        cantidad = 0;
    }

    ~ColaCircular() {
        delete[] arreglo;
    }

    bool estaLlena() const {
        return cantidad == capacidad;
    }

    bool estaVacia() const {
        return cantidad == 0;
    }

    int obtenerCantidad() const {
        return cantidad;
    }

    void encolar(Paciente p) {
        if (!estaLlena()) {
            trasero = (trasero + 1) % capacidad;
            arreglo[trasero] = p;
            cantidad++;
        }
    }

    Paciente desencolar() {
        Paciente extraido;
        if (!estaVacia()) {
            extraido = arreglo[frente];
            frente = (frente + 1) % capacidad;
            cantidad--;
        }
        return extraido;
    }
};

#endif
