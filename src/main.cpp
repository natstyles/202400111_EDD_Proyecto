#include <iostream>

#include "cargadores/CargadorCambios.h"
using namespace std;

//AVIONES
#include "estructuras/ListaCircularAviones.h"
#include "estructuras_no_lineales/ArbolBAviones.h"
#include "cargadores/CargadorAviones.h"

//PILOTOS
#include "estructuras_no_lineales/ArbolPilotos.h"
#include "estructuras_no_lineales/TablaHashPilotos.h"
#include "cargadores/CargadorPilotos.h"

//RUTAS
#include "estructuras_no_lineales/GrafoRutas.h"
#include "cargadores/CargadorRutas.h"
GrafoRutas grafoRutas;

//MATRIZ DISPERSA
#include "estructuras_no_lineales/MatrizDispersa.h"
MatrizDispersa matriz;

void menuPrincipal() {
    cout << "\n----- SISTEMA DE GESTION DE AEROPUERTO -----\n";
    cout << "1. Carga de aviones\n";
    cout << "2. Carga de pilotos\n";
    cout << "3. Carga de rutas\n";
    cout << "4. Carga de movimientos\n";
    cout << "5. Consulta de horas de vuelo (pilotos)\n";
    cout << "6. Recomendar ruta\n";
    cout << "7. Visualizar reportes\n";
    cout << "8. Salir\n";
    cout << "Seleccione una opcion: ";
}

void menuMovimientos() {
    cout << "\n--- CARGA DE MOVIMIENTOS ---\n";
    cout << "1. Cambiar estado de avion\n";
    cout << "2. Dar de baja piloto\n";
    cout << "3. Asignar vuelo a piloto\n";
    cout << "4. Carga masiva de movimientos\n";
    cout << "5. Regresar\n";
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

void menuReportes() {
    cout << "\n--- REPORTES ---\n";
    cout << "1. Aviones (Arbol B y Lista)\n";
    cout << "2. Arbol binario de pilotos\n";
    cout << "3. Tabla hash de pilotos\n";
    cout << "4. Grafo de rutas\n";
    cout << "5. Matriz dispersa\n";
    cout << "6. Regresar\n";
    cout << "Seleccione una opcion: ";
}

int main() {

    //AVIONES
    ArbolBAviones disponibles;
    ListaCircularAviones mantenimiento;

    //PILOTOS
    ArbolPilotos arbolPilotos;
    TablaHashPilotos tablaHashPilotos;

    int opcion;

    do {
        menuPrincipal();
        cin >> opcion;

        switch (opcion) {

            case 1:
                cargarAviones("avionesTest2.json", disponibles, mantenimiento);
                break;

            case 2:
                cargarPilotos("pilotos.json", arbolPilotos, tablaHashPilotos);
                cout << "Pilotos cargados correctamente.\n";
                break;

            case 3:
                if (CargadorRutas::cargar(grafoRutas))
                    cout << "Rutas cargadas correctamente.\n";
                else
                    cout << "Error al cargar rutas.\n";
                break;

            case 4: {
                int opMov;
                do {
                    menuMovimientos();
                    cin >> opMov;

                    switch (opMov) {

                        case 4:
                            CargadorCambios::cargarMovimientos(
                                "movimientosTest2.txt",
                                disponibles,
                                mantenimiento,
                                arbolPilotos,
                                tablaHashPilotos,
                                grafoRutas,
                                matriz
                            );
                            break;
                    }

                } while (opMov != 5);
                break;
            }

            case 5: {
                int op;
                do {
                    menuPilotos();
                    cin >> op;

                    switch (op) {
                        case 1:
                            arbolPilotos.mostrarPreOrden();
                            break;
                        case 2:
                            arbolPilotos.mostrarInOrden();
                            break;
                        case 3:
                            arbolPilotos.mostrarPostOrden();
                            break;
                    }
                } while (op != 4);
                break;
            }

            case 6: {
                string origen, destino;
                cout << "Ciudad origen: ";
                cin >> origen;
                cout << "Ciudad destino: ";
                cin >> destino;
                grafoRutas.dijkstra(origen, destino);
                break;
            }

            case 7: {
                int opRep;
                do {
                    menuReportes();
                    cin >> opRep;

                    switch (opRep) {
                        case 1:
                            disponibles.generarReporte("aviones_disponibles", "Arbol B - Aviones");
                            mantenimiento.generarReporte("aviones_mantenimiento", "Lista - Mantenimiento");
                            break;
                        case 2:
                            arbolPilotos.generarReporte();
                            break;
                        case 3:
                            tablaHashPilotos.generarReporte("tabla_hash_pilotos");
                            break;
                        case 4:
                            grafoRutas.generarReporte("grafo_rutas", "Grafo de rutas");
                            break;
                        case 5:
                            matriz.generarReporte("matriz_dispersa");
                            break;
                    }
                } while (opRep != 6);
                break;
            }

            case 8:
                cout << "Saliendo del sistema...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 8);

    return 0;
}