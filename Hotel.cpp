#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    struct Nodo {
    public:
        Nodo *previo;
        string dato1;
        int dato2;
        Nodo *sgte;

        Nodo(string nombre, int numHabitacion) {
            previo = nullptr;
            dato1 = nombre;
            dato2 = numHabitacion;
            sgte = nullptr;
        }
    };

    class Lista {
    public:
        Nodo *raiz;

        Lista() {
            raiz = nullptr;
        }

        void insertarNodo(string nombre, int numHabitacion) {
            Nodo *nuevoNodo = new Nodo(nombre, numHabitacion);

            if (raiz == nullptr) {
                raiz = nuevoNodo;
            } else {
                Nodo *actual = raiz;

                while (actual->sgte != nullptr) {
                    actual = actual->sgte;
                }

                actual->sgte = nuevoNodo;
                nuevoNodo->previo = actual;
            }
        }

        Nodo *buscarPorNombre(string nombre) {
            Nodo *actual = raiz;

            while (actual != nullptr) {
                if (actual->dato1 == nombre) {
                    return actual;
                }

                actual = actual->sgte;
            }

            return nullptr;
        }

        Nodo *buscarPorNumHabitacion(int numHabitacion) const {
            Nodo *actual = raiz;

            while (actual != nullptr) {
                if (actual->dato2 == numHabitacion) {
                    return actual;
                }

                actual = actual->sgte;
            }

            return nullptr;
        }

        void mostrarListaAlfabetica() const {
            Nodo *actual = raiz;

            while (actual != nullptr) {
                cout << actual->dato1 << " - " << actual->dato2 << endl;
                actual = actual->sgte;
            }
        }

        void mostrarListaLlegada() const {
            Nodo *actual = raiz;

            while (actual->sgte != nullptr) {
                actual = actual->sgte;
            }

            while (actual != nullptr) {
                cout << actual->dato1 << " - " << actual->dato2 << endl;
                actual = actual->previo;
            }
        }
    };


        Lista lista;

        // Cargar información del archivo de texto en la lista
        ifstream archivo("huespedes.txt");
        string nombre;
        int numHabitacion;

        while (archivo >> nombre >> numHabitacion) {
            lista.insertarNodo(nombre, numHabitacion);
        }

        archivo.close();

        // Menú de opciones
        int opcion;

        do {
            cout << endl;
            cout << "1. Ingresar nuevo huesped" << endl;
            cout << "2. Buscar huesped" << endl;
            cout << "3. Mostrar lista (alfabetica)" << endl;
            cout << "4. Mostrar lista (orden de llegada)" << endl;
            cout << "5. Consultar vecinos" << endl;
            cout << "6. Salir" << endl;
        }
        while(opcion=!6);{
            cout << "Ingrese una opcion del 1 al 5: ";
        };

            return 0;

}
