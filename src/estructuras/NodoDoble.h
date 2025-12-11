#ifndef NODODOBLE_H
#define NODODOBLE_H

template <typename T>
class NodoDoble {
private:
    T dato;
    NodoDoble *siguiente;
    NodoDoble *anterior;

public:
    NodoDoble(T dato) {
        this->dato = dato;
        siguiente = nullptr;
        anterior = nullptr;
    }

    T getDato() { return dato; }
    NodoDoble* getSiguiente() { return siguiente; }
    NodoDoble* getAnterior() { return anterior; }

    void setSiguiente(NodoDoble *sig) { siguiente = sig; }
    void setAnterior(NodoDoble *ant) { anterior = ant; }
};

#endif
