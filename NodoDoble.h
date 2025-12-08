#ifndef NODODOBLE_H
#define NODODOBLE_H

class NodoDoble {
private:
    int dato;
    NodoDoble *siguiente;
    NodoDoble *anterior;

public:
    // Constructor
    NodoDoble(int dato) {
        this->dato = dato;
        this->siguiente = nullptr;
        this->anterior = nullptr;
    }

    // Getters
    int getDato() {
        return dato;
    }

    NodoDoble* getSiguiente() {
        return siguiente;
    }

    NodoDoble* getAnterior() {
        return anterior;
    }

    // Setters
    void setSiguiente(NodoDoble *sig) {
        siguiente = sig;
    }

    void setAnterior(NodoDoble *ant) {
        anterior = ant;
    }
};

#endif
