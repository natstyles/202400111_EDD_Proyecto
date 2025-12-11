#ifndef CARGADORAVIONES_H
#define CARGADORAVIONES_H

#include <fstream>
#include <string>
#include <iostream>
#include "../estructuras/ListaCircularAviones.h"
#include "../utils/Utilidades.h"


using namespace std;

void cargarAviones(string ruta,
                   ListaCircularAviones &disponibles,
                   ListaCircularAviones &mantenimiento) {

    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo: " << ruta << endl;
        return;
    }

    string linea;
    string vuelo, registro, modelo, fabricante, aerolinea, estado;
    int ano = 0, capacidad = 0, peso = 0;

    int contador = 0;

    while (getline(archivo, linea)) {

        if (linea.find("\"vuelo\"") != string::npos)
            vuelo = limpiar(linea.substr(linea.find(":") + 1));

        else if (linea.find("numero_de_registro") != string::npos)
            registro = limpiar(linea.substr(linea.find(":") + 1));

        else if (linea.find("\"modelo\"") != string::npos)
            modelo = limpiar(linea.substr(linea.find(":") + 1));

        else if (linea.find("\"fabricante\"") != string::npos)
            fabricante = limpiar(linea.substr(linea.find(":") + 1));

        else if (linea.find("ano_fabricacion") != string::npos)
            ano = stoi(linea.substr(linea.find(":") + 2));

        else if (linea.find("\"capacidad\"") != string::npos)
            capacidad = stoi(linea.substr(linea.find(":") + 2));

        else if (linea.find("peso_max_despegue") != string::npos)
            peso = stoi(linea.substr(linea.find(":") + 2));

        else if (linea.find("\"aerolinea\"") != string::npos)
            aerolinea = limpiar(linea.substr(linea.find(":") + 1));

        else if (linea.find("\"estado\"") != string::npos) {
            estado = limpiar(linea.substr(linea.find(":") + 1));

            Avion a(vuelo, registro, modelo, fabricante,
                    ano, capacidad, peso, aerolinea, estado);

            if (estado == "Disponible")
                disponibles.insertar(a);
            else
                mantenimiento.insertar(a);

            contador++;
        }
    }

    archivo.close();

    cout << "Aviones cargados: " << contador << endl;

    //prueba
    cout << "\n--- AVIONES DISPONIBLES ---\n";
    disponibles.mostrar();

    cout << "\n--- AVIONES EN MANTENIMIENTO ---\n";
    mantenimiento.mostrar();
}

#endif
