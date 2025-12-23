#ifndef CARGADORPILOTOS_H
#define CARGADORPILOTOS_H

#include <fstream>
#include <iostream>
#include <string>
#include <cctype>

#include "../modelos/Piloto.h"
#include "../estructuras_no_lineales/ArbolPilotos.h"
#include "../estructuras_no_lineales/TablaHashPilotos.h"
#include "../utils/Utilidades.h"

using namespace std;

void cargarPilotos(
    string ruta,
    ArbolPilotos& arbol,
    TablaHashPilotos& hash
) {
    ifstream archivo(ruta);

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << ruta << endl;
        return;
    }

    string linea;
    string idCompleto = "";
    string nombre = "";
    int horasVuelo = 0;
    string licencia = "";

    int contador = 0;

    while (getline(archivo, linea)) {

        // ID del piloto
        if (linea.find("\"numero_de_id\"") != string::npos ||
            linea.find("\"id\"") != string::npos) {

            idCompleto = limpiar(linea.substr(linea.find(":") + 1));

            // Validación: letra + 9 dígitos
            bool valido = true;

            if (idCompleto.length() != 9 || !isalpha(idCompleto[0])) {
                valido = false;
            } else {
                for (int i = 1; i < 9; i++) {
                    if (!isdigit(idCompleto[i])) {
                        valido = false;
                        break;
                    }
                }
            }

            if (!valido) {
                cout << "ID de piloto invalido: " << idCompleto << endl;
                idCompleto = "";
            }
        }

        // Nombre
        else if (linea.find("\"nombre\"") != string::npos) {
            nombre = limpiar(linea.substr(linea.find(":") + 1));
        }

        // Horas de vuelo
        else if (linea.find("\"horas_de_vuelo\"") != string::npos ||
                 linea.find("\"horas_vuelo\"") != string::npos) {

            horasVuelo = stoi(linea.substr(linea.find(":") + 1));
        }

        // Licencia (último campo → se crea el piloto)
        else if (linea.find("\"tipo_de_licencia\"") != string::npos ||
                 linea.find("\"licencia\"") != string::npos) {

            licencia = limpiar(linea.substr(linea.find(":") + 1));

            if (idCompleto != "") {
                Piloto p(idCompleto, nombre, horasVuelo, licencia);
                arbol.insertar(p);
                hash.insertar(p);
                contador++;
            }

            // Reset de campos para el siguiente piloto
            idCompleto = "";
            nombre = "";
            horasVuelo = 0;
            licencia = "";
        }
    }

    archivo.close();

    cout << "Pilotos cargados correctamente: " << contador << endl;
}

#endif