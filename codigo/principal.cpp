// Autores: Pablo Andres Bueno Ceron 9038949, Juan Eduardo Gómez Aguilar 9024217.
// Punto de entrada del proyecto. Reemplacen este archivo por el suyo.
#include <cstdio>
#include <iostream>
#include <iomanip> 

using namespace std;

struct Paciente {
    string nombre;
    int tiempoLlegada;
};

class ColaCircular {
private:
    Paciente* arreglo;
    int capacidad;
    int frente;
    int trasero;
    int cantidad;

public:
    ColaCircular(int capacidad) {
        this->capacidad = capacidad;
        this->arreglo = new Paciente[capacidad];
        this->frente = 0;
        this->trasero = -1;
        this->cantidad = 0;
    }
}
    ~ColaCircular() {
        delete[] this->arreglo;
    }

    bool estaLlena() {
        bool llena = false;
        if (this->cantidad == this->capacidad) {
            llena = true;
        }
        return llena;
    }

    bool estaVacia() {
        bool vacia = false;
        if (this->cantidad == 0) {
            vacia = true;
        }
        return vacia;
    }
