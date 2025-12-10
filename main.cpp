#include <iostream>
using namespace std;

//includes
#include "Avion.h"
#include "Pasajero.h"
#include "ColaPasajeros.h"
#include "PilaEquipaje.h"
#include "ListaCircularAviones.h"
#include "ListaDoblePasajeros.h"
#include "CargadorAviones.h"
#include "CargadorPasajeros.h"
#include "CargadorCambios.h"


void menu() {
    cout << "\n----- Gestión de aeropuerto -----\n";
    cout << "1. Carga de aviones\n";
    cout << "2. Carga de pasajeros\n";
    cout << "3. Carga de movimientos\n";
    cout << "4. Consultar pasajero\n";
    cout << "5. Visualizar reportes\n";
    cout << "6. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {

    ColaPasajeros cola;
    PilaEquipaje pila;
    ListaCircularAviones disponibles;
    ListaCircularAviones mantenimiento;
    ListaDoblePasajeros listaPasajeros;

    int opcion;

    do {
        menu();
        cin >> opcion;

        switch (opcion) {

            case 1:
                cargarAviones("aviones.json", disponibles, mantenimiento);
                cout << "Aviones cargados correctamente.\n";
                break;

            case 2:
                cargarPasajeros("pasajeros.json", cola);
                cout << "Pasajeros cargados correctamente.\n";
                break;

            case 3:
                procesarCambios("Cambios.txt", cola, listaPasajeros, pila);
                cout << "Movimientos procesados correctamente.\n";
                break;

            case 4: {
                string pass;
                cout << "Ingrese numero de pasaporte: ";
                cin >> pass;
                listaPasajeros.consultar(pass);
                break;
            }

            case 5:
                cout << "Mostrando reportes...\n";
                // 🟡 Aquí luego generamos los DOT + PNG de Graphviz
                break;

            case 6:
                cout << "Saliendo del sistema...\n";
                break;

            default:
                cout << "Opcion invalida, intenta de nuevo!\n";
        }

    } while (opcion != 6);

    return 0;
}
