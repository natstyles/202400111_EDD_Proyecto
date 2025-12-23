#ifndef NODORUTA_H
#define NODORUTA_H

#include <string>
using namespace std;

class NodoRuta {
public:
    string destino;   //nombre de la ciudad destino
    int distancia;    //km
    NodoRuta* sig;    //siguiente ruta en la lista

    NodoRuta(string destino, int distancia) {
        this->destino = destino;
        this->distancia = distancia;
        this->sig = nullptr;
    }
};

#endif
