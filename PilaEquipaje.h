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

    //generación de reporte graphviz
    void generarReporte(string nombre, string titulo) {
        ofstream archivo(nombre + ".dot");

        archivo << "digraph G {\n";
        archivo << "rankdir=TB;\n";

        archivo << "labelloc=\"t\";\n";
        archivo << "label=\"" << titulo << "\";\n";
        archivo << "fontsize=20;\n";

        archivo << "node [shape=box, fontname=\"Arial\"];\n";

        NodoSimple<int>* actual = tope;

        while (actual != nullptr) {
            archivo << "\"" << actual->getDato() << "\"";

            if (actual->getSiguiente() != nullptr) {
                archivo << " -> \"" << actual->getSiguiente()->getDato() << "\";\n";
            } else {
                archivo << ";\n";
            }

            actual = actual->getSiguiente();
        }

        archivo << "}\n";
        archivo.close();

        generarImagen(nombre + ".dot", nombre + ".png");
    }
};

#endif
