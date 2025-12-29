#ifndef ARBOLBAVIONES_H
#define ARBOLBAVIONES_H

#include <iostream>
#include <fstream>
#include <string>
#include "../modelos/Avion.h"
#include "../utils/Graphviz.h"
#include <vector>

using namespace std;

class NodoBAvion {
public:
    bool hoja;
    int cuenta; //cant claves
    Avion claves[4];        //orden 5 → 4 claves
    NodoBAvion* hijos[5];   //5 hijos

    NodoBAvion(bool _hoja) {
        hoja = _hoja;
        cuenta = 0;
        for (int i = 0; i < 5; i++)
            hijos[i] = nullptr;
    }
};

class ArbolBAviones {
private:
    NodoBAvion* raiz;

    void dividirHijo(NodoBAvion* padre, int i, NodoBAvion* hijo) {
        NodoBAvion* nuevo = new NodoBAvion(hijo->hoja);

        //hijo tiene 4 claves: 0 1 2 3
        //promocionamos clave[2]
        Avion promovida = hijo->claves[2];

        //hijo derecho se queda con clave[3]
        nuevo->cuenta = 1;
        nuevo->claves[0] = hijo->claves[3];

        //si no es hoja, mover hijos [3] y [4] al nuevo
        if (!hijo->hoja) {
            nuevo->hijos[0] = hijo->hijos[3];
            nuevo->hijos[1] = hijo->hijos[4];

            //limpiar del hijo para evitar doble delete
            hijo->hijos[3] = nullptr;
            hijo->hijos[4] = nullptr;
        }

        //hijo izquierdo se queda con claves [0,1]
        hijo->cuenta = 2;

        //mover hijos del padre para insertar el nuevo hijo
        for (int j = padre->cuenta; j >= i + 1; j--) {
            padre->hijos[j + 1] = padre->hijos[j];
        }
        padre->hijos[i + 1] = nuevo;

        //mover claves del padre para insertar la promovida
        for (int j = padre->cuenta - 1; j >= i; j--) {
            padre->claves[j + 1] = padre->claves[j];
        }
        padre->claves[i] = promovida;
        padre->cuenta++;
    }

    void insertarNoLleno(NodoBAvion* nodo, Avion avion) {
        int i = nodo->cuenta - 1;

        if (nodo->hoja) {
            while (i >= 0 && avion.getRegistro() < nodo->claves[i].getRegistro()) {
                nodo->claves[i + 1] = nodo->claves[i];
                i--;
            }
            nodo->claves[i + 1] = avion;
            nodo->cuenta++;
        } else {
            while (i >= 0 && avion.getRegistro() < nodo->claves[i].getRegistro())
                i--;

            i++;

            if (nodo->hijos[i] && nodo->hijos[i]->cuenta == 4) {
                dividirHijo(nodo, i, nodo->hijos[i]);

                if (avion.getRegistro() > nodo->claves[i].getRegistro())
                    i++;
            }

            insertarNoLleno(nodo->hijos[i], avion);
        }
    }

    //archivo dot
    void generarDot(NodoBAvion* nodo, ofstream& archivo) {
        if (!nodo) return;

        archivo << "node" << nodo << " [label=\"";

        // Puerto inicial
        archivo << "<f0>";

        for (int i = 0; i < nodo->cuenta; i++) {
            archivo << " | "
                    << "Registro: " << nodo->claves[i].getRegistro()
                    << "\\nVuelo: " << nodo->claves[i].getVuelo()
                    << "\\nEstado: " << nodo->claves[i].getEstado()
                    << " | <f" << (i + 1) << ">";
        }

        archivo << "\"];\n";

        // Conectar hijos usando puertos
        if (!nodo->hoja) {
            for (int i = 0; i <= nodo->cuenta; i++) {
                if (nodo->hijos[i]) {
                    archivo << "node" << nodo << ":f" << i
                            << " -> node" << nodo->hijos[i] << ";\n";
                    generarDot(nodo->hijos[i], archivo);
                }
            }
        }
    }

