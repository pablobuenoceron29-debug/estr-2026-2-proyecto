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

// esto es para organizar la cola como montículo binario

//mouskerramienta que usaremos más tarde

void intercambiar(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

// Baja un elemento hasta su lugar

void heapify(std::vector<int>& a, int n, int i) {
    while (true) {
        int mayor = i;
        int izq = 2 * i + 1;
        int der = 2 * i + 2;

        if (izq < n && a[izq] > a[mayor]) mayor = izq;
        if (der < n && a[der] > a[mayor]) mayor = der;

        if (mayor == i) break;
        intercambiar(a[i], a[mayor]);
        i = mayor;
    }
}

// Ordena la lista completa de menor a mayor

void construirHeap(std::vector<int>& a) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
}

// Ordena la lista completa de menor a mayor

void heapSort(std::vector<int>& a) {
    int n = a.size();
    construirHeap(a);
    for (int i = n - 1; i > 0; i--) {
        intercambiar(a[0], a[i]);
        heapify(a, i, 0);
    }
}

// Sube el nuevo valor hasta su lugar

void insertarHeap(std::vector<int>& a, int valor) {
    a.push_back(valor);
    int i = a.size() - 1;

    while (i > 0) {
        int padre = (i - 1) / 2;
        if (a[i] <= a[padre]) break;
        intercambiar(a[i], a[padre]);
        i = padre;
    }
}

