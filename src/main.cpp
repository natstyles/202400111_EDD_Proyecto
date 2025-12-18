#include <iostream>
using namespace std;

//AVIONES
#include "estructuras/ListaCircularAviones.h"
#include "estructuras_no_lineales/ArbolBAviones.h"
#include "cargadores/CargadorAviones.h"

//PILOTOS
#include "estructuras_no_lineales/ArbolPilotos.h"
#include "cargadores/CargadorPilotos.h"

void menu() {
    cout << "\n----- SISTEMA DE GESTION DE AEROPUERTO -----\n";
    cout << "1. Cargar aviones\n";
    cout << "2. Cambiar estado de avion\n";
    cout << "3. Reportes de aviones\n";
    cout << "4. Cargar pilotos\n";
    cout << "5. Recorridos de pilotos\n";
    cout << "6. Reporte arbol de pilotos\n";
    cout << "7. Salir\n";
    cout << "Seleccione una opcion: ";
}

void menuPilotos() {
    cout << "\n--- RECORRIDOS ABB PILOTOS ---\n";
    cout << "1. Preorden\n";
    cout << "2. Inorden\n";
    cout << "3. Postorden\n";
    cout << "4. Regresar\n";
    cout << "Seleccione una opcion: ";
}

int main() {

    //AVIONES
    ArbolBAviones disponibles;
    ListaCircularAviones mantenimiento;

    //PILOTOS
    ArbolPilotos arbolPilotos;

    int opcion;

    do {
        menu();

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
        }

        switch (opcion) {

            case 1:
                cargarAviones("avionesTest2.json", disponibles, mantenimiento);
                break;

            case 2: {
                string registro;
                cout << "Ingrese el numero de registro del avion: ";
                cin >> registro;

                Avion a;
                if (disponibles.extraer(registro, a)) {
                    a.setEstado("Mantenimiento");
                    mantenimiento.insertar(a);
                    cout << "Avion enviado a mantenimiento.\n";
                }
                else if (mantenimiento.extraerPorRegistro(registro, a)) {
                    a.setEstado("Disponible");
                    disponibles.insertar(a);
                    cout << "Avion enviado a disponibles.\n";
                }
                else {
                    cout << "Avion no encontrado.\n";
                }
                break;
            }

            case 3:
                disponibles.generarReporte(
                    "aviones_disponibles",
                    "Arbol B - Aviones Disponibles"
                );
                mantenimiento.generarReporte(
                    "aviones_mantenimiento",
                    "Lista Circular - Aviones en Mantenimiento"
                );
                cout << "Reportes de aviones generados.\n";
                break;

            case 4:
                cargarPilotos("pilotos.json", arbolPilotos);
                break;

            case 5: {
                int op;
                do {
                    menuPilotos();
                    cin >> op;

                    switch (op) {
                        case 1:
                            cout << "\n--- PREORDEN ---\n";
                            arbolPilotos.mostrarPreOrden();
                            break;
                        case 2:
                            cout << "\n--- INORDEN ---\n";
                            arbolPilotos.mostrarInOrden();
                            break;
                        case 3:
                            cout << "\n--- POSTORDEN ---\n";
                            arbolPilotos.mostrarPostOrden();
                            break;
                        case 4:
                            break;
                        default:
                            cout << "Opcion invalida\n";
                    }
                } while (op != 4);
                break;
            }

            case 6:
                arbolPilotos.generarReporte();
                cout << "Reporte del arbol de pilotos generado.\n";
                break;

            case 7:
                cout << "Saliendo del sistema...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 7);

    return 0;
}
