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
            cout << actual->getDato().getNombre() << " -> ";
            actual = actual->getSiguiente();
        }
        cout << endl;
    }

    //reporte
    void generarReporte(string nombre) {
        ofstream archivo(nombre + ".dot");
        archivo << "digraph G {\n";
        archivo << "rankdir=LR;\n";
        archivo << "node [shape=box];\n";

        NodoSimple<Pasajero>* actual = frente;

        while (actual != nullptr) {
            archivo << "\"" << actual->getDato().getPasaporte() << "\";\n";

            if (actual->getSiguiente() != nullptr) {
                archivo << "\"" << actual->getDato().getPasaporte()
                        << "\" -> \""
                        << actual->getSiguiente()->getDato().getPasaporte()
                        << "\";\n";
            }

            actual = actual->getSiguiente();
        }

        archivo << "}\n";
        archivo.close();

        generarImagen(nombre + ".dot", nombre + ".png");
    }

};

#endif
