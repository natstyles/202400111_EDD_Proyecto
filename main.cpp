#include <iostream>
using namespace std;

//includes
#include "Avion.h"
#include "Pasajero.h"
#include "ColaPasajeros.h"
#include "PilaEquipaje.h"
#include "ListaCircularAviones.h"
#include "ListaDoblePasajeros.h"

void menu() {
    cout << "\n===== Gestion de aeropuerto =====\n";
    cout << "1. Registrar pasajero\n";
    cout << "2. Atender pasajero\n";
    cout << "3. Mostrar cola de pasajeros\n";
    cout << "4. Mostrar pila de equipaje\n";
    cout << "5. Mostrar pasajeros atendidos\n";
    cout << "6. Insertar avion\n";
    cout << "7. Mostrar aviones\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    ColaPasajeros cola;
    PilaEquipaje pila;
    ListaCircularAviones aviones;
    ListaDoblePasajeros listaPasajeros;

    int opcion;

    do {
        menu();
        cin >> opcion;

        switch (opcion) {
        case 1: {
            //registro de pasajero
            string nombre, pasaporte;
            int vuelo, asiento, equipaje;

            cout << "Registrando nuevo pasajero:\n";
            cout << "Nombre: ";
            cin.ignore();
            getline(cin, nombre);

            cout << "Pasaporte: ";
            getline(cin, pasaporte);

            cout << "Numero de vuelo: ";
            cin >> vuelo;

            cout << "Numero de asiento: ";
            cin >> asiento;

            cout << "Cantidad de equipaje: ";
            cin >> equipaje;

            Pasajero p(nombre, pasaporte, vuelo, asiento, equipaje);
            cola.encolar(p);

            cout << "Pasajero registrado correctamente.\n";
            break;
        }
        case 2: {
            cout << "Atendiendo a pasajero:\n";
            //atendemos al pasajero, tonces lo desencola
            if (!cola.estaVacia()) {
                Pasajero p = cola.desencolar();

                cout << "Pasajero atendido: " << p.getNombre() << endl;

                // Pasa a la lista doble ordenada
                listaPasajeros.insertarOrdenado(p);

                // Si tiene equipaje entra a la pila
                if (p.getEquipaje() > 0) {
                    pila.push(p.getEquipaje());
                }
            } else {
                cout << "No hay pasajeros en espera.\n";
            }
            break;
        }
        case 3:
            //mostrar cola de pasajeros
            cout << "\n--- COLA DE PASAJEROS ---\n";
            cola.mostrar();
            break;

        case 4:
            //mostramos pila de equipaje
            cout << "\n--- PILA DE EQUIPAJE ---\n";
            pila.mostrar();
            break;

        case 5:
            //pasajeros atendidos
            cout << "\n--- PASAJEROS ATENDIDOS ---\n";
            listaPasajeros.mostrar();
            break;

        case 6: {
            //ingresamos el avion
            string registro, modelo, estado;
            int capacidad;

            cout << "Registro del avion: ";
            cin >> registro;

            cout << "Modelo: ";
            cin >> modelo;

            cout << "Capacidad: ";
            cin >> capacidad;

            cout << "Estado (Disponible - Mantenimiento): ";
            cin >> estado;

            Avion a(registro, modelo, capacidad, estado);
            aviones.insertar(a);

            cout << "✅ Avion registrado correctamente.\n";
            break;
        }
        case 7:
            //mostramos aviones
            cout << "\n--- AVIONES REGISTRADOS ---\n";
            aviones.mostrar();
            break;

        case 0:
            cout << "Saliendo del sistema...\n";
            break;

        default:
            cout << "Opcion invalida, intenta de nuevo!\n";
        }

    } while (opcion != 0);

    return 0;
}
