#ifndef NODOCIUDAD_H
#define NODOCIUDAD_H

#include <string>
#include "NodoRuta.h"
using namespace std;

class NodoCiudad {
public:
    string nombre;
    NodoRuta* adyacentes;   //lista de rutas salientes
    NodoCiudad* sig;        //siguiente ciudad en el grafo

    NodoCiudad(string nombre) {
        this->nombre = nombre;
        this->adyacentes = nullptr;
        this->sig = nullptr;
    }

    //Inserta una ruta saliente
    void agregarRuta(string destino, int distancia) {
        NodoRuta* nueva = new NodoRuta(destino, distancia);
        if (!adyacentes) {
            adyacentes = nueva;
        } else {
            NodoRuta* aux = adyacentes;
            while (aux->sig) aux = aux->sig;
            aux->sig = nueva;
        }
    }
};

#endif
