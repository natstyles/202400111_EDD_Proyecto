#ifndef AVION_H
#define AVION_H

#include <string>
using namespace std;

class Avion {
private:
    string registro;
    string modelo;
    int capacidad;
    string estado; //puede estar en mantenimiento o disponible

public:
    Avion() {}

    Avion(string registro, string modelo, int capacidad, string estado) {
        this->registro = registro;
        this->modelo = modelo;
        this->capacidad = capacidad;
        this->estado = estado;
    }

    //GET
    string getRegistro() { return registro; }
    string getModelo() { return modelo; }
    int getCapacidad() { return capacidad; }
    string getEstado() { return estado; }

    //SET
    void setRegistro(string r) { registro = r; }
    void setModelo(string m) { modelo = m; }
    void setCapacidad(int c) { capacidad = c; }
    void setEstado(string e) { estado = e; }
};

#endif
