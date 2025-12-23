#ifndef PILOTO_H
#define PILOTO_H

#include <string>
using namespace std;

class Piloto {
private:
    string idCompleto;   //P123456789
    string nombre;
    int horasVuelo;
    string licencia;

public:
    Piloto() : horasVuelo(0) {}

    Piloto(string idCompleto, string nombre,
           int horasVuelo, string licencia) {
        this->idCompleto = idCompleto;
        this->nombre = nombre;
        this->horasVuelo = horasVuelo;
        this->licencia = licencia;
    }

    // Getters
    string getIdCompleto() const { return idCompleto; }
    string getNombre() const { return nombre; }
    int getHorasVuelo() const { return horasVuelo; }
    string getLicencia() const { return licencia; }
};

#endif