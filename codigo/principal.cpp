// Autores: Pablo Andres Bueno Ceron 9038949, Juan Eduardo Gomez Aguilar 9024217
#include <iostream>
#include <iomanip>
#include <string>
#include "Paciente.h"
#include "ColaCircular.h"
#include "MonticuloBinario.h"

using namespace std;

template <typename Estructura>
void ejecutarSimulacion(int numOrdenes) {
    // Capacidad acotada para probar el comportamiento modular de la cola circular
    int capacidad = (numOrdenes > 0) ? numOrdenes : 1;
    Estructura sala(capacidad);

    int pacientesAtendidos = 0;
    double sumaTiemposEspera = 0.0;
    int reloj = 1;

    while (reloj <= numOrdenes) {
        string orden;
        cin >> orden;

        if (orden == "LLEGA") {
            string nombre;
            int urgencia;
            cin >> nombre >> urgencia;
            Paciente nuevo(nombre, urgencia, reloj);
            sala.encolar(nuevo);
        } else if (orden == "ATIENDE") {
            if (sala.estaVacia()) {
                cout << "nadie espera\n";
            } else {
                Paciente atendido = sala.desencolar();
                int espera = reloj - atendido.tiempoLlegada;
                sumaTiemposEspera += espera;
                pacientesAtendidos++;
                cout << atendido.nombre << "\n";
            }
        } else if (orden == "ESPERAN") {
            cout << sala.obtenerCantidad() << "\n";
        } else if (orden == "PROMEDIO") {
            if (pacientesAtendidos == 0) {
                cout << "0.0\n";
            } else {
                double promedio = sumaTiemposEspera / pacientesAtendidos;
                cout << fixed << setprecision(1) << promedio << "\n";
            }
        }
        reloj++;
    }
}

int main() {
    int numOrdenes = 0;
    if (cin >> numOrdenes) {
        if (numOrdenes > 0) {
            // Intercambiable por ejecutarSimulacion<ColaCircular>(numOrdenes);
            ejecutarSimulacion<MonticuloBinario>(numOrdenes);
        }
    }
    return 0;
}
