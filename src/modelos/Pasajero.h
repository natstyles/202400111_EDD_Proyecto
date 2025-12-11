#ifndef PASAJERO_H
#define PASAJERO_H

#include <string>
using namespace std;

class Pasajero {
private:
    string nombre;
    string nacionalidad;
    string pasaporte;
    string vuelo;
    int asiento;
    string destino;
    string origen;
    int equipaje;

public:
    Pasajero() {}

    Pasajero(string nombre, string nacionalidad, string pasaporte,
             string vuelo, int asiento, string destino,
             string origen, int equipaje) {
        this->nombre = nombre;
        this->nacionalidad = nacionalidad;
        this->pasaporte = pasaporte;
        this->vuelo = vuelo;
        this->asiento = asiento;
        this->destino = destino;
        this->origen = origen;
        this->equipaje = equipaje;
    }

    string getNombre() { return nombre; }
    string getPasaporte() { return pasaporte; }
    string getVuelo() { return vuelo; }
    int getAsiento() { return asiento; }
    int getEquipaje() { return equipaje; }
};

#endif
