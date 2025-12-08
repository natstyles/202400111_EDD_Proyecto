#ifndef LISTACIRCULARAVIONES_H
#define LISTACIRCULARAVIONES_H

#include <iostream>
using namespace std;

#include "NodoDoble.h"
#include "Avion.h"

class ListaCircularAviones {
private:
    NodoDoble<Avion> *primero;
    NodoDoble<Avion> *ultimo;

public:
    ListaCircularAviones() {
        primero = nullptr;
        ultimo = nullptr;
    }

    bool estaVacia() {
        return (primero == nullptr && ultimo == nullptr);
    }

    //inserta al final
    void insertar(Avion a) {
        NodoDoble<Avion> *nuevo = new NodoDoble<Avion>(a);

        if (estaVacia()) {
            primero = ultimo = nuevo;
            primero->setSiguiente(primero);
            primero->setAnterior(primero);
        } else {
            nuevo->setAnterior(ultimo);
            nuevo->setSiguiente(primero);

            ultimo->setSiguiente(nuevo);
            primero->setAnterior(nuevo);

            ultimo = nuevo;
        }
    }

    //mostrar
    void mostrar() {
        if (estaVacia()) {
            cout << "Lista vacia" << endl;
            return;
        }

        NodoDoble<Avion> *actual = primero;
        do {
            cout << actual->getDato().getRegistro()
                 << " (" << actual->getDato().getEstado() << ") <-> ";
            actual = actual->getSiguiente();
        } while (actual != primero);

        cout << endl;
    }
};

#endif
