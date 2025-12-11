#ifndef LISTADOBLEPASAJEROS_H
#define LISTADOBLEPASAJEROS_H

#include <iostream>
using namespace std;

#include "NodoDoble.h"
#include "../modelos/Pasajero.h"

class ListaDoblePasajeros {
private:
    NodoDoble<Pasajero> *primero;

public:
    ListaDoblePasajeros() {
        primero = nullptr;
    }

    //Insertamos por vuelo y asiento
    void insertarOrdenado(Pasajero p) {
        NodoDoble<Pasajero> *nuevo = new NodoDoble<Pasajero>(p);

        if (primero == nullptr) {
            primero = nuevo;
            return;
        }

        NodoDoble<Pasajero> *actual = primero;

        while (actual != nullptr &&
              (actual->getDato().getVuelo() < p.getVuelo() ||
              (actual->getDato().getVuelo() == p.getVuelo() &&
               actual->getDato().getAsiento() < p.getAsiento()))) {
            actual = actual->getSiguiente();
               }

        if (actual == primero) {
            nuevo->setSiguiente(primero);
            primero->setAnterior(nuevo);
            primero = nuevo;
        }
        else if (actual == nullptr) {
            NodoDoble<Pasajero> *temp = primero;
            while (temp->getSiguiente() != nullptr)
                temp = temp->getSiguiente();

            temp->setSiguiente(nuevo);
            nuevo->setAnterior(temp);
        }
        else {
            NodoDoble<Pasajero> *ant = actual->getAnterior();
            ant->setSiguiente(nuevo);
            nuevo->setAnterior(ant);
            nuevo->setSiguiente(actual);
            actual->setAnterior(nuevo);
        }
    }

    //mostramos la lista
    void mostrar() {
        NodoDoble<Pasajero> *actual = primero;

        while (actual != nullptr) {
            cout << actual->getDato().getNombre() << " (Pasaporte: " << actual->getDato().getPasaporte() << ")"
                 << " | Vuelo: " << actual->getDato().getVuelo()
                 << " | Asiento: " << actual->getDato().getAsiento()
                 << " | Cant. Equipaje: " << actual->getDato().getEquipaje()
                 << endl;
            actual = actual->getSiguiente();
        }
    }

    //consultamos pasajeros por pasaporte
    void consultar(string pasaporte) {
        if (primero == nullptr) {
            cout << "No hay pasajeros atendidos.\n";
            return;
        }

        NodoDoble<Pasajero> *actual = primero;

        while (actual != nullptr) {
            if (actual->getDato().getPasaporte() == pasaporte) {
                Pasajero p = actual->getDato();

                cout << "\n--- PASAJERO ENCONTRADO ---\n";
                cout << "Nombre: " << p.getNombre() << endl;
                cout << "Pasaporte: " << p.getPasaporte() << endl;
                cout << "Vuelo: " << p.getVuelo() << endl;
                cout << "Asiento: " << p.getAsiento() << endl;
                cout << "Equipaje: " << p.getEquipaje() << endl;
                return;
            }

            actual = actual->getSiguiente();
        }

        cout << "Pasajero no encontrado.\n";
    }

    //reporte graphviz
    void generarReporte(string nombre, string titulo) {
        ofstream archivo(nombre + ".dot");

        archivo << "digraph G {\n";
        archivo << "rankdir=LR;\n";

        archivo << "labelloc=\"t\";\n";
        archivo << "label=\"" << titulo << "\";\n";
        archivo << "fontsize=20;\n";

        archivo << "node [shape=box, fontname=\"Arial\"];\n";

        NodoDoble<Pasajero>* actual = primero;

        while (actual != nullptr) {

            Pasajero p = actual->getDato();

            string etiqueta =
                "Nombre: " + p.getNombre() + "\\n" +
                "Pasaporte: " + p.getPasaporte();

            archivo << "\"" << etiqueta << "\";\n";

            if (actual->getSiguiente() != nullptr) {
                Pasajero ps = actual->getSiguiente()->getDato();
                string etiqueta2 =
                    "Nombre: " + ps.getNombre() + "\\n" +
                    "Pasaporte: " + ps.getPasaporte();

                archivo << "\"" << etiqueta << "\" -> \"" << etiqueta2 << "\";\n";
                archivo << "\"" << etiqueta2 << "\" -> \"" << etiqueta << "\";\n";
            }

            actual = actual->getSiguiente();
        }

        archivo << "}\n";
        archivo.close();

        generarImagen(nombre + ".dot", nombre + ".png");
    }
};

#endif
