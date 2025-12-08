#ifndef PASAJERO_H
#define PASAJERO_H

#include <string>
using namespace std;

class Pasajero {
private:
    string nombre;
    string pasaporte;
    int vuelo;
    int asiento;
    int equipaje;

public:
    Pasajero() {}

    Pasajero(string nombre, string pasaporte, int vuelo, int asiento, int equipaje) {
        this->nombre = nombre;
        this->pasaporte = pasaporte;
        this->vuelo = vuelo;
        this->asiento = asiento;
        this->equipaje = equipaje;
    }

    //GET
    string getNombre() { return nombre; }
    string getPasaporte() { return pasaporte; }
    int getVuelo() { return vuelo; }
    int getAsiento() { return asiento; }
    int getEquipaje() { return equipaje; }
};

#endif
