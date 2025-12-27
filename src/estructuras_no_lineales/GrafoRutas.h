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

    void dijkstra(string origen, string destino) {
        int n = contarCiudades();
        if (n == 0) {
            cout << "No hay ciudades en el grafo\n";
            return;
        }

        // 1. Guardar nombres de ciudades en un arreglo
        string nombres[n];
        NodoCiudad* aux = ciudades;
        for (int i = 0; i < n; i++) {
            nombres[i] = aux->nombre;
            aux = aux->sig;
        }

        int dist[n];
        bool visitado[n];
        int previo[n];
        int pesoPrevio[n];

        for (int i = 0; i < n; i++) {
            dist[i] = INT_MAX;
            visitado[i] = false;
            previo[i] = -1;
            pesoPrevio[i] = 0;
        }

        int origenIdx = obtenerIndiceCiudad(origen, nombres, n);
        int destinoIdx = obtenerIndiceCiudad(destino, nombres, n);

        if (origenIdx == -1 || destinoIdx == -1) {
            cout << "Ciudad origen o destino no encontrada\n";
            return;
        }

        dist[origenIdx] = 0;

        // 2. Algoritmo de Dijkstra
        for (int i = 0; i < n - 1; i++) {
            int u = -1;
            int minDist = INT_MAX;

            for (int j = 0; j < n; j++) {
                if (!visitado[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    u = j;
                }
            }

            if (u == -1) break;
            visitado[u] = true;

            NodoCiudad* ciudadActual = buscarCiudad(nombres[u]);
            NodoRuta* ruta = ciudadActual->adyacentes;

            while (ruta) {
                int v = obtenerIndiceCiudad(ruta->destino, nombres, n);
                if (!visitado[v] && dist[u] != INT_MAX &&
                    dist[u] + ruta->distancia < dist[v]) {
                    dist[v] = dist[u] + ruta->distancia;
                    previo[v] = u;
                    pesoPrevio[v] = ruta->distancia;
                }
                ruta = ruta->sig;
            }
        }

        // 3. Mostrar resultado
        cout << "Ruta mas corta:\n";
        imprimirRutaConPesos(previo, pesoPrevio, destinoIdx, nombres);
        cout << endl;

        cout << "Distancia total: " << dist[destinoIdx] << " km\n";
        cout << endl;
    }

    int obtenerIndiceCiudad(string nombre, string ciudades[], int n) {
        for (int i = 0; i < n; i++) {
            if (ciudades[i] == nombre)
                return i;
        }
        return -1;
    }

    void imprimirRutaConPesos(
        int previo[],
        int pesoPrevio[],
        int idx,
        string ciudades[]
    ) {
        if (previo[idx] == -1) {
            cout << ciudades[idx];
            return;
        }

        imprimirRutaConPesos(previo, pesoPrevio, previo[idx], ciudades);

        cout << " --" << pesoPrevio[idx] << "--> "
             << ciudades[idx];
    }

    //corroboramos que exista una ciudad para el momento de la matriz disperza
    bool existeCiudad(const string& nombre) {
        NodoCiudad* actual = ciudades;
        while (actual) {
            if (actual->nombre == nombre)
                return true;
            actual = actual->sig;
        }
        return false;
    }

};

#endif
