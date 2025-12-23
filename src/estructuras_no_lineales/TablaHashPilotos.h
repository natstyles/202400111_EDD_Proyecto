#ifndef TABLAHASHPILOTOS_H
#define TABLAHASHPILOTOS_H

#include <iostream>
#include <fstream>
using namespace std;

#include "../modelos/Piloto.h"
#include "ListaSimplePilotos.h"
#include "../utils/Graphviz.h"

class TablaHashPilotos {
private:
    int tamTabla;
    ListaSimplePilotos* tabla;

    int funcionHash(int idNumerico) {
        return idNumerico % tamTabla;
    }

public:
    TablaHashPilotos() {
        tamTabla = 19;
        tabla = new ListaSimplePilotos[tamTabla];
    }

    void insertar(Piloto p) {
        int indice = funcionHash(p.getIdCompleto());
        tabla[indice].insertarFinal(p);
    }

    bool buscar(const string& idCompleto, Piloto& resultado) {
        int indice = funcionHash(idCompleto);
        return tabla[indice].buscarPorIdCompleto(idCompleto, resultado);
    }

    bool eliminar(const string& idCompleto) {
        int indice = funcionHash(idCompleto);
        return tabla[indice].eliminarPorIdCompleto(idCompleto);
    }

    void mostrar() {
        for (int i = 0; i < tamTabla; i++) {
            cout << "[" << i << "] -> ";
            tabla[i].mostrar();
        }
    }

    void generarReporte(string nombre) {
        ofstream archivo(nombre + ".dot");

        archivo << "digraph G {\n";
        archivo << "rankdir=LR;\n";
        archivo << "labelloc=\"t\";\n";
        archivo << "label=\"Tabla Hash de Pilotos (M = 19)\";\n";
        archivo << "node [shape=box];\n";

        for (int i = 0; i < tamTabla; i++) {
            string bucket = "b" + to_string(i);
            archivo << bucket << " [label=\"[" << i << "]\"];\n";
            tabla[i].generarDot(bucket, archivo);
        }

        archivo << "}\n";
        archivo.close();

        generarImagen(nombre + ".dot", nombre + ".png");
    }

    ~TablaHashPilotos() {
        delete[] tabla;
    }

    int calcularLlaveHash(const string& idCompleto) {
        int suma = 0;

        // 1. Letra inicial → ASCII
        suma += (int)idCompleto[0];

        // 2. Sumar los 9 dígitos
        for (int i = 1; i < idCompleto.length(); i++) {
            if (isdigit(idCompleto[i])) {
                suma += idCompleto[i] - '0';
            }
        }

        return suma;
    }

    int funcionHash(const string& idCompleto) {
        int llave = calcularLlaveHash(idCompleto);
        return llave % tamTabla; // M = 19
    }

};

#endif
