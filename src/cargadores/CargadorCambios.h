#ifndef CARGADORCAMBIOS_H
#define CARGADORCAMBIOS_H

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

void procesarCambios(string ruta,
                      ColaPasajeros &cola,
                      ListaDoblePasajeros &lista,
                      PilaEquipaje &pila) {

    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo: " << ruta << endl;
        return;
    }

    string linea;
    int contador = 0;

    while (getline(archivo, linea)) {

        if (linea.find("IngresoEquipajes") != string::npos) {

            if (!cola.estaVacia()) {

                Pasajero p = cola.desencolar();
                lista.insertarOrdenado(p);

                if (p.getEquipaje() > 0)
                    pila.push(p.getPasaporte(), p.getEquipaje());

                contador++;
            }
        }
    }

    archivo.close();

    cout << "Movimientos procesados: " << contador << endl;

    //prueba
    cout << "\n--- PASAJEROS ATENDIDOS ---\n";
    lista.mostrar();

    cout << "\n--- PILA DE EQUIPAJE ---\n";
    pila.mostrar();
}

#endif
