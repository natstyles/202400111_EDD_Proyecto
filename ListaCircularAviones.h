#ifndef LISTACIRCULARAVIONES_H
#define LISTACIRCULARAVIONES_H

#include <iostream>
#include "Graphviz.h"
#include <fstream>

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

    //generar reportes
    void generarReporte(string nombre) {
        ofstream archivo(nombre + ".dot");

        archivo << "digraph G {\n";
        archivo << "rankdir=LR;\n";
        archivo << "node [shape=box];\n";

        if (!estaVacia()) {
            NodoDoble<Avion>* actual = primero;

            do {
                archivo << "\"" << actual->getDato().getRegistro()
                        << "\\n" << actual->getDato().getEstado() << "\";\n";

                archivo << "\"" << actual->getDato().getRegistro()
                        << "\\n" << actual->getDato().getEstado() << "\" -> \""
                        << actual->getSiguiente()->getDato().getRegistro()
                        << "\\n" << actual->getSiguiente()->getDato().getEstado()
                        << "\";\n";

                actual = actual->getSiguiente();

            } while (actual != primero);
        }

        archivo << "}\n";
        archivo.close();

        generarImagen(nombre + ".dot", nombre + ".png");
    }
};

#endif
