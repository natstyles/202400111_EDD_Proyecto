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

        int h = altura(nodo); // ALTURA del subárbol (como antes)

        archivo << "node" << nodo << " [label=\""
                << h << "\\n"
                << "ID: " << nodo->getPiloto().getIdCompleto() << "\\n"
                << "Horas: " << nodo->getPiloto().getHorasVuelo()
                << "\"];\n";

        // Hijo izquierdo (<)
        if (nodo->getIzq()) {
            archivo << "node" << nodo
                    << " -> node" << nodo->getIzq()
                    << " [label=\"<\"];\n";
        }

        // Hijo derecho (>)
        if (nodo->getDer()) {
            archivo << "node" << nodo
                    << " -> node" << nodo->getDer()
                    << " [label=\">\"];\n";
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

    //altura de arbol
    int altura(NodoArbolPiloto* nodo) {
        if (!nodo) return 0;
        return 1 + max(altura(nodo->getIzq()), altura(nodo->getDer()));
    }

    void recolectarNivel(NodoArbolPiloto* nodo, int nivel, int actual,
                     vector<NodoArbolPiloto*>& lista) {
        if (!nodo) return;

        if (nivel == actual) {
            lista.push_back(nodo);
            return;
        }

        recolectarNivel(nodo->getIzq(), nivel, actual + 1, lista);
        recolectarNivel(nodo->getDer(), nivel, actual + 1, lista);
    }

    void generarRanks(ofstream& archivo) {
        int h = altura(raiz);

        for (int i = 1; i <= h; i++) {
            vector<NodoArbolPiloto*> nivel;
            recolectarNivel(raiz, i, 1, nivel);

            if (!nivel.empty()) {
                archivo << "{ rank=same; ";
                for (auto n : nivel)
                    archivo << "node" << n << "; ";
                archivo << "}\n";
            }
        }
    }

    void generarReporte() {
        if (estaVacio()) {
            cout << "Arbol de pilotos vacio\n";
            return;
        }

        ofstream archivo("arbol_pilotos.dot");

        archivo << "digraph Pilotos {\n";
        archivo << "labelloc=\"t\";\n";
        archivo << "label=\"Arbol Binario de Busqueda - Pilotos\";\n";
        archivo << "fontsize=20;\n";

        // Estilo tipo libro
        archivo << "node [\n";
        archivo << "  shape=circle,\n";
        archivo << "  style=filled,\n";
        archivo << "  fillcolor=\"#d9f2d9\",\n";
        archivo << "  color=\"#4CAF50\",\n";
        archivo << "  fontcolor=\"#2e7d32\",\n";
        archivo << "  fontsize=10,\n";
        archivo << "  width=1.1\n";
        archivo << "];\n";

        archivo << "edge [color=\"#4CAF50\", arrowsize=0.7];\n";

        generarDot(raiz, archivo);
        generarRanks(archivo);

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