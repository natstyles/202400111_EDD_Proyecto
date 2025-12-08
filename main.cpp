#include <iostream>
using namespace std;
#include "ListaSimple.h"
#include "ListaDoble.h"
#include "ListaCircular.h"
#include "Fila.h"
#include "Pila.h"
#include "ListaCircularDoble.h"

int main() {
    /*ListaSimple miLista;
    miLista.insertarInicio(10);
    miLista.insertarFinal(15);
    miLista.insertarInicio(5);
    miLista.insertarFinal(20);

    miLista.visualizarLista();*/

    cout << endl;

    /*ListaDoble miListaDoble;
    miListaDoble.insertarInicio(200);
    miListaDoble.insertarInicio(150);
    miListaDoble.insertarInicio(100);
    miListaDoble.insertarInicio(50);
    miListaDoble.insertarInicio(250);

    miListaDoble.visualizarLista();*/

    ListaCircular lista;

    lista.insertarFinal(10);
    lista.insertarFinal(20);
    lista.insertarInicio(5);

    lista.visualizarLista();  // 5 -> 10 -> 20

    lista.eliminarInicio();
    lista.visualizarLista();  // 10 -> 20

    lista.eliminarFinal();
    lista.visualizarLista();  // 10

    Fila fila;
    fila.encolar(10);
    fila.encolar(20);
    fila.encolar(30);
    fila.mostrarFila();  // 10 <- 20 <- 30
    fila.desencolar();
    fila.mostrarFila();  // 20 <- 30

    cout << endl;

    Pila pila;
    pila.push(5);
    pila.push(10);
    pila.push(15);
    pila.mostrarPila();
    pila.pop();
    pila.mostrarPila();

    ListaCircularDoble listadoble;

    listadoble.insertarFinal(10);
    listadoble.insertarFinal(20);
    listadoble.insertarInicio(5);

    listadoble.mostrarAdelante(); // 5 <-> 10 <-> 20
    listadoble.mostrarAtras();    // 20 <-> 10 <-> 5

    listadoble.eliminarInicio();
    listadoble.mostrarAdelante(); // 10 <-> 20

    listadoble.eliminarFinal();
    listadoble.mostrarAdelante(); // 10

    return 0;

}