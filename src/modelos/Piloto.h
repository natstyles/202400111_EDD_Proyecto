#ifndef PILOTO_H
#define PILOTO_H

#include <string>
using namespace std;

class Piloto {
private:
    string idCompleto;
    int idNumerico;
    string nombre;
    int horasVuelo;
    string licencia;

public:
    Piloto() {
        idNumerico = 0;
        horasVuelo = 0;
    }

    Piloto(string idCompleto, int idNumerico,
           string nombre, int horasVuelo, string licencia) {
        this->idCompleto = idCompleto;
        this->idNumerico = idNumerico;
        this->nombre = nombre;
        this->horasVuelo = horasVuelo;
        this->licencia = licencia;
    }

    // Getters
    string getIdCompleto() const { return idCompleto; }
    int getIdNumerico() const { return idNumerico; }
    string getNombre() const { return nombre; }
    int getHorasVuelo() const { return horasVuelo; }
    string getLicencia() const { return licencia; }
};

#endif