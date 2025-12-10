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
    cout << "\n----- Gestion de aeropuerto -----\n";
    cout << "1. Carga de aviones\n";
    cout << "2. Carga de pasajeros\n";
    cout << "3. Carga de movimientos\n";
    cout << "4. Consultar pasajero\n";
    cout << "5. Visualizar reportes\n";
    cout << "6. Visualizar estructuras\n";
    cout << "7. Salir\n";
    cout << "Seleccione una opcion: ";
}

//ver listas de pasajeros, aviones y maletas en consola!
void menuVisualizacion() {
    cout << "\n----- Menu de vistas -----\n";
    cout << "1. Mostrar cola de pasajeros\n";
    cout << "2. Mostrar pasajeros atendidos\n";
    cout << "3. Mostrar aviones disponibles\n";
    cout << "4. Mostrar aviones en mantenimiento\n";
    cout << "5. Regresar al menu principal\n";
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
                disponibles.generarReporte("aviones_disponibles", "Aviones Disponibles");
                mantenimiento.generarReporte("aviones_mantenimiento", "Aviones en Mantenimiento");
                cola.generarReporte("cola_pasajeros", "Cola de Pasajeros Registrados");
                pila.generarReporte("pila_equipaje", "Pila de Equipaje Facturado");
                listaPasajeros.generarReporte("lista_pasajeros", "Pasajeros Atendidos");
                break;

            case 6: {
                int op2;
                do {
                    menuVisualizacion();
                    cin >> op2;

                    switch (op2) {
                        case 1:
                            cout << "\n--- Cola de pasajeros ---\n";
                            cola.mostrar();
                            break;

                        case 2:
                            cout << "\n--- Pasajeros atendidos ---\n";
                            listaPasajeros.mostrar();
                            break;

                        case 3:
                            cout << "\n--- Aviones disponibles ---\n";
                            disponibles.mostrar();
                            break;

                        case 4:
                            cout << "\n--- Aviones en mantenimientos ---\n";
                            mantenimiento.mostrar();
                            break;

                        case 5:
                            cout << "Regresando al menu principal...\n";
                            break;

                        default:
                            cout << "Opcion invalida, intenta de nuevo.\n";
                    }

                } while (op2 != 5);

                break;
            }

            case 7:
                cout << "Saliendo del sistema...\n";
                break;

            default:
                cout << "Opcion invalida, intenta de nuevo!\n";
        }

    } while (opcion != 7);

    return 0;
}
