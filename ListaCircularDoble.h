#ifndef LISTA_CIRCULAR_DOBLE_H
#define LISTA_CIRCULAR_DOBLE_H

#include <iostream>
using namespace std;
#include "NodoDoble.h"

class ListaCircularDoble {
private:
    NodoDoble *primero;
    NodoDoble *ultimo;

public:
    //constructor
    ListaCircularDoble() {
        primero = nullptr;
        ultimo = nullptr;
    }

    bool estaVacia() {
        return (primero == nullptr && ultimo == nullptr);
    }

    //insertar al inicio
    void insertarInicio(int dato) {
        NodoDoble *nuevo = new NodoDoble(dato);

        if (estaVacia()) {
            primero = ultimo = nuevo;
            primero->setSiguiente(primero);
            primero->setAnterior(primero);
        } else {
            nuevo->setSiguiente(primero);
            nuevo->setAnterior(ultimo);

            primero->setAnterior(nuevo);
            ultimo->setSiguiente(nuevo);

            primero = nuevo;
        }
    }

    //insertar al final
    void insertarFinal(int dato) {
        NodoDoble *nuevo = new NodoDoble(dato);

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

    //eliminar al inicio
    void eliminarInicio() {
        if (estaVacia()) {
            cout << "Lista vacia" << endl;
        } 
        else if (primero == ultimo) {
            delete primero;
            primero = ultimo = nullptr;
        } 
        else {
            NodoDoble *aux = primero;

            primero = primero->getSiguiente();
            primero->setAnterior(ultimo);
            ultimo->setSiguiente(primero);

            delete aux;
        }
    }

    //eliminar al final
    void eliminarFinal() {
        if (estaVacia()) {
            cout << "Lista vacia" << endl;
        } 
        else if (primero == ultimo) {
            delete primero;
            primero = ultimo = nullptr;
        } 
        else {
            NodoDoble *aux = ultimo;

            ultimo = ultimo->getAnterior();
            ultimo->setSiguiente(primero);
            primero->setAnterior(ultimo);

            delete aux;
        }
    }

    //mostrar de izq a derecha
    void mostrarAdelante() {
        if (estaVacia()) {
            cout << "Lista vacia" << endl;
        } else {
            NodoDoble *actual = primero;

            do {
                cout << actual->getDato();
                actual = actual->getSiguiente();
                if (actual != primero)
                    cout << " <-> ";
            } while (actual != primero);

            cout << endl;
        }
    }

    //mostrar de derecha a izquierda
    void mostrarAtras() {
        if (estaVacia()) {
            cout << "Lista vacia" << endl;
        } else {
            NodoDoble *actual = ultimo;

            do {
                cout << actual->getDato();
                actual = actual->getAnterior();
                if (actual != ultimo)
                    cout << " <-> ";
            } while (actual != ultimo);

            cout << endl;
        }
    }

    ~ListaCircularDoble() {
        while (!estaVacia()) {
            eliminarInicio();
        }
    }
};

#endif
