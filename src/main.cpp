#include <iostream>
using namespace std;

//Estructuras
#include "estructuras/ListaCircularAviones.h"
#include "estructuras_no_lineales/ArbolBAviones.h"

//Cargadores
#include "cargadores/CargadorAviones.h"

void menu() {
    cout << "\n----- SISTEMA DE GESTION DE AEROPUERTO -----\n";
    cout << "1. Carga de aviones\n";
    cout << "2. Cambiar estado de avion\n";
    cout << "3. Generar reportes\n";
    cout << "4. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    ArbolBAviones disponibles;              //Árbol B (orden 5)
    ListaCircularAviones mantenimiento;     //Lista circular doble

    int opcion;

    do {
        menu();

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
        }

        switch (opcion) {

            case 1: {
                cargarAviones("avionesTest2.json", disponibles, mantenimiento);
                cout << "Aviones cargados correctamente.\n";
                break;
            }

            case 2: {
                string registro;
                cout << "Ingrese el numero de registro del avion: ";
                cin >> registro;

                Avion a;

                // Intentar sacar de disponibles
                if (disponibles.extraer(registro, a)) {
                    a.setEstado("Mantenimiento");
                    mantenimiento.insertar(a);
                    cout << "Avion enviado a mantenimiento.\n";
                }
                else {
                    // Intentar sacar de mantenimiento
                    if (mantenimiento.extraerPorRegistro(registro, a)) {
                        a.setEstado("Disponible");
                        disponibles.insertar(a);
                        cout << "Avion enviado a disponibles.\n";
                    }
                    else {
                        cout << "Avion no encontrado.\n";
                    }
                }
                break;
            }

            case 3: {
                disponibles.generarReporte(
                    "aviones_disponibles",
                    "Arbol B - Aviones Disponibles"
                );

                mantenimiento.generarReporte(
                    "aviones_mantenimiento",
                    "Lista Circular - Aviones en Mantenimiento"
                );

                cout << "Reportes generados correctamente.\n";
                break;
            }

            case 4:
                cout << "Saliendo del sistema...\n";
                break;

            default:
                cout << "Opcion invalida, intente de nuevo.\n";
        }

    } while (opcion != 4);

    return 0;
}