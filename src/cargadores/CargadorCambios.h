#ifndef CARGADORCAMBIOS_H
#define CARGADORCAMBIOS_H

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

void procesarCambios(string ruta,
                      ColaPasajeros &cola,
                      ListaDoblePasajeros &lista,
                      PilaEquipaje &pila,
                      ListaCircularAviones &disponibles,
                      ListaCircularAviones &mantenimiento) {

    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo: " << ruta << endl;
        return;
    }

    string linea;
    int contadorPasajeros = 0;
    int contadorAviones = 0;

    while (getline(archivo, linea)) {

        //equipajes
        if (linea.find("IngresoEquipajes") != string::npos) {

            if (!cola.estaVacia()) {
                Pasajero p = cola.desencolar();
                lista.insertarOrdenado(p);

                if (p.getEquipaje() > 0)
                    pila.push(p.getPasaporte(), p.getEquipaje());

                contadorPasajeros++;
            }
        }

        //movimiento de estado de los aviones FIXED
        else if (linea.find("MantenimientoAviones") != string::npos) {

            //MantenimientoAviones,Ingreso,N12345;
            string comando, accion, registro;

            size_t p1 = linea.find(",");
            size_t p2 = linea.find(",", p1 + 1);

            if (p1 != string::npos && p2 != string::npos) {
                comando = linea.substr(0, p1);
                accion = linea.substr(p1 + 1, p2 - p1 - 1);
                registro = linea.substr(p2 + 1);

                //quitar el ;
                if (!registro.empty() && registro.back() == ';')
                    registro.pop_back();

                if (accion == "Ingreso") {
                    if (disponibles.buscarYEnviarAMantenimiento(registro, mantenimiento)) {
                        contadorAviones++;
                    } else {
                        cout << "Avion no encontrado en disponibles: "
                             << registro << endl;
                    }
                }

                else if (accion == "Salida") {
                    if (mantenimiento.buscarYEnviarADisponibles(registro, disponibles)) {
                        contadorAviones++;
                    } else {
                        cout << "Avion no encontrado en mantenimiento: "
                             << registro << endl;
                    }
                }
            }
        }
    }

    archivo.close();

    cout << "\nMovimientos procesados:\n";
    cout << "- Pasajeros atendidos: " << contadorPasajeros << endl;
    cout << "- Cambios de aviones: " << contadorAviones << endl;

    //reportes
    cout << "\n--- PASAJEROS ATENDIDOS ---\n";
    lista.mostrar();

    cout << "\n--- PILA DE EQUIPAJE ---\n";
    pila.mostrar();
}

#endif
