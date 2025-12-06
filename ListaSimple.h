#include <iostream>
using namespace std;
#include "Nodo.h"

class ListaSimple {
    private:
        //Necesitamos una referencia del primer y ultimo nodo de la lista
        Nodo *primero;
        Nodo *ultimo;
    public:
        //Constructor
        ListaSimple();

        bool estaVacia() {
            return ((primero == nullptr) & (ultimo == nullptr));
        }

        void insertarInicio(int dato) {
            Nodo *nuevo = new Nodo(dato);
            if (ListaSimple::estaVacia()) {
                //Como solo existe el nuevo nodo creado, este será el primero y el último
                primero = ultimo = nuevo;
            }
            else {
                nuevo->setSiguiente(primero); //Se enlaza el nuevo nodo al primero
                primero = nuevo; //Se verifica que el nodo creado sea el primero
            }
        }

        void insertarFinal(int dato) {
            Nodo *nuevo = new Nodo(dato);
            if (ListaSimple::estaVacia()) {
                primero = ultimo = nuevo;
            }
            else {
                ultimo->setSiguiente(nuevo); //Se enlaza el ultimo nodo al nuevo
                ultimo = nuevo;
            }
        }

        void eliminarInicio() {
            if (ListaSimple::estaVacia()) {
                cout << "Lista esta vacia" << endl;
            }
            else {
                if (primero == ultimo) { //Si primero y ultimo son iguales, solo hay un elemento en la lista
                    delete primero;
                    primero = ultimo = nullptr; //Eliminamos las referencias
                }
                else {
                    Nodo *segundo = primero->getSiguiente(); //Guardamos la referencia del segundo nodo
                    delete primero;
                    primero = segundo; //Verifico que el segundo nodo pase ahora a ser el primero
                }
            }
        }

        void eliminarFinal() {
            if (ListaSimple::estaVacia()) {
                cout << "Lista esta vacia" << endl;
            }
            else {
                Nodo *temporal = primero;
                //Si namas hay uno
                if (primero == ultimo) {
                    delete primero;
                    primero = ultimo = nullptr; //Se eliminan las referencias
                }
                else {
                    while (temporal != nullptr) {
                        if (temporal->getSiguiente() == ultimo) { //Si el siguiente de temporal es el ultimo, entonces encontrar el antepenúltimo
                            delete ultimo;
                            temporal->setSiguiente(nullptr); //Se cambia el enlace quitando la referencia del ultimo nodo
                            ultimo = temporal; //Se verifica que temporal pasa a ser el ultimo
                        }
                        temporal = temporal->getSiguiente(); //Nos aseguramos que estamos recorriendo la lista
                    }
                }
            }
        }

        void visualizarLista() {
            if (ListaSimple::estaVacia()) {
                cout << "Lista esta vacia" << endl;
            }
            else {
                int nodoDato;
                Nodo *actual = primero;
                while (actual != nullptr) {
                    nodoDato = actual->getDato();
                    cout << nodoDato << (actual->getSiguiente() != nullptr ? " -> " : "\n");
                    actual = actual->getSiguiente();
                }
            }
        }

        ~ListaSimple();
};

ListaSimple::ListaSimple() {
    primero = nullptr;
    ultimo = nullptr;
}

ListaSimple::~ListaSimple() {

}