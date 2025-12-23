#ifndef ARBOLPILOTOS_H
#define ARBOLPILOTOS_H

#include <iostream>
#include <fstream>
using namespace std;

#include "NodoArbolPiloto.h"

class ArbolPilotos {
private:
    NodoArbolPiloto* raiz;

    //inserción
    NodoArbolPiloto* insertarNodo(Piloto p, NodoArbolPiloto* nodo) {
        if (nodo == nullptr) {
            return new NodoArbolPiloto(p);
        }

        if (p.getHorasVuelo() < nodo->getPiloto().getHorasVuelo()) {
            nodo->setIzq(insertarNodo(p, nodo->getIzq()));
        }
        else if (p.getHorasVuelo() > nodo->getPiloto().getHorasVuelo()) {
            nodo->setDer(insertarNodo(p, nodo->getDer()));
        }
        else {
            cout << "Piloto con horas duplicadas no insertado\n";
        }

        return nodo;
    }

    //recorridos
    void inOrden(NodoArbolPiloto* nodo) {
        if (!nodo) return;
        inOrden(nodo->getIzq());
        cout << nodo->getPiloto().getNombre()
             << " (" << nodo->getPiloto().getHorasVuelo() << " hrs)\n";
        inOrden(nodo->getDer());
    }

    void preOrden(NodoArbolPiloto* nodo) {
        if (!nodo) return;
        cout << nodo->getPiloto().getNombre()
             << " (" << nodo->getPiloto().getHorasVuelo() << " hrs)\n";
        preOrden(nodo->getIzq());
        preOrden(nodo->getDer());
    }

    void postOrden(NodoArbolPiloto* nodo) {
        if (!nodo) return;
        postOrden(nodo->getIzq());
        postOrden(nodo->getDer());
        cout << nodo->getPiloto().getNombre()
             << " (" << nodo->getPiloto().getHorasVuelo() << " hrs)\n";
    }

    //graphviz
    void generarDot(NodoArbolPiloto* nodo, ofstream& archivo) {
        if (!nodo) return;

        int idNodo = nodo->getPiloto().getHorasVuelo();

        archivo << "n" << idNodo << " [label=\""
                << "ID: " << nodo->getPiloto().getIdCompleto() << "\\n"
                << "Nombre: " << nodo->getPiloto().getNombre() << "\\n"
                << "Licencia: " << nodo->getPiloto().getLicencia() << "\\n"
                << "Horas: " << nodo->getPiloto().getHorasVuelo()
                << "\"];\n";

        if (nodo->getIzq()) {
            archivo << "n" << idNodo << " -> n"
                    << nodo->getIzq()->getPiloto().getHorasVuelo()
                    << ";\n";
        }

        if (nodo->getDer()) {
            archivo << "n" << idNodo << " -> n"
                    << nodo->getDer()->getPiloto().getHorasVuelo()
                    << ";\n";
        }

        generarDot(nodo->getIzq(), archivo);
        generarDot(nodo->getDer(), archivo);
    }

    //eliminación
    NodoArbolPiloto* eliminarNodo(
        NodoArbolPiloto* nodo,
        int horas,
        bool& eliminado,
        Piloto& eliminadoPiloto
    ) {
        if (!nodo) return nullptr;

        if (horas < nodo->getPiloto().getHorasVuelo()) {
            nodo->setIzq(eliminarNodo(nodo->getIzq(), horas, eliminado, eliminadoPiloto));
        }
        else if (horas > nodo->getPiloto().getHorasVuelo()) {
            nodo->setDer(eliminarNodo(nodo->getDer(), horas, eliminado, eliminadoPiloto));
        }
        else {
            eliminado = true;
            eliminadoPiloto = nodo->getPiloto();

            //Caso hoja
            if (!nodo->getIzq() && !nodo->getDer()) {
                delete nodo;
                return nullptr;
            }

            //Un hijo
            if (!nodo->getIzq()) {
                NodoArbolPiloto* temp = nodo->getDer();
                delete nodo;
                return temp;
            }
            if (!nodo->getDer()) {
                NodoArbolPiloto* temp = nodo->getIzq();
                delete nodo;
                return temp;
            }

            //Dos hijos
            NodoArbolPiloto* mayorIzq = obtenerMayor(nodo->getIzq());
            nodo->setPiloto(mayorIzq->getPiloto());
            nodo->setIzq(eliminarNodo(
                nodo->getIzq(),
                mayorIzq->getPiloto().getHorasVuelo(),
                eliminado,
                eliminadoPiloto
            ));
        }
        return nodo;
    }

    NodoArbolPiloto* obtenerMayor(NodoArbolPiloto* nodo) {
        while (nodo->getDer() != nullptr) {
            nodo = nodo->getDer();
        }
        return nodo;
    }

    int contarRec(NodoArbolPiloto* nodo) {
        if (!nodo) return 0;
        return 1 + contarRec(nodo->getIzq()) + contarRec(nodo->getDer());
    }

public:
    ArbolPilotos() {
        raiz = nullptr;
    }

    bool estaVacio() {
        return raiz == nullptr;
    }

    void insertar(Piloto p) {
        raiz = insertarNodo(p, raiz);
    }

    void mostrarInOrden() {
        inOrden(raiz);
    }

    void mostrarPreOrden() {
        preOrden(raiz);
    }

    void mostrarPostOrden() {
        postOrden(raiz);
    }

    int contar() {
        return contarRec(raiz);
    }

    void generarReporte() {
        if (estaVacio()) {
            cout << "Arbol de pilotos vacio\n";
            return;
        }

        ofstream archivo("arbol_pilotos.dot");

        archivo << "digraph G {\n";
        archivo << "labelloc=\"t\";\n";
        archivo << "label=\"Arbol de Pilotos\";\n";
        archivo << "node [shape=box, style=rounded];\n";

        generarDot(raiz, archivo);

        archivo << "}\n";
        archivo.close();

        system("dot -Tpng arbol_pilotos.dot -o arbol_pilotos.png");
        system("start arbol_pilotos.png");
    }

    //Dar de baja por horas
    bool eliminarPorHoras(int horas, Piloto& eliminado) {
        bool eliminadoFlag = false;
        raiz = eliminarNodo(raiz, horas, eliminadoFlag, eliminado);
        return eliminadoFlag;
    }
};

#endif