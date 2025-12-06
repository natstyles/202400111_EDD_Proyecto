#include <iostream>
using namespace std;

class Nodo {
private:
    int dato;
    Nodo *siguiente;
    Nodo *anterior;

public:
    Nodo(int dato);

    Nodo *getSiguiente() {
        return this->siguiente;
    };

    Nodo *getAnterior() {
        return this->anterior;
    }

    void setSiguiente(Nodo *siguiente) {
        this->siguiente = siguiente;
    }

    void setAnterior(Nodo *anterior) {
        this->anterior = anterior;
    }

    int getDato() {
        return this->dato;
    }

    void setDato(int dato) {
        this->dato = dato;
    }

    ~Nodo();
};

//Constructor
Nodo::Nodo(int dato) {
    this->dato = dato;
    this->siguiente = nullptr;
    this->anterior = nullptr;
}

//Destructor
Nodo::~Nodo() {

}