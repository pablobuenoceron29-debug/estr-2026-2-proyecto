// Autores: Pablo Andres Bueno Ceron 9038949, Juan Eduardo Gómez Aguilar 9024217.
// Punto de entrada del proyecto. Reemplacen este archivo por el suyo.
#include <cstdio>
#include <iostream>
#include <iomanip> 

using namespace std;

struct Paciente {
    string nombre;
    int tiempoLlegada;
    int prioridad;
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
    int obtenerCantidad() {
        return this->cantidad;
    }
    void encolar(Paciente p) {
        if (!this->estaLlena()) {
            this->trasero = (this->trasero + 1) % this->capacidad;
            this->arreglo[this->trasero] = p;
            this->cantidad++;
        }
        return;
    }
    Paciente desencolar() {
        Paciente extraido;
        extraido.nombre = "";
        extraido.tiempoLlegada = -1;

        if (!this->estaVacia()) {
            extraido = this->arreglo[this->frente];
            this->frente = (this->frente + 1) % this->capacidad;
            this->cantidad--;
        }
        return extraido;
    }
};

int main() {
    int numOrdenes = 0;
    cin >> numOrdenes;

    if (numOrdenes > 0) {
        ColaCircular cola(numOrdenes);

        int pacientesAtendidos = 0;
        double sumaTiemposEspera = 0.0;

        int reloj = 1; // El reloj avanza 1 unidad por cada orden
