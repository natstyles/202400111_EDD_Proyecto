#ifndef PILAEQUIPAJE_H
#define PILAEQUIPAJE_H

#include <iostream>
using namespace std;

#include "NodoSimple.h"

class PilaEquipaje {
private:
    NodoSimple<int> *tope;

public:
    PilaEquipaje() {
        tope = nullptr;
    }

    bool estaVacia() {
        return (tope == nullptr);
    }

    //metemos
    void push(int maletas) {
        NodoSimple<int> *nuevo = new NodoSimple<int>(maletas);
        nuevo->setSiguiente(tope);
        tope = nuevo;
    }

    //sacamos
    int pop() {
        if (estaVacia()) {
            cout << "Pila vacia" << endl;
            return -1;
        }

        NodoSimple<int> *aux = tope;
        int dato = aux->getDato();
        tope = tope->getSiguiente();
        delete aux;
        return dato;
    }

    void mostrar() {
        NodoSimple<int> *actual = tope;

        while (actual != nullptr) {
            cout << actual->getDato() << endl;
            actual = actual->getSiguiente();
        }
    }
};

#endif
