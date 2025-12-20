#ifndef LISTASIMPLEPILOTOS_H
#define LISTASIMPLEPILOTOS_H

#include <iostream>
using namespace std;

#include "../estructuras/NodoSimple.h"
#include "../modelos/Piloto.h"

class ListaSimplePilotos {
private:
    NodoSimple<Piloto>* primero;

public:
    ListaSimplePilotos() {
        primero = nullptr;
    }

    bool estaVacia() {
        return primero == nullptr;
    }

    void insertarFinal(Piloto p) {
        NodoSimple<Piloto>* nuevo = new NodoSimple<Piloto>(p);

        if (estaVacia()) {
            primero = nuevo;
        } else {
            NodoSimple<Piloto>* actual = primero;
            while (actual->getSiguiente() != nullptr) {
                actual = actual->getSiguiente();
            }
            actual->setSiguiente(nuevo);
        }
    }

    bool buscarPorId(int id, Piloto& resultado) {
        NodoSimple<Piloto>* actual = primero;

        while (actual != nullptr) {
            if (actual->getDato().getId() == id) {
                resultado = actual->getDato();
                return true;
            }
            actual = actual->getSiguiente();
        }
        return false;
    }

    bool eliminarPorId(int id) {
        if (estaVacia()) return false;

        // eliminar primero
        if (primero->getDato().getId() == id) {
            NodoSimple<Piloto>* temp = primero;
            primero = primero->getSiguiente();
            delete temp;
            return true;
        }

        NodoSimple<Piloto>* actual = primero;
        while (actual->getSiguiente() != nullptr) {
            if (actual->getSiguiente()->getDato().getId() == id) {
                NodoSimple<Piloto>* temp = actual->getSiguiente();
                actual->setSiguiente(temp->getSiguiente());
                delete temp;
                return true;
            }
            actual = actual->getSiguiente();
        }
        return false;
    }

    void mostrar() {
        NodoSimple<Piloto>* actual = primero;
        while (actual != nullptr) {
            cout << actual->getDato().getId()
                 << " (" << actual->getDato().getNombre() << ") -> ";
            actual = actual->getSiguiente();
        }
        cout << "NULL\n";
    }

    void generarDot(string padre, ofstream& archivo) {
        NodoSimple<Piloto>* actual = primero;
        int i = 0;

        string anterior = padre;

        while (actual != nullptr) {
            string nodo = padre + "_n" + to_string(i);

            archivo << nodo << " [label=\"ID: "
                    << actual->getDato().getId() << "\\n"
                    << "Licencia: " << actual->getDato().getLicencia()
                    << "\"];\n";

            archivo << anterior << " -> " << nodo << ";\n";

            anterior = nodo;
            actual = actual->getSiguiente();
            i++;
        }
    }
};

#endif
