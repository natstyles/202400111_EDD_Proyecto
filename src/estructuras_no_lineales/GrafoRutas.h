#ifndef GRAFORUTAS_H
#define GRAFORUTAS_H

#include <fstream>
#include <sstream>
#include <iostream>
#include "NodoCiudad.h"
using namespace std;

class GrafoRutas {
private:
    NodoCiudad* ciudades;

    NodoCiudad* buscarCiudad(const string& nombre) {
        NodoCiudad* aux = ciudades;
        while (aux) {
            if (aux->nombre == nombre) return aux;
            aux = aux->sig;
        }
        return nullptr;
    }

    NodoCiudad* crearCiudadSiNoExiste(const string& nombre) {
        NodoCiudad* c = buscarCiudad(nombre);
        if (c) return c;

        NodoCiudad* nueva = new NodoCiudad(nombre);
        nueva->sig = ciudades;
        ciudades = nueva;
        return nueva;
    }

public:
    GrafoRutas() : ciudades(nullptr) {}

    //Insertar una ruta dirigida Origen -> Destino
    void insertarRuta(const string& origen, const string& destino, int distancia) {
        NodoCiudad* cOrigen = crearCiudadSiNoExiste(origen);
        crearCiudadSiNoExiste(destino); //asegura que exista el nodo destino
        cOrigen->agregarRuta(destino, distancia);
    }

    // Reporte Graphviz
    void generarReporte(const string& nombre, const string& titulo) {
        ofstream dot(nombre + ".dot");

        int totalCiudades = contarCiudades();

        dot << "digraph Rutas {\n";
        dot << "rankdir=LR;\n";
        dot << "labelloc=\"t\";\n";
        dot << "label=\"" << titulo << " (" << totalCiudades << " ciudades)\";\n";
        dot << "fontsize=20;\n";

        NodoCiudad* c = ciudades;
        while (c) {
            NodoRuta* r = c->adyacentes;
            while (r) {
                dot << "\"" << c->nombre << "\" -> \"" << r->destino
                    << "\" [label=\"" << r->distancia << " km\"];\n";
                r = r->sig;
            }
            c = c->sig;
        }

        dot << "}\n";
        dot.close();

        generarImagen(nombre + ".dot", nombre + ".png");
    }

    int contarCiudades() {
        int total = 0;
        NodoCiudad* aux = ciudades;
        while (aux) {
            total++;
            aux = aux->sig;
        }
        return total;
    }
};

#endif
