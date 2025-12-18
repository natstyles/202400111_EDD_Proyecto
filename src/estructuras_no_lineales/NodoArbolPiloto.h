#ifndef NODOARBOLPILOTO_H
#define NODOARBOLPILOTO_H

#include "../modelos/Piloto.h"

class NodoArbolPiloto {
private:
    Piloto piloto;
    NodoArbolPiloto* izq;
    NodoArbolPiloto* der;

public:
    NodoArbolPiloto(Piloto p) {
        piloto = p;
        izq = nullptr;
        der = nullptr;
    }

    Piloto getPiloto() {
        return piloto;
    }

    void setPiloto(Piloto p) {
        piloto = p;
    }

    NodoArbolPiloto* getIzq() {
        return izq;
    }

    void setIzq(NodoArbolPiloto* n) {
        izq = n;
    }

    NodoArbolPiloto* getDer() {
        return der;
    }

    void setDer(NodoArbolPiloto* n) {
        der = n;
    }
};

#endif
