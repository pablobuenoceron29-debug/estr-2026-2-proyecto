
#include <iostream>

using namespace std;

class paciente {
    private:
    string nombre;
    int tiempoE;
    int nivelA;
    int promedio;
    public:
    paciente() : nombre(""), tiempoE(0), nivelA(1), promedio(0) {}
    paciente(string n, int ni){
        nombre = n;
        tiempoE = 0;
        promedio = 1;
        if (ni < 1){
            nivelA = 1;
        }
        else{
            if (ni > 5){
                nivelA = 5;
                promedio = 5 + 0/2;
            }
            else{
                nivelA = ni;
                promedio = ni + 0/2;
            }
        }
        

    }
    //~paciente();
    void aumentarTiempo(){
        tiempoE += 1;
        promedio = (tiempoE + nivelA) / 2;
    }
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
    paciente* arregloAlternativo;
    int frente;
    int final;
    int capacidad;
    int contador;
    int pos(int i) { return (frente + i) % capacidad; }
    double sumaEspera;
    int atendidos;
    double sumaEsperaAl;
    int atendidosAl;

public:
    colaCircular(int tamano) {
        capacidad = tamano;
        arreglo = new paciente[capacidad];
        arregloAlternativo = new paciente[capacidad];
        frente = 0;
        final = -1;
        contador = 0;
        sumaEspera = 0;
        atendidos = 0;
        sumaEsperaAl = 0;
        atendidosAl = 0;
    };
    ~colaCircular(){
        delete[] arreglo;
        delete[] arregloAlternativo;
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
    void promedio(){
        float promedio;
        float promedioAlternativo;
        if (atendidos > 0) {
            promedio = static_cast<float>(sumaEspera) / atendidos;
            cout << "Promedio de espera(monticulo binario): " << promedio << endl;
            promedioAlternativo = static_cast<float>(sumaEsperaAl) / atendidosAl;
            cout << "Promedio de espera(cola circular): " << promedioAlternativo << endl;
        }
        else {
            cout << "No se han atendido pacientes." << endl;
        }
    };
    bool estaLlena(){
        return contador == capacidad;
    };
    bool estaVacia(){
        return contador == 0;
    };
    void pasaTiempo(){
        for (int i = 0; i < contador; i++) {
            arreglo[pos(i)].aumentarTiempo();
            arregloAlternativo[pos(i)].aumentarTiempo();
        }
    }
    void encolar(paciente valor) {
        if (estaLlena()) {
            cout << "la cola esta llena" << endl;
            return;
        }
        final = (final + 1) % capacidad;
        arreglo[final] = valor;
        arregloAlternativo[final] = valor;
        contador++;
        organizarMB(); 
    }
    
    void desencolar() {
        if (estaVacia()) {
            cout << "no hay nadie en la cola." << endl;
            return;
        }
        cout << "se fue (monticulo binario): " << arreglo[frente].getNombre() << endl;
        cout << "se fue (cola circular): " << arregloAlternativo[frente].getNombre() << endl;

        sumaEspera += arreglo[frente].getTiempoE();
        atendidos++;

        sumaEsperaAl += arregloAlternativo[frente].getTiempoE();
        atendidosAl++;

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
    void cuantos() {
        cout << "Cantidad de pacientes en la cola: " << contador << endl;
    }
};
int main() {
    int tamano;
    cout << "Ingrese numero de ejecuciones: ";
    cin >> tamano;
    string eleccion;
    string nombre;
    int nivel;
    cin >> eleccion;
    colaCircular cola(5);
    for (int i = 0; i < tamano; i++) {
    
        if (eleccion == "LLEGA" or eleccion == "llega") {
            cin >> nombre;
            cin >> nivel;
            paciente p(nombre, nivel);
            cola.encolar(p);
            cola.pasaTiempo();
        }
        else if (eleccion == "ATIENDE" or eleccion == "atiende") {
            cola.desencolar();
            cola.pasaTiempo();
        }
        else if (eleccion == "ESPERAN" or eleccion == "esperan") {
            cola.cuantos();
            cola.pasaTiempo();
        }
        else if (eleccion == "PROMEDIO" or eleccion == "promedio") {
            cola.promedio();
            cola.pasaTiempo();
        }
        else {
            cout << "Opcion no valida" << endl;
            i--;
        }
        cin >> eleccion;
    }
    return 0; // Único return de la función main
}
