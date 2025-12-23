#ifndef LISTASIMPLEPILOTOS_H
#define LISTASIMPLEPILOTOS_H

#include <iostream>
#include <fstream>
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

    //INSERCIÓN
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

    //BUSQUEDA
    bool buscarPorIdCompleto(const string& idCompleto, Piloto& resultado) {
        NodoSimple<Piloto>* actual = primero;

        while (actual != nullptr) {
            if (actual->getDato().getIdCompleto() == idCompleto) {
                resultado = actual->getDato();
                return true;
            }
            actual = actual->getSiguiente();
        }
        return false;
    }

    //ELIMINACIÓN
    bool eliminarPorIdCompleto(const string& idCompleto) {
        if (estaVacia()) return false;

        // Caso: eliminar primero
        if (primero->getDato().getIdCompleto() == idCompleto) {
            NodoSimple<Piloto>* temp = primero;
            primero = primero->getSiguiente();
            delete temp;
            return true;
        }

        NodoSimple<Piloto>* actual = primero;
        while (actual->getSiguiente() != nullptr) {
            if (actual->getSiguiente()->getDato().getIdCompleto() == idCompleto) {
                NodoSimple<Piloto>* temp = actual->getSiguiente();
                actual->setSiguiente(temp->getSiguiente());
                delete temp;
                return true;
            }
            actual = actual->getSiguiente();
        }
        return false;
    }

    //MOSTRAR
    void mostrar() {
        NodoSimple<Piloto>* actual = primero;
        while (actual != nullptr) {
            cout << actual->getDato().getIdCompleto()
                 << " (" << actual->getDato().getNombre() << ") -> ";
            actual = actual->getSiguiente();
        }
        cout << "NULL\n";
    }

    //GRAPHVIZ
    void generarDot(const string& padre, ofstream& archivo) {
        NodoSimple<Piloto>* actual = primero;
        string anterior = padre;
        int contador = 0;

        while (actual != nullptr) {
            string nodo = padre + "_n" + to_string(contador);

            archivo << nodo << " [label=\""
                    << "ID: " << actual->getDato().getIdCompleto() << "\\n"
                    << "Nombre: " << actual->getDato().getNombre() << "\\n"
                    << "Licencia: " << actual->getDato().getLicencia()
                    << "\"];\n";

            archivo << anterior << " -> " << nodo << ";\n";

            anterior = nodo;
            actual = actual->getSiguiente();
            contador++;
        }
    }
};

#endif