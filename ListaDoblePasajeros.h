#ifndef LISTADOBLEPASAJEROS_H
#define LISTADOBLEPASAJEROS_H

#include <iostream>
using namespace std;

#include "NodoDoble.h"
#include "Pasajero.h"

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
            cout << actual->getDato().getNombre()
                 << " | Vuelo: " << actual->getDato().getVuelo()
                 << " | Asiento: " << actual->getDato().getAsiento()
                 << endl;
            actual = actual->getSiguiente();
        }
    }
};

#endif
