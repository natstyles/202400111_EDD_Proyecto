#ifndef ARBOLPILOTOS_H
#define ARBOLPILOTOS_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "NodoArbolPiloto.h"

class ArbolPilotos {
private:
    NodoArbolPiloto* raiz;

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

    void generarDot(NodoArbolPiloto* nodo, ofstream& archivo) {
        if (!nodo) return;

        //nodo con información completa
        archivo << "\"" << nodo->getPiloto().getId() << "\" "
                << "[label=\""
                << "ID: " << nodo->getPiloto().getId() << "\\n"
                << "Licencia: " << nodo->getPiloto().getLicencia() << "\\n"
                << "Horas: " << nodo->getPiloto().getHorasVuelo()
                << "\"];\n";

        //enlace izquierdo
        if (nodo->getIzq()) {
            archivo << "\"" << nodo->getPiloto().getId() << "\" -> \""
                    << nodo->getIzq()->getPiloto().getId() << "\";\n";
        }

        //enlace derecho
        if (nodo->getDer()) {
            archivo << "\"" << nodo->getPiloto().getId() << "\" -> \""
                    << nodo->getDer()->getPiloto().getId() << "\";\n";
        }

        generarDot(nodo->getIzq(), archivo);
        generarDot(nodo->getDer(), archivo);
    }

    //contar pilots
    int contarRec(NodoArbolPiloto* nodo) {
        if (!nodo) return 0;
        return 1 + contarRec(nodo->getIzq()) + contarRec(nodo->getDer());
    }

    void recolectar(NodoArbolPiloto* nodo, vector<Piloto>& lista) {
        if (!nodo) return;

        recolectar(nodo->getIzq(), lista);
        lista.push_back(nodo->getPiloto());
        recolectar(nodo->getDer(), lista);
    }

    void liberar(NodoArbolPiloto* nodo) {
        if (!nodo) return;
        liberar(nodo->getIzq());
        liberar(nodo->getDer());
        delete nodo;
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

        int total = contar();

        archivo << "digraph G {\n";
        archivo << "labelloc=\"t\";\n";
        archivo << "label=\"Arbol de Pilotos (" << total << ")\";\n";
        archivo << "fontsize=20;\n";
        archivo << "node [shape=box, style=rounded];\n";

        generarDot(raiz, archivo);

        archivo << "}\n";
        archivo.close();

        system("dot -Tpng arbol_pilotos.dot -o arbol_pilotos.png");
        system("start arbol_pilotos.png");
    }

    bool extraerPorId(int id, Piloto& resultado) {
    if (!raiz) return false;

    vector<Piloto> pilotos;
    recolectar(raiz, pilotos);

    bool encontrado = false;

    liberar(raiz);
    raiz = nullptr;

    for (Piloto& p : pilotos) {
        if (p.getId() == id && !encontrado) {
            resultado = p;
            encontrado = true;
        } else {
            insertar(p);
        }
    }

    return encontrado;
}

};

#endif
