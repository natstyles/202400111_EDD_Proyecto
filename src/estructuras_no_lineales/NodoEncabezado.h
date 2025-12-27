#ifndef NODOENCABEZADO_H
#define NODOENCABEZADO_H

#include <string>
using namespace std;

class NodoMatriz; //forward declaration

class NodoEncabezado {
public:
    string id;                 //ID piloto o ciudad
    NodoEncabezado* siguiente; //siguiente encabezado
    NodoMatriz* acceso;        //primer nodo de la fila/columna

    NodoEncabezado(string id) {
        this->id = id;
        siguiente = nullptr;
        acceso = nullptr;
    }
};

#endif