    //busqueda recursiva
    bool buscarRec(NodoBAvion* nodo, string registro, Avion& resultado) {
        if (!nodo) return false;

        int i = 0;
        while (i < nodo->cuenta && registro > nodo->claves[i].getRegistro())
            i++;

        if (i < nodo->cuenta && registro == nodo->claves[i].getRegistro()) {
            resultado = nodo->claves[i]; // COPIA
            return true;
        }

        if (nodo->hoja)
            return false;

        return buscarRec(nodo->hijos[i], registro, resultado);
    }

    //recorrer y recolectar
    void recolectar(NodoBAvion* nodo, vector<Avion>& lista) {
        if (!nodo) return;

        int i;
        for (i = 0; i < nodo->cuenta; i++) {
            if (!nodo->hoja)
                recolectar(nodo->hijos[i], lista);

            lista.push_back(nodo->claves[i]);
        }

        if (!nodo->hoja)
            recolectar(nodo->hijos[i], lista);
    }

    //liberar memoria
    void liberar(NodoBAvion* nodo) {
        if (!nodo) return;

        if (!nodo->hoja) {
            for (int i = 0; i <= nodo->cuenta; i++)
                liberar(nodo->hijos[i]);
        }

        delete nodo;
    }

    //Contamos aviones disponibles
    int contarRec(NodoBAvion* nodo) {
        if (!nodo) return 0;

        int total = nodo->cuenta;

        if (!nodo->hoja) {
            for (int i = 0; i <= nodo->cuenta; i++) {
                total += contarRec(nodo->hijos[i]);
            }
        }

        return total;
    }

public:
    ArbolBAviones() {
        raiz = nullptr;
    }

    void insertar(Avion avion) {
        if (!raiz) {
            raiz = new NodoBAvion(true);
            raiz->claves[0] = avion;
            raiz->cuenta = 1;
            return;
        }

        if (raiz->cuenta == 4) {
            NodoBAvion* nuevaRaiz = new NodoBAvion(false);
            nuevaRaiz->hijos[0] = raiz;
            dividirHijo(nuevaRaiz, 0, raiz);
            raiz = nuevaRaiz;
        }

        insertarNoLleno(raiz, avion);
    }

    //contamos aviones disponibles
    int contar() {
        return contarRec(raiz);
    }

    //reporte grafo
    void generarReporte(string nombre, string titulo) {
        ofstream archivo(nombre + ".dot");

        int total = contar();

        archivo << "digraph BTree {\n";
        archivo << "node [shape=record, height=.1];\n";
        archivo << "labelloc=\"t\";\n";
        archivo << "label=\"" << titulo << " (" << total << ")\";\n";
        archivo << "fontsize=20;\n";

        generarDot(raiz, archivo);

        archivo << "}\n";
        archivo.close();

        generarImagen(nombre + ".dot", nombre + ".png");
    }

    bool buscar(string registro, Avion& resultado) {
        return buscarRec(raiz, registro, resultado);
    }

    //eliminación pública
    bool eliminar(string registro) {
        if (!raiz) return false;

        vector<Avion> aviones;
        recolectar(raiz, aviones);

        bool eliminado = false;
        liberar(raiz);
        raiz = nullptr;

        for (Avion& a : aviones) {
            if (a.getRegistro() != registro)
                insertar(a);
            else
                eliminado = true;
        }

        return eliminado;
    }

    //extraer avion
    bool extraer(string registro, Avion& resultado) {
        if (!raiz) return false;

        vector<Avion> aviones;
        recolectar(raiz, aviones);

        bool encontrado = false;

        liberar(raiz);
        raiz = nullptr;

        for (Avion& a : aviones) {
            if (a.getRegistro() == registro && !encontrado) {
                resultado = a;
                encontrado = true;
            } else {
                insertar(a);
            }
        }

        return encontrado;
    }
};



#endif
