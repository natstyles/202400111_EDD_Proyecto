#ifndef CARGADORPASAJEROS_H
#define CARGADORPASAJEROS_H

#include <fstream>
#include <string>
#include <iostream>
#include "ColaPasajeros.h"
#include "Utilidades.h"


using namespace std;

void cargarPasajeros(string ruta, ColaPasajeros &cola) {

    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo: " << ruta << endl;
        return;
    }

    string linea;
    string nombre, nacionalidad, pasaporte, vuelo, destino, origen;
    int asiento = 0, equipaje = 0;

    int contador = 0;

    while (getline(archivo, linea)) {

        if (linea.find("\"nombre\"") != string::npos)
            nombre = limpiar(linea.substr(linea.find(":") + 1));

        else if (linea.find("nacionalidad") != string::npos)
            nacionalidad = limpiar(linea.substr(linea.find(":") + 1));

        else if (linea.find("numero_de_pasaporte") != string::npos)
            pasaporte = limpiar(linea.substr(linea.find(":") + 1));

        else if (linea.find("\"vuelo\"") != string::npos)
            vuelo = limpiar(linea.substr(linea.find(":") + 1));

        else if (linea.find("\"asiento\"") != string::npos)
            asiento = stoi(linea.substr(linea.find(":") + 2));

        else if (linea.find("\"destino\"") != string::npos)
            destino = limpiar(linea.substr(linea.find(":") + 1));

        else if (linea.find("\"origen\"") != string::npos)
            origen = limpiar(linea.substr(linea.find(":") + 1));

        else if (linea.find("equipaje_facturado") != string::npos) {

            equipaje = stoi(linea.substr(linea.find(":") + 2));

            Pasajero p(nombre, nacionalidad, pasaporte,
                       vuelo, asiento, destino, origen, equipaje);

            cola.encolar(p);
            contador++;
        }
    }

    archivo.close();

    cout << "Pasajeros cargados: " << contador << endl;

    //prueba
    cout << "\n--- PASAJEROS EN COLA ---\n";
    cola.mostrar();
}

#endif
