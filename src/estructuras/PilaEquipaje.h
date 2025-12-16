#ifndef PILAEQUIPAJE_H
#define PILAEQUIPAJE_H

#include <iostream>
#include <fstream>
using namespace std;

#include "NodoSimple.h"
#include "../modelos/Equipaje.h"
#include "../utils/Graphviz.h"

class PilaEquipaje {
private:
    NodoSimple<Equipaje>* tope;

public:
    PilaEquipaje() {
        tope = nullptr;
    }

    bool estaVacia() {
        return (tope == nullptr);
    }

    // metemos equipaje con pasaporte
    void push(string pasaporte, int maletas) {
        Equipaje e(pasaporte, maletas);
        NodoSimple<Equipaje>* nuevo = new NodoSimple<Equipaje>(e);
        nuevo->setSiguiente(tope);
        tope = nuevo;
    }

    // sacamos equipaje
    Equipaje pop() {
        if (estaVacia()) {
            cout << "Pila vacia" << endl;
            return Equipaje("", -1);
        }

        NodoSimple<Equipaje>* aux = tope;
        Equipaje dato = aux->getDato();
        tope = tope->getSiguiente();
        delete aux;
        return dato;
    }

    void mostrar() {
        NodoSimple<Equipaje>* actual = tope;

        while (actual != nullptr) {
            Equipaje e = actual->getDato();
            cout << "Pasaporte: " << e.getPasaporte()
                 << " | Equipaje: " << e.getCantidad() << endl;
            actual = actual->getSiguiente();
        }
    }

    // generación de reporte graphviz
    void generarReporte(string nombre, string titulo) {
        ofstream archivo(nombre + ".dot");

        archivo << "digraph G {\n";
        archivo << "rankdir=TB;\n";

        archivo << "labelloc=\"t\";\n";
        archivo << "label=\"" << titulo << "\";\n";
        archivo << "fontsize=20;\n";

        archivo << "node [shape=box, fontname=\"Arial\"];\n";

        NodoSimple<Equipaje>* actual = tope;

        while (actual != nullptr) {
            Equipaje e = actual->getDato();

            string etiqueta =
                "Pasaporte: " + e.getPasaporte() + "\\n" +
                "Equipaje: " + to_string(e.getCantidad());

            archivo << "\"" << etiqueta << "\"";

            if (actual->getSiguiente() != nullptr) {
                Equipaje sig = actual->getSiguiente()->getDato();
                string etiqueta2 =
                    "Pasaporte: " + sig.getPasaporte() + "\\n" +
                    "Equipaje: " + to_string(sig.getCantidad());

                archivo << " -> \"" << etiqueta2 << "\";\n";
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
