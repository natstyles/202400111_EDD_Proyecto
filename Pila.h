#ifndef PILA_H
#define PILA_H

#include <iostream>
using namespace std;

class Pila {
private:
    Nodo *tope;

public:
    // Constructor
    Pila() {
        tope = nullptr;
    }

    bool estaVacia() {
        return (tope == nullptr);
    }

    //metemos dato
    void push(int dato) {
        Nodo *nuevo = new Nodo(dato);

        if (estaVacia()) {
            tope = nuevo;
        } else {
            nuevo->setSiguiente(tope);
            tope = nuevo;
        }
    }

    //sacamos dato
    void pop() {
        if (estaVacia()) {
            cout << "Pila vacia" << endl;
        } else {
            Nodo *aux = tope;
            tope = tope->getSiguiente();
            delete aux;
        }
    }

    //miramos el tope de la pila
    void verTope() {
        if (estaVacia()) {
            cout << "Pila vacia" << endl;
        } else {
            cout << "Tope: " << tope->getDato() << endl;
        }
    }

    // ✅ MOSTRAR PILA
    void mostrarPila() {
        if (estaVacia()) {
            cout << "Pila vacia" << endl;
        } else {
            Nodo *actual = tope;
            while (actual != nullptr) {
                cout << actual->getDato() << endl;
                actual = actual->getSiguiente();
            }
        }
    }

    // Destructor
    ~Pila() {
        while (!estaVacia()) {
            pop();
        }
    }
};

#endif
