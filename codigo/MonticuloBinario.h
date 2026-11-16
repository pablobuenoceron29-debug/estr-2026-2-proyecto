// Autores: Pablo Andres Bueno Ceron 9038949, Juan Eduardo Gomez Aguilar 9024217
#ifndef MONTICULOBINARIO_H
#define MONTICULOBINARIO_H

#include "Paciente.h"

class MonticuloBinario {
private:
    Paciente* arreglo;
    int capacidad;
    int cantidad;

    bool tieneMayorPrioridad(const Paciente& a, const Paciente& b) const {
        bool mayor = false;
        if (a.urgencia > b.urgencia) {
            mayor = true;
        } else if (a.urgencia == b.urgencia && a.tiempoLlegada < b.tiempoLlegada) {
            mayor = true;
        }
        return mayor;
    }

    void intercambiar(Paciente& a, Paciente& b) {
        Paciente temp = a;
        a = b;
        b = temp;
    }

    void flotar(int indice) {
        int actual = indice;
        bool posicionado = false;
        while (actual > 0 && !posicionado) {
            int padre = (actual - 1) / 2;
            if (tieneMayorPrioridad(arreglo[actual], arreglo[padre])) {
                intercambiar(arreglo[actual], arreglo[padre]);
                actual = padre;
            } else {
                posicionado = true;
            }
        }
    }

    void hundir(int indice) {
        int actual = indice;
        bool posicionado = false;
        while (!posicionado) {
            int izq = 2 * actual + 1;
            int der = 2 * actual + 2;
            int mayor = actual;

            if (izq < cantidad && tieneMayorPrioridad(arreglo[izq], arreglo[mayor])) {
                mayor = izq;
            }
            if (der < cantidad && tieneMayorPrioridad(arreglo[der], arreglo[mayor])) {
                mayor = der;
            }

            if (mayor != actual) {
                intercambiar(arreglo[actual], arreglo[mayor]);
                actual = mayor;
            } else {
                posicionado = true;
            }
        }
    }

public:
    MonticuloBinario(int cap) {
        capacidad = cap;
        arreglo = new Paciente[capacidad];
        cantidad = 0;
    }

    ~MonticuloBinario() {
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
            arreglo[cantidad] = p;
            flotar(cantidad);
            cantidad++;
        }
    }

    Paciente desencolar() {
        Paciente raiz;
        if (!estaVacia()) {
            raiz = arreglo[0];
            cantidad--;
            if (cantidad > 0) {
                arreglo[0] = arreglo[cantidad];
                hundir(0);
            }
        }
        return raiz;
    }
};
#endif
