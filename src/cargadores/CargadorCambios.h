#ifndef CARGADORCAMBIOS_H
#define CARGADORCAMBIOS_H

#include <fstream>
#include <string>
#include <iostream>

#include "../estructuras/ListaCircularAviones.h"
#include "../estructuras_no_lineales/ArbolBAviones.h"
#include "../estructuras_no_lineales/ArbolPilotos.h"
#include "../estructuras_no_lineales/TablaHashPilotos.h"
#include "../estructuras_no_lineales/GrafoRutas.h"
#include "../estructuras_no_lineales/MatrizDispersa.h"

using namespace std;

class CargadorCambios {
public:
    static void cargarMovimientos(
        const string& rutaArchivo,
        ArbolBAviones& disponibles,
        ListaCircularAviones& mantenimiento,
        ArbolPilotos& arbolPilotos,
        TablaHashPilotos& tablaHashPilotos,
        GrafoRutas& grafoRutas,
        MatrizDispersa& matriz
    ) {

        ifstream archivo(rutaArchivo);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo de movimientos.\n";
            return;
        }

        string linea;
        while (getline(archivo, linea)) {

            if (linea.find("MantenimientoAviones") != string::npos) {

                //Quitar el punto y coma final
                if (!linea.empty() && linea.back() == ';') {
                    linea.pop_back();
                }

                //Separar por comas
                size_t p1 = linea.find(",");
                size_t p2 = linea.find(",", p1 + 1);

                string accion   = linea.substr(p1 + 1, p2 - p1 - 1);
                string registro = linea.substr(p2 + 1);

                Avion a;

                //Ingreso → Disponible → Mantenimiento
                if (accion == "Ingreso") {
                    if (disponibles.extraer(registro, a)) {
                        a.setEstado("Mantenimiento");
                        mantenimiento.insertar(a);
                    }
                }
                //Salida → Mantenimiento → Disponible
                else if (accion == "Salida") {
                    if (mantenimiento.extraerPorRegistro(registro, a)) {
                        a.setEstado("Disponible");
                        disponibles.insertar(a);
                    }
                }
            }

            //Dar de baja
            else if (linea.find("DarDeBaja") != string::npos) {

                int p1 = linea.find("(");
                int p2 = linea.find(")");

                string id = linea.substr(p1 + 1, p2 - p1 - 1);

                Piloto p;
                if (tablaHashPilotos.buscar(id, p)) {
                    arbolPilotos.eliminarPorHoras(p.getHorasVuelo(), p);
                    tablaHashPilotos.eliminar(id);
                    matriz.eliminarPiloto(id);
                }
            }

            //Asignar Vuelos
            else if (linea.find("AsignarVuelo") != string::npos) {

                int p1 = linea.find("(");
                int p2 = linea.find(",");
                int p3 = linea.find(",", p2 + 1);
                int p4 = linea.find(")");

                string pilotoId = linea.substr(p1 + 1, p2 - p1 - 1);
                string ciudad   = linea.substr(p2 + 1, p3 - p2 - 1);
                string registro = linea.substr(p3 + 1, p4 - p3 - 1);

                Piloto p;
                Avion a;

                if (tablaHashPilotos.buscar(pilotoId, p) &&
                    grafoRutas.existeCiudad(ciudad) &&
                    (disponibles.buscar(registro, a) || mantenimiento.buscarPorRegistro(registro, a))) {

                    matriz.insertar(pilotoId, ciudad, a.getVuelo());
                }
            }
        }

        archivo.close();
        cout << "Carga masiva de movimientos finalizada correctamente.\n";
    }
};

#endif