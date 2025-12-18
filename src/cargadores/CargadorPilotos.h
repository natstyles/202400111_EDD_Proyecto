#ifndef CARGADORPILOTOS_H
#define CARGADORPILOTOS_H

#include <fstream>
#include <iostream>
#include <string>

#include "../modelos/Piloto.h"
#include "../estructuras_no_lineales/ArbolPilotos.h"
#include "../utils/Utilidades.h"

using namespace std;

void cargarPilotos(string ruta, ArbolPilotos& arbol) {

    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << ruta << endl;
        return;
    }

    string linea;
    int id = 0;
    string nombre;
    int horasVuelo = 0;
    string licencia;

    int contador = 0;

    while (getline(archivo, linea)) {

        if (linea.find("\"id\"") != string::npos) {
            id = stoi(linea.substr(linea.find(":") + 1));
        }
        else if (linea.find("\"nombre\"") != string::npos) {
            nombre = limpiar(linea.substr(linea.find(":") + 1));
        }
        else if (linea.find("horas_vuelo") != string::npos) {
            horasVuelo = stoi(linea.substr(linea.find(":") + 1));
        }
        else if (linea.find("\"licencia\"") != string::npos) {
            licencia = limpiar(linea.substr(linea.find(":") + 1));

            // cuando ya tenemos todos los campos
            Piloto p(id, nombre, horasVuelo, licencia);
            arbol.insertar(p);
            contador++;
        }
    }

    archivo.close();

    cout << "Pilotos cargados: " << contador << endl;
}

#endif
