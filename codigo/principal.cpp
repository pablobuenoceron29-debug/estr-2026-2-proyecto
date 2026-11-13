// Autores: Pablo Andres Bueno Ceron 9038949, Juan Eduardo Gómez Aguilar 9024217.
// Punto de entrada del proyecto. Reemplacen este archivo por el suyo.
#include <cstdio>
#include <iostream>
#include <iomanip> 

using namespace std;

class paciente {
    private:
    string nombre;
    int tiempoE;
    int nivelA;
    int promedio;
    public:
    paciente() : nombre(""), tiempoE(0), nivelA(1), promedio(0) {}
    paciente(string n, int t, int ni){
        nombre = n;
        if (t < 0){
            tiempoE = 0;
        }
        else{
            tiempoE = t;
        }
        if (ni < 1){
            nivelA = 1;
        }
        else{
            if (ni > 5){
                nivelA = 5;
            }
            else{
                nivelA = ni;
            }
        }
        
        promedio = ((tiempoE+nivelA)/2);
    }
    //~paciente();
    string getNombre(){
        return nombre;
    }
    int getNivelA(){
        return nivelA;
    }
    int getTiempoE(){
        return tiempoE;
    }
    int getPromedio(){
        return promedio;
    }
};

class colaCircular
{
private:
    paciente* arreglo;
    int frente;
    int final;
    int capacidad;
    int contador;
    int pos(int i) { return (frente + i) % capacidad; }
public:
    colaCircular(int tamano) {
        capacidad = tamano;
        arreglo = new paciente[capacidad];
        frente = 0;
        final = -1;
        contador = 0;
    };
    ~colaCircular(){
        delete[] arreglo;
    };
 void organizarMB() {
        int n = contador;
        for (int i = n / 2 - 1; i >= 0; i--) {
            int actual = i;
            while (true) {
                int izq = 2 * actual + 2; //si tu toc no es tan grande como el mio esto seria al revez, pero en realidad no afecta
                int der = 2 * actual + 1;
                int mayor = actual;

                if (izq < n && arreglo[pos(izq)].getPromedio() > arreglo[pos(mayor)].getPromedio())
                    mayor = izq;
                if (der < n && arreglo[pos(der)].getPromedio() > arreglo[pos(mayor)].getPromedio())
                    mayor = der;

                if (mayor == actual) break;

                swap(arreglo[pos(actual)], arreglo[pos(mayor)]);
                actual = mayor;
            }
        }
    }
    bool estaLlena(){
        return contador == capacidad;
    };
    bool estaVacia(){
        return contador == 0;
    };
    
    void encolar(paciente valor) {
        if (estaLlena()) {
            cout << "ba llena" << endl;
            return;
        }
        final = (final + 1) % capacidad;
        arreglo[final] = valor;
        contador++;
        organizarMB(); 
    }
    
    void desencolar() {
        if (estaVacia()) {
            cout << "va cia? preguntale a cia si va" << endl;
            return;
        }
        cout << "se fue: " << arreglo[frente].getNombre() << endl;
        frente = (frente + 1) % capacidad;
        contador--;
        organizarMB();
    }
    void mostrar() {
        if (estaVacia()) {
            cout << "va cia" << endl;
            return;
        }
        cout << "elementos el la cola: ";
        for (int i = 0; i < contador; i++) {
            cout << arreglo[pos(i)].getNombre() << " (" << "Nivel de atencion: " << arreglo[pos(i)].getNivelA() << " - Tiempo esperado: " << arreglo[pos(i)].getTiempoE() << ") ";
        }
        cout << endl;
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
        while (reloj <= numOrdenes) {
            string orden;
            cin >> orden;

            if (orden == "LLEGA") {
                string nombre;
                int urgencia;
                cin >> nombre >> urgencia;

                Paciente nuevoPaciente;
                nuevoPaciente.nombre = nombre;
                nuevoPaciente.tiempoLlegada = reloj; 
                cola.encolar(nuevoPaciente);
            }
            else if (orden == "ATIENDE") {
                if (cola.estaVacia()) {
                    cout << "nadie espera\n";
                } else {
                    Paciente p = cola.desencolar();
                    // Tiempo de espera = Reloj actual (atención) - Reloj de registro
                    int tiempoEspera = reloj - p.tiempoLlegada;
                    sumaTiemposEspera += tiempoEspera;
                    pacientesAtendidos++;
                    cout << p.nombre << "\n";
                }
            }
            else if (orden == "ESPERAN") {
                cout << cola.obtenerCantidad() << "\n";
            }
            else if (orden == "PROMEDIO") {
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
    return 0; // Único return de la función main
}
