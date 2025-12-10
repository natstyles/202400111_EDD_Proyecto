#ifndef AVION_H
#define AVION_H

#include <string>
using namespace std;

class Avion {
private:
    string vuelo;
    string registro;
    string modelo;
    string fabricante;
    int ano;
    int capacidad;
    int peso;
    string aerolinea;
    string estado;

public:
    Avion() {}

    Avion(string vuelo, string registro, string modelo, string fabricante,
          int ano, int capacidad, int peso, string aerolinea, string estado) {
        this->vuelo = vuelo;
        this->registro = registro;
        this->modelo = modelo;
        this->fabricante = fabricante;
        this->ano = ano;
        this->capacidad = capacidad;
        this->peso = peso;
        this->aerolinea = aerolinea;
        this->estado = estado;
    }

    string getVuelo() { return vuelo; }
    string getRegistro() { return registro; }
    string getModelo() { return modelo; }
    string getFabricante() { return fabricante; }
    int getAno() { return ano; }
    int getCapacidad() { return capacidad; }
    int getPeso() { return peso; }
    string getAerolinea() { return aerolinea; }
    string getEstado() { return estado; }

    void setEstado(string e) { estado = e; }
};

#endif
