#ifndef COLAPASAJEROS_H
#define COLAPASAJEROS_H

#include <iostream>
#include "Graphviz.h"
#include <fstream>

using namespace std;

#include "NodoSimple.h"
#include "Pasajero.h"

class ColaPasajeros {
private:
    NodoSimple<Pasajero> *frente;
    NodoSimple<Pasajero> *final;

public:
    ColaPasajeros() {
        frente = nullptr;
        final = nullptr;
    }

    bool estaVacia() {
        return (frente == nullptr && final == nullptr);
    }

    void encolar(Pasajero p) {
        NodoSimple<Pasajero> *nuevo = new NodoSimple<Pasajero>(p);

        if (estaVacia()) {
            frente = final = nuevo;
        } else {
            final->setSiguiente(nuevo);
            final = nuevo;
        }
    }

    Pasajero desencolar() {
        if (estaVacia()) {
            cout << "Cola vacia" << endl;
            return Pasajero();
        }

        NodoSimple<Pasajero> *aux = frente;
        Pasajero dato = aux->getDato();
        frente = frente->getSiguiente();

        if (frente == nullptr)
            final = nullptr;

        delete aux;
        return dato;
    }

    void mostrar() {
        NodoSimple<Pasajero> *actual = frente;

        while (actual != nullptr) {
            cout << actual->getDato().getNombre() << " (Pasaporte: " << actual->getDato().getPasaporte() << ")" << " -> ";
            actual = actual->getSiguiente();
        }
        cout << endl;
    }

    //reporte
    void generarReporte(string nombre, string titulo) {
        ofstream archivo(nombre + ".dot");

        archivo << "digraph G {\n";
        archivo << "rankdir=LR;\n";

        archivo << "labelloc=\"t\";\n";
        archivo << "label=\"" << titulo << "\";\n";
        archivo << "fontsize=20;\n";

        archivo << "node [shape=box, fontname=\"Arial\"];\n";

        NodoSimple<Pasajero>* actual = frente;

        while (actual != nullptr) {
            Pasajero p = actual->getDato();

            string etiqueta =
                "Nombre: " + p.getNombre() + "\\n" +
                "Pasaporte: " + p.getPasaporte();

            archivo << "\"" << etiqueta << "\";\n";

            if (actual->getSiguiente() != nullptr) {
                Pasajero s = actual->getSiguiente()->getDato();
                string etiqueta2 =
                    "Nombre: " + s.getNombre() + "\\n" +
                    "Pasaporte: " + s.getPasaporte();

                archivo << "\"" << etiqueta << "\" -> \"" << etiqueta2 << "\";\n";
            }

            actual = actual->getSiguiente();
        }

        archivo << "}\n";
        archivo.close();

        generarImagen(nombre + ".dot", nombre + ".png");
    }
};

#endif
