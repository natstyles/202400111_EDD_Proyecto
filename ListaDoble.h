#include <iostream>
using namespace std;

class ListaDoble {
    private:
        //Necesitamos una referencia del primer y ultimo nodo de la lista
        Nodo *primero;
        Nodo *ultimo;
    public:
        //Constructor
        ListaDoble();

        bool estaVacia() {
            return ((primero == nullptr) & (ultimo == nullptr));
        }

        void insertarInicio(int dato) {
            Nodo *nuevo = new Nodo(dato);
            if (ListaDoble::estaVacia()) {
                //Como solo existe el nuevo nodo creado, este será el primero y el último
                primero = ultimo = nuevo;
            }
            else {
                primero->setAnterior(nuevo); //Se enlaza el primer nodo al nuevo
                nuevo->setSiguiente(primero); //Se enlaza el nuevo nodo al primero
                primero = nuevo; //Se verifica que el nodo creado sea el primero
            }
        }

        void insertarFinal(int dato) {
            Nodo *nuevo = new Nodo(dato);
            if (ListaDoble::estaVacia()) {
                primero = ultimo = nuevo;
            }
            else {
                ultimo->setSiguiente(nuevo); //Se enlaza el ultimo nodo al nuevo
                nuevo->setAnterior(ultimo); //Se enlaza el nuevo nodo al ultimo
                ultimo = nuevo; //Se verifica que el nodo creado sea el ultimo
            }
        }

        void eliminarInicio() {
            if (ListaDoble::estaVacia()) {
                cout << "Lista esta vacia" << endl;
            }
            else {
                if (primero == ultimo) { //Si primero y ultimo son iguales, solo hay un elemento en la lista
                    delete primero;
                    primero = ultimo = nullptr; //Eliminamos las referencias
                }
                else {
                    Nodo *segundo = primero->getSiguiente(); //Guardamos la referencia del segundo nodo de la lista
                    segundo->setAnterior(nullptr);
                    delete primero;
                    primero = segundo; //Verifico que el segundo nodo pase a ser el primero
                }
            }
        }

        void eliminarFinal() {
            if (ListaDoble::estaVacia()) {
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
                    Nodo *antepenultimo = (ultimo->getAnterior()); //Guardo la referencia del antepenultimo
                    delete ultimo;
                    antepenultimo->setSiguiente(nullptr);
                    ultimo = antepenultimo; //Verificamos que el antepenultimo nodo pase a ser el ultimo
                }
            }
        }

        void visualizarLista() {
            if (ListaDoble::estaVacia()) {
                cout << "Lista esta vacia" << endl;
            }
            else {
                int nodoDato;
                Nodo* actual = primero;
                while (actual != nullptr) {
                    nodoDato = actual->getDato();
                    cout << nodoDato << endl;
                    actual = actual->getSiguiente();
                }
            }
        }

        ~ListaDoble();
};

ListaDoble::ListaDoble() {
    primero = nullptr;
    ultimo = nullptr;
}

ListaDoble::~ListaDoble() {

}