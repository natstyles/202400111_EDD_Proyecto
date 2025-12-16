#ifndef EQUIPAJE_H
#define EQUIPAJE_H

#include <string>
using namespace std;

class Equipaje {
private:
    string pasaporte;
    int cantidad;

public:
    //constructor vacío
    Equipaje() {
        pasaporte = "";
        cantidad = 0;
    }

    //constructor
    Equipaje(string p, int c) {
        pasaporte = p;
        cantidad = c;
    }

    string getPasaporte() { return pasaporte; }
    int getCantidad() { return cantidad; }
};

#endif
