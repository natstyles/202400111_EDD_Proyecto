#include <iostream>
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

void menu() {
    cout << "\n----- SISTEMA DE GESTION DE AEROPUERTO -----\n";
    cout << "1. Cargar aviones\n";
    cout << "2. Cambiar estado de avion\n";
    cout << "3. Reportes de aviones\n";
    cout << "4. Cargar pilotos\n";
    cout << "5. Recorridos de pilotos (ABB)\n";
    cout << "6. Reporte arbol de pilotos\n";
    cout << "7. Reporte tabla hash de pilotos\n";
    cout << "8. Dar de baja piloto\n";
    cout << "9. Cargar rutas\n";
    cout << "10. Reporte grafo de rutas\n";
    cout << "11. Recomendar ruta mas corta (Dijkstra)\n";
    cout << "12. Salir\n";
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
    TablaHashPilotos tablaHashPilotos;

    int opcion;

    do {
        menu();

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
        }

        switch (opcion) {

            //AVIONES
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

            //PILOTOS
            case 4:
                cargarPilotos("pilotos.json", arbolPilotos, tablaHashPilotos);
                cout << "Pilotos cargados en ABB y Tabla Hash.\n";
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
                tablaHashPilotos.generarReporte("tabla_hash_pilotos");
                cout << "Reporte de tabla hash generado.\n";
                break;

            case 8: {
                string idCompleto;
                cout << "Ingrese el ID del piloto a dar de baja (ej. P12345678): ";
                cin >> idCompleto;

                // Extraer parte numérica (quitamos la primera letra)
                int idNumerico = stoi(idCompleto.substr(1));

                Piloto p;

                // 1. Buscar en la tabla hash usando ID NUMÉRICO
                if (!tablaHashPilotos.buscar(idNumerico, p)) {
                    cout << "Piloto no encontrado\n";
                    break;
                }

                // 2. Eliminar del ABB usando HORAS DE VUELO
                if (arbolPilotos.eliminarPorHoras(p.getHorasVuelo(), p)) {

                    // 3. Eliminar de la tabla hash usando ID NUMÉRICO
                    tablaHashPilotos.eliminar(idNumerico);

                    cout << "Piloto dado de baja correctamente\n";
                    cout << "ID: " << p.getIdCompleto()
                         << " | Nombre: " << p.getNombre() << endl;
                } else {
                    cout << "Error al eliminar del arbol\n";
                }
                break;
            }

            //RUTAS
            case 9: {
                if (CargadorRutas::cargar(grafoRutas)) {
                    cout << "Rutas cargadas correctamente.\n";
                } else {
                    cout << "Error al cargar rutas.\n";
                }
                break;
            }

            case 10: {
                grafoRutas.generarReporte("grafo_rutas", "Grafo de Rutas");
                cout << "Reporte de rutas generado.\n";
                break;
            }

            case 11: {
                string origen, destino;
                cout << "Ciudad origen: ";
                cin >> origen;
                cout << "Ciudad destino: ";
                cin >> destino;

                grafoRutas.dijkstra(origen, destino);
                break;
            }

            case 12:
                cout << "Saliendo del sistema...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 12);

    return 0;
}