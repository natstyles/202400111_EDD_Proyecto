#ifndef FILA_H
#define FILA_H

#include <iostream>
using namespace std;

class Fila {
private:
    Nodo *frente;
    Nodo *final;

public:
    // Constructor
    Fila() {
        frente = nullptr;
        final = nullptr;
    }

    bool estaVacia() {
        return (frente == nullptr && final == nullptr);
    }

    //encolar
    void encolar(int dato) {
        Nodo *nuevo = new Nodo(dato);

        if (estaVacia()) {
            frente = final = nuevo;
        } else {
            final->setSiguiente(nuevo);
            final = nuevo;
        }
    }

    //desencolar
    void desencolar() {
        if (estaVacia()) {
            cout << "La fila esta vacia" << endl;
        } 
        else if (frente == final) { //solo hay un nodo
            delete frente;
            frente = final = nullptr;
        } 
        else {
            Nodo *aux = frente;
            frente = frente->getSiguiente();
            delete aux;
        }
    }

    //ver frente
    void verFrente() {
        if (estaVacia()) {
            cout << "Fila vacia" << endl;
        } else {
            cout << "Frente: " << frente->getDato() << endl;
        }
    }

    //mostramos la fila
    void mostrarFila() {
        if (estaVacia()) {
            cout << "Fila vacia" << endl;
        } else {
            Nodo *actual = frente;
            while (actual != nullptr) {
                cout << actual->getDato();
                actual = actual->getSiguiente();
                if (actual != nullptr)
                    cout << " <- ";
            }
            cout << endl;
        }
    }

    // Destructor
    ~Fila() {
        while (!estaVacia()) {
            desencolar();
        }
    }
};

#endif
