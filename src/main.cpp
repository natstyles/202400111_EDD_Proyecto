#include <iostream>
#include <clocale>
#ifdef _WIN32
#include <windows.h>
#endif

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

    setlocale(LC_ALL, "");

    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

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
                cargarAviones("aviones.json", disponibles, mantenimiento);
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

                        // =================== CAMBIAR ESTADO AVIÓN ===================
                        case 1: {
                            string registro;
                            cout << "Numero de registro del avion: ";
                            cin >> registro;

                            Avion avion;

                            //disponible a mantenimiento
                            if (disponibles.extraer(registro, avion)) {
                                avion.setEstado("Mantenimiento");
                                mantenimiento.insertar(avion);
                                cout << "Avion cambiado a Mantenimiento.\n";
                            }
                            //si no está en disponible, entonces de mantenimiento a disponible
                            else if (mantenimiento.extraerPorRegistro(registro, avion)) {
                                avion.setEstado("Disponible");
                                disponibles.insertar(avion);
                                cout << "Avion cambiado a Disponible.\n";
                            }
                            else {
                                cout << "Avion no encontrado en el sistema.\n";
                            }

                            break;
                        }

                        // =================== DAR DE BAJA PILOTO ===================
                        case 2: {
                            string id;
                            cout << "ID del piloto: ";
                            cin >> id;

                            Piloto piloto;

                            // 1. Buscar piloto en hash
                            if (!tablaHashPilotos.buscar(id, piloto)) {
                                cout << "Piloto no encontrado.\n";
                                break;
                            }

                            // 2. Eliminar del árbol por HORAS
                            Piloto eliminado;
                            arbolPilotos.eliminarPorHoras(piloto.getHorasVuelo(), eliminado);

                            // 3. Eliminar de tabla hash
                            tablaHashPilotos.eliminar(id);

                            // 4. Eliminar de matriz dispersa
                            matriz.eliminarPiloto(id);

                            cout << "Piloto dado de baja correctamente.\n";
                            break;
                        }

                        // =================== ASIGNAR VUELO A PILOTO ===================
                        case 3: {
                            string idPiloto, vuelo, ciudad;
                            cout << "ID del piloto: ";
                            cin >> idPiloto;
                            cout << "Vuelo: ";
                            cin >> vuelo;
                            cout << "Ciudad destino: ";
                            cin >> ciudad;

                            matriz.insertar(idPiloto, ciudad, vuelo);
                            cout << "Vuelo asignado correctamente.\n";
                            break;
                        }

                        // =================== CARGA MASIVA ===================
                        case 4: {
                            CargadorCambios::cargarMovimientos(
                                "movimientos.txt",
                                disponibles,
                                mantenimiento,
                                arbolPilotos,
                                tablaHashPilotos,
                                grafoRutas,
                                matriz
                            );
                            cout << "Carga masiva finalizada.\n";
                            break;
                        }

                        case 5:
                            break;

                        default:
                            cout << "Opcion invalida.\n";
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