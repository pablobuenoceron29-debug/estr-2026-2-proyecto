// Autores: Pablo Andres Bueno Ceron 9038949, Juan Eduardo Gómez Aguilar 9024217.
// Punto de entrada del proyecto. Reemplacen este archivo por el suyo.
#include <cstdio>
#include <iostream>

class ColaCircular {
private:
    int* arreglo;
    int capacidad;
    int frente;
    int trasero;
    int cantidad;

public:
    // Constructor
    ColaCircular(int capacidad) {
        this->capacidad = capacidad;
        this->arreglo = new int[capacidad];
        this->frente = 0;
        this->trasero = -1;
        this->cantidad = 0;
    }

    // Destructor 
    ~ColaCircular() {
        delete[] this->arreglo;
    }

    // 1. Método para verificar si está llena 
    bool estaLlena() {
        bool llena = false;
        if (this->cantidad == this->capacidad) {
            llena = true;
        }
        return llena;
    }

    // 2. Método para verificar si está vacía 
    bool estaVacia() {
        bool vacia = false;
        if (this->cantidad == 0) {
            vacia = true;
        }
        return vacia;
    }

    // 3. Método para encolar 
    void encolar(int valor) {
        if (!this->estaLlena()) {
            this->trasero = (this->trasero + 1) % this->capacidad;
            this->arreglo[this->trasero] = valor;
            this->cantidad++;
        }
        return; 
    }

    // 4. Método para desencolar 
    int desencolar() {
        int valorExtraido = -1;
        if (!this->estaVacia()) {
            valorExtraido = this->arreglo[this->frente];
            this->frente = (this->frente + 1) % this->capacidad;
            this->cantidad--;
        }
        return valorExtraido;
    }
};
