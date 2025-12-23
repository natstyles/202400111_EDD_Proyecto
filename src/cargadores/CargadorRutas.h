#ifndef CARGADORRUTAS_H
#define CARGADORRUTAS_H

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "../estructuras_no_lineales/GrafoRutas.h"

using namespace std;

class CargadorRutas {
public:
    static bool cargar(GrafoRutas& grafo) {
        ifstream file("rutas.txt");  // archivo fijo
        if (!file.is_open()) {
            cout << "No se pudo abrir el archivo rutas.txt\n";
            return false;
        }

        string linea;
        while (getline(file, linea)) {
            if (linea.empty()) continue;

            // quitar ';'
            if (linea.back() == ';')
                linea.pop_back();

            string origen, destino, distanciaStr;
            stringstream ss(linea);

            getline(ss, origen, '/');
            getline(ss, destino, '/');
            getline(ss, distanciaStr, '/');

            int distancia = stoi(distanciaStr);
            grafo.insertarRuta(origen, destino, distancia);
        }

        file.close();
        return true;
    }
};

#endif
