#ifndef PILOTO_H
#define PILOTO_H

#include <string>
using namespace std;

class Piloto {
private:
    int id;                 //llave para tabla hash
    string nombre;
    int horasVuelo;         //llave para ABB
    string licencia;

public:
    Piloto() {
        id = 0;
        horasVuelo = 0;
    }

    Piloto(int id, string nombre, int horasVuelo, string licencia) {
        this->id = id;
        this->nombre = nombre;
        this->horasVuelo = horasVuelo;
        this->licencia = licencia;
    }

    //get
    int getId() const { return id; }
    string getNombre() const { return nombre; }
    int getHorasVuelo() const { return horasVuelo; }
    string getLicencia() const { return licencia; }

    //set
    void setNombre(string n) { nombre = n; }
    void setHorasVuelo(int h) { horasVuelo = h; }
    void setLicencia(string l) { licencia = l; }
};

#endif
