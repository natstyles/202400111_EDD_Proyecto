#include <iostream>
using namespace std;

class ListaCircular {
private:
    Nodo *primero;
    Nodo *ultimo;

public:
    ListaCircular();

    bool estaVacia() {
        return (primero == nullptr && ultimo == nullptr);
    }

    //insertar final
    void insertarInicio(int dato) {
        Nodo *nuevo = new Nodo(dato);

        if (estaVacia()) {
            primero = ultimo = nuevo;
            ultimo->setSiguiente(primero); // 🔁 circular
        } else {
            nuevo->setSiguiente(primero);
            primero = nuevo;
            ultimo->setSiguiente(primero); // 🔁 se mantiene la circularidad
        }
    }

    //insertar al inicio
    void insertarFinal(int dato) {
        Nodo *nuevo = new Nodo(dato);

        if (estaVacia()) {
            primero = ultimo = nuevo;
            ultimo->setSiguiente(primero); // 🔁 circular
        } else {
            ultimo->setSiguiente(nuevo);
            ultimo = nuevo;
            ultimo->setSiguiente(primero); // 🔁 cerrar el ciclo
        }
    }

    //eliminar inicio
    void eliminarInicio() {
        if (estaVacia()) {
            cout << "Lista esta vacia" << endl;
        } else if (primero == ultimo) { //solo hay uno
            delete primero;
            primero = ultimo = nullptr;
        } else {
            Nodo *aux = primero;
            primero = primero->getSiguiente();
            //el ultimo apunta a primero
            ultimo->setSiguiente(primero);
            delete aux;
        }
    }

    //eliminar al final
    void eliminarFinal() {
        if (estaVacia()) {
            cout << "Lista esta vacia" << endl;
        } else if (primero == ultimo) { //solo hay uno
            delete primero;
            primero = ultimo = nullptr;
        } else {
            Nodo *actual = primero;

            while (actual->getSiguiente() != ultimo) {
                actual = actual->getSiguiente();
            }

            delete ultimo;
            ultimo = actual;
            ultimo->setSiguiente(primero); //cerramos ciclo
        }
    }

    //mostrar la lista
    void visualizarLista() {
        if (estaVacia()) {
            cout << "Lista esta vacia" << endl;
        } else {
            Nodo *actual = primero;

            do {
                cout << actual->getDato();
                actual = actual->getSiguiente();
                if (actual != primero)
                    cout << " -> ";
            } while (actual != primero);

            cout << endl;
        }
    }

    ~ListaCircular();
};

//constructor
ListaCircular::ListaCircular() {
    primero = nullptr;
    ultimo = nullptr;
}

//destructor
ListaCircular::~ListaCircular() {
    while (!estaVacia()) {
        eliminarInicio();
    }
}
