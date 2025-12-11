#ifndef NODOSIMPLE_H
#define NODOSIMPLE_H

template <typename T>
class NodoSimple {
private:
    T dato;
    NodoSimple *siguiente;

public:
    NodoSimple(T dato) {
        this->dato = dato;
        siguiente = nullptr;
    }

    T getDato() { return dato; }
    NodoSimple* getSiguiente() { return siguiente; }

    void setSiguiente(NodoSimple *sig) {
        siguiente = sig;
    }
};

#endif
