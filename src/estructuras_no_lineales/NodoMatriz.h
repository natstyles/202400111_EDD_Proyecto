#ifndef NODOMATRIZ_H
#define NODOMATRIZ_H

#include <string>
using namespace std;

class NodoMatriz {
public:
    string pilotoId;
    string ciudad;
    string vuelo;

    NodoMatriz* derecha;
    NodoMatriz* izquierda;
    NodoMatriz* arriba;
    NodoMatriz* abajo;

    NodoMatriz(string pilotoId, string ciudad, string vuelo) {
        this->pilotoId = pilotoId;
        this->ciudad = ciudad;
        this->vuelo = vuelo;

        derecha = izquierda = arriba = abajo = nullptr;
    }
};

#endif
