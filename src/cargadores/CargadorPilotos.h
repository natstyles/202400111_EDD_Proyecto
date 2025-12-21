#ifndef CARGADORPILOTOS_H
#define CARGADORPILOTOS_H

#include <fstream>
#include <iostream>
#include <string>

#include "../modelos/Piloto.h"
#include "../estructuras_no_lineales/ArbolPilotos.h"
#include "../utils/Utilidades.h"

using namespace std;

void cargarPilotos(string ruta, ArbolPilotos& arbol, TablaHashPilotos& hash) {

    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << ruta << endl;
        return;
    }

    string linea;
    string idCompleto = "";
    int idNumerico = 0;
    string nombre;
    int horasVuelo = 0;
    string licencia;

    int contador = 0;

    while (getline(archivo, linea)) {

        if (linea.find("\"numero_de_id\"") != string::npos ||
            linea.find("\"id\"") != string::npos) {

            // Ejemplo: "P12345678"
            idCompleto = limpiar(linea.substr(linea.find(":") + 1));

            // Quitamos la primera letra (P) y convertimos a int
            idNumerico = stoi(idCompleto.substr(1));
            }
        else if (linea.find("\"nombre\"") != string::npos) {
            nombre = limpiar(linea.substr(linea.find(":") + 1));
        }
        else if (linea.find("\"horas_de_vuelo\"") != string::npos ||
                 linea.find("\"horas_vuelo\"") != string::npos) {

            horasVuelo = stoi(linea.substr(linea.find(":") + 1));
                 }
        else if (linea.find("\"tipo_de_licencia\"") != string::npos ||
                 linea.find("\"licencia\"") != string::npos) {

            licencia = limpiar(linea.substr(linea.find(":") + 1));

            // Cuando ya tenemos todos los campos
            Piloto p(idCompleto, idNumerico, nombre, horasVuelo, licencia);
            arbol.insertar(p);
            hash.insertar(p);
            contador++;
                 }
    }

    archivo.close();

    cout << "Pilotos cargados: " << contador << endl;
}

#endif
