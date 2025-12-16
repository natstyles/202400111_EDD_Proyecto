#ifndef LISTACIRCULARAVIONES_H
#define LISTACIRCULARAVIONES_H

#include <iostream>
#include <fstream>
#include "../utils/Graphviz.h"

using namespace std;

#include "NodoDoble.h"
#include "../modelos/Avion.h"

class ListaCircularAviones {
private:
    NodoDoble<Avion>* primero;
    NodoDoble<Avion>* ultimo;

public:
    ListaCircularAviones() {
        primero = nullptr;
        ultimo = nullptr;
    }

    bool estaVacia() {
        return primero == nullptr && ultimo == nullptr;
    }

    Avion obtenerPrimero() {
        if (estaVacia()) {
            throw runtime_error("Lista vacia: no hay primero");
        }
        return primero->getDato();
    }

    //insertar al final
    void insertar(Avion a) {
        NodoDoble<Avion>* nuevo = new NodoDoble<Avion>(a);

        if (estaVacia()) {
            primero = ultimo = nuevo;
            nuevo->setSiguiente(nuevo);
            nuevo->setAnterior(nuevo);
        } else {
            nuevo->setAnterior(ultimo);
            nuevo->setSiguiente(primero);

            ultimo->setSiguiente(nuevo);
            primero->setAnterior(nuevo);

            ultimo = nuevo;
        }
    }

    //mostrar en consola
    void mostrar() {
        if (estaVacia()) {
            cout << "Lista vacia" << endl;
            return;
        }

        NodoDoble<Avion>* actual = primero;
        do {
            cout << actual->getDato().getRegistro()
                 << " (" << actual->getDato().getEstado() << ") <-> ";
            actual = actual->getSiguiente();
        } while (actual != primero);

        cout << endl;
    }

    //contar cant aviones
    int contarNodos() {
        if (estaVacia()) return 0;

        int contador = 0;
        NodoDoble<Avion>* actual = primero;

        do {
            contador++;
            actual = actual->getSiguiente();
        } while (actual != primero);

        return contador;
    }

    //eliminar por registro
    void eliminarPorRegistro(string registro) {
        if (estaVacia()) return;

        NodoDoble<Avion>* actual = primero;

        do {
            if (actual->getDato().getRegistro() == registro) {

                // Solo un nodo
                if (primero == ultimo) {
                    delete actual;
                    primero = ultimo = nullptr;
                    return;
                }

                actual->getAnterior()->setSiguiente(actual->getSiguiente());
                actual->getSiguiente()->setAnterior(actual->getAnterior());

                if (actual == primero)
                    primero = actual->getSiguiente();

                if (actual == ultimo)
                    ultimo = actual->getAnterior();

                delete actual;
                return;
            }

            actual = actual->getSiguiente();
        } while (actual != primero);
    }

    //mandar a mantenimiento
    bool buscarYEnviarAMantenimiento(string registro, ListaCircularAviones& mantenimiento) {
        if (estaVacia()) return false;

        NodoDoble<Avion>* actual = primero;

        do {
            if (actual->getDato().getRegistro() == registro) {
                Avion a = actual->getDato();
                a.setEstado("Mantenimiento");

                eliminarPorRegistro(registro);
                mantenimiento.insertar(a);
                return true;
            }
            actual = actual->getSiguiente();
        } while (actual != primero);

        return false;
    }

    //mandar a disponible
    bool buscarYEnviarADisponibles(string registro, ListaCircularAviones& disponibles) {
        if (estaVacia()) return false;

        NodoDoble<Avion>* actual = primero;

        do {
            if (actual->getDato().getRegistro() == registro) {
                Avion a = actual->getDato();
                a.setEstado("Disponible");

                eliminarPorRegistro(registro);
                disponibles.insertar(a);
                return true;
            }
            actual = actual->getSiguiente();
        } while (actual != primero);

        return false;
    }

    //reporte grapho
    void generarReporte(string nombre, string titulo) {
        ofstream archivo(nombre + ".dot");
        int total = contarNodos();

        archivo << "digraph G {\n";
        archivo << "rankdir=LR;\n";
        archivo << "labelloc=\"t\";\n";
        archivo << "label=\"" << titulo << " (" << total << ")\";\n";
        archivo << "fontsize=20;\n";
        archivo << "node [shape=box, fontname=\"Arial\"];\n";

        if (!estaVacia()) {
            NodoDoble<Avion>* actual = primero;
            int i = 0;

            // Declarar nodos
            do {
                Avion a = actual->getDato();
                archivo << "n" << i << " [label=\""
                        << "Registro: " << a.getRegistro() << "\\n"
                        << "Modelo: " << a.getModelo() << "\\n"
                        << "Estado: " << a.getEstado()
                        << "\"];\n";
                actual = actual->getSiguiente();
                i++;
            } while (actual != primero);

            //enlaces doble sentido
            for (int j = 0; j < total; j++) {
                int sig = (j + 1) % total;
                archivo << "n" << j << " -> n" << sig << " [dir=both];\n";
            }

        }

        archivo << "}\n";
        archivo.close();

        generarImagen(nombre + ".dot", nombre + ".png");
    }
};

#endif
