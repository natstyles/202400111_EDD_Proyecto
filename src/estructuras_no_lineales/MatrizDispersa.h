#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include <iostream>
#include <fstream>
#include <string>

//definiciones de nodos
#include "NodoEncabezado.h"
#include "NodoMatriz.h"

using namespace std;

class MatrizDispersa {
private:
    NodoEncabezado* filas;    //VUELOS (Eje Y)
    NodoEncabezado* columnas; //CIUDADES DESTINO (Eje X)


    NodoEncabezado* obtenerFila(string vuelo) {
        NodoEncabezado* actual = filas;
        NodoEncabezado* anterior = nullptr;

        while (actual) {
            if (actual->id == vuelo) return actual; //Vuelo ya existe
            if (actual->id > vuelo) break;          //Mantener orden alfabético
            anterior = actual;
            actual = actual->siguiente;
        }

        //Insertar nuevo vuelo
        NodoEncabezado* nuevo = new NodoEncabezado(vuelo);
        if (!anterior) {
            nuevo->siguiente = filas;
            filas = nuevo;
        } else {
            nuevo->siguiente = actual;
            anterior->siguiente = nuevo;
        }
        return nuevo;
    }

    NodoEncabezado* obtenerColumna(string ciudad) {
        NodoEncabezado* actual = columnas;
        NodoEncabezado* anterior = nullptr;

        while (actual) {
            if (actual->id == ciudad) return actual;
            if (actual->id > ciudad) break;
            anterior = actual;
            actual = actual->siguiente;
        }

        //Insertar nueva city
        NodoEncabezado* nuevo = new NodoEncabezado(ciudad);
        if (!anterior) {
            nuevo->siguiente = columnas;
            columnas = nuevo;
        } else {
            nuevo->siguiente = actual;
            anterior->siguiente = nuevo;
        }
        return nuevo;
    }

    //eliminar un nodo específico sabiendo sus coordenadas
    void eliminarNodo(NodoMatriz* nodo) {
        //Desvincular de la FILA (Vuelo)
        if (nodo->izquierda) nodo->izquierda->derecha = nodo->derecha;

        if (nodo->derecha) nodo->derecha->izquierda = nodo->izquierda;

        //Desvincular de la COLUMNA (Ciudad)
        if (nodo->arriba) nodo->arriba->abajo = nodo->abajo;
        if (nodo->abajo) nodo->abajo->arriba = nodo->arriba;
    }

public:
    MatrizDispersa() {
        filas = nullptr;
        columnas = nullptr;
    }

    //insertar
    void insertar(string pilotoId, string ciudad, string vuelo) {

        NodoEncabezado* fila = obtenerFila(vuelo);       //Buscamos/Creamos el Vuelo
        NodoEncabezado* columna = obtenerColumna(ciudad); //Buscamos/Creamos la Ciudad

        NodoMatriz* nuevo = new NodoMatriz(pilotoId, ciudad, vuelo);

        //FILA
        if (!fila->acceso) {
            fila->acceso = nuevo;
        } else {
            NodoMatriz* actual = fila->acceso;
            NodoMatriz* previo = nullptr;

            //insertar ordenado por columna (ciudad) o al final
            while (actual && actual->ciudad < ciudad) {
                previo = actual;
                actual = actual->derecha;
            }

            if (!previo) { //Insertar al inicio
                nuevo->derecha = fila->acceso;
                fila->acceso->izquierda = nuevo;
                fila->acceso = nuevo;
            } else { //Insertar en medio o final
                previo->derecha = nuevo;
                nuevo->izquierda = previo;
                if (actual) {
                    nuevo->derecha = actual;
                    actual->izquierda = nuevo;
                }
            }
        }

        //COLUMNA
        if (!columna->acceso) {
            columna->acceso = nuevo;
        } else {
            NodoMatriz* actual = columna->acceso;
            NodoMatriz* previo = nullptr;

            //Insertar ordenado por fila (vuelo)
            while (actual && actual->vuelo < vuelo) {
                previo = actual;
                actual = actual->abajo;
            }

            if (!previo) { //Insertar al inicio
                nuevo->abajo = columna->acceso;
                columna->acceso->arriba = nuevo;
                columna->acceso = nuevo;
            } else { //Insertar en medio o final
                previo->abajo = nuevo;
                nuevo->arriba = previo;
                if (actual) {
                    nuevo->abajo = actual;
                    actual->arriba = nuevo;
                }
            }
        }
    }

    //ELIMINAR PILOTO
    //quitar su información de la matriz
    void eliminarPiloto(string pilotoId) {
        bool eliminado = false;

        //Recorremos las filas (Vuelos)
        NodoEncabezado* filaActual = filas;

        while (filaActual) {
            NodoMatriz* actual = filaActual->acceso;

            while (actual) {
                if (actual->pilotoId == pilotoId) {
                    NodoMatriz* aBorrar = actual;
                    actual = actual->derecha; //Avanzamos antes de perder la referencia

                    //Desvincular de la FILA (Izquierda/Derecha)
                    if (aBorrar->izquierda) {
                        aBorrar->izquierda->derecha = aBorrar->derecha;
                    } else {
                        //Es el primero de la fila
                        filaActual->acceso = aBorrar->derecha;
                    }
                    if (aBorrar->derecha) {
                        aBorrar->derecha->izquierda = aBorrar->izquierda;
                    }

                    //Desvincular de la COLUMNA (Arriba/Abajo)
                    //Necesitamos encontrar el nodo "arriba" real o el encabezado
                    if (aBorrar->arriba) {
                        aBorrar->arriba->abajo = aBorrar->abajo;
                    } else {
                        //Es el primero de la columna, buscamos el encabezado columna
                        NodoEncabezado* colEnc = columnas;
                        while(colEnc && colEnc->id != aBorrar->ciudad) colEnc = colEnc->siguiente;
                        if(colEnc) colEnc->acceso = aBorrar->abajo;
                    }
                    if (aBorrar->abajo) {
                        aBorrar->abajo->arriba = aBorrar->arriba;
                    }

                    delete aBorrar;
                    eliminado = true;
                } else {
                    actual = actual->derecha;
                }
            }
            filaActual = filaActual->siguiente;
        }

        if (eliminado) {
            cout << "Piloto " << pilotoId << " eliminado de la matriz dispersa." << endl;
            limpiarEncabezadosVacios();
        } else {
            cout << "El piloto no tenia asignaciones en la matriz." << endl;
        }
    }

    //Limpia filas o columnas que se quedaron sin nodos tras una eliminación
    void limpiarEncabezadosVacios() {
        //Limpiar Filas (Vuelos) vacíos
        NodoEncabezado* fila = filas;
        NodoEncabezado* antFila = nullptr;
        while (fila) {
            if (!fila->acceso) {
                NodoEncabezado* temp = fila;
                if (!antFila) filas = fila->siguiente;
                else antFila->siguiente = fila->siguiente;
                fila = fila->siguiente;
                delete temp;
            } else {
                antFila = fila;
                fila = fila->siguiente;
            }
        }

        //Limpiar columnas vacías
        NodoEncabezado* col = columnas;
        NodoEncabezado* antCol = nullptr;
        while (col) {
            if (!col->acceso) {
                NodoEncabezado* temp = col;
                if (!antCol) columnas = col->siguiente;
                else antCol->siguiente = col->siguiente;
                col = col->siguiente;
                delete temp;
            } else {
                antCol = col;
                col = col->siguiente;
            }
        }
    }

    //REPORTE GRAPHVIZ
    void generarReporte(string nombreArchivo) {
        ofstream archivo(nombreArchivo + ".dot");

        archivo << "digraph MatrizDispersa {\n";
        archivo << "node [shape=box, style=filled, fillcolor=white];\n"; // Cajas blancas como imagen 7
        archivo << "graph [ranksep=0.5, nodesep=0.5];\n"; // Separación equilibrada
        archivo << "labelloc=\"t\";\n";
        archivo << "label=\"Matriz Dispersa: Piloto - Ciudad - Vuelo\";\n";
        archivo << "root [label=\"Vuelo/Ciudad destino\", group=\"0\"];\n";

        //Encabezados de Columna
        NodoEncabezado* col = columnas;
        while (col) {
            archivo << "C_" << col->id << " [label=\"Ciudad: " << col->id << "\", group=\"" << col->id << "\"];\n";
            col = col->siguiente;
        }

        //Encabezados de fila y nodos internos
        NodoEncabezado* fila = filas;
        while (fila) {
            archivo << "F_" << fila->id << " [label=\"Vuelo: " << fila->id << "\", group=\"0\"];\n";

            //Nodos de la fila
            NodoMatriz* actual = fila->acceso;
            while (actual) {
                string idNodo = "N_" + actual->vuelo + "_" + actual->ciudad;
                archivo << idNodo << " [label=\"Piloto: " << actual->pilotoId << "\", group=\"" << actual->ciudad << "\"];\n";
                actual = actual->derecha;
            }
            fila = fila->siguiente;
        }

        //alineamos matriz
        archivo << "{ rank=same; root; ";
        col = columnas;
        while (col) {
            archivo << "C_" << col->id << "; ";
            col = col->siguiente;
        }
        archivo << "}\n";

        //alinear cada Vuelo con sus nodos internos, filas siguientes
        fila = filas;
        while (fila) {
            archivo << "{ rank=same; F_" << fila->id << "; ";
            NodoMatriz* actual = fila->acceso;
            while (actual) {
                archivo << "N_" << actual->vuelo << "_" << actual->ciudad << "; ";
                actual = actual->derecha;
            }
            archivo << "}\n";
            fila = fila->siguiente;
        }

        //aristas

        //raiz
        if (columnas) archivo << "root -> C_" << columnas->id << ";\n";
        if (filas) archivo << "root -> F_" << filas->id << ";\n";

        //Conexiones entre Ciudades
        col = columnas;
        while (col && col->siguiente) {
            archivo << "C_" << col->id << " -> C_" << col->siguiente->id << " [dir=both];\n";
            col = col->siguiente;
        }

        //Conexiones entre Vuelos
        fila = filas;
        while (fila && fila->siguiente) {
            archivo << "F_" << fila->id << " -> F_" << fila->siguiente->id << " [dir=both];\n";
            fila = fila->siguiente;
        }

        //conexiones internas
        //punteros verticales
        col = columnas;
        while(col) {
            if (col->acceso) {
                //Primer nodo de la columna
                archivo << "C_" << col->id << " -> N_" << col->acceso->vuelo << "_" << col->acceso->ciudad << " [dir=both];\n";

                //Nodo -> Nodo abajo
                NodoMatriz* actual = col->acceso;
                while (actual->abajo) {
                    archivo << "N_" << actual->vuelo << "_" << actual->ciudad << " -> "
                            << "N_" << actual->abajo->vuelo << "_" << actual->abajo->ciudad << " [dir=both];\n";
                    actual = actual->abajo;
                }
            }
            col = col->siguiente;
        }

        //Punteros Horizontales, hacia la derecha
        fila = filas;
        while (fila) {
            if (fila->acceso) {
                //Primer nodo de la fila
                archivo << "F_" << fila->id << " -> N_" << fila->acceso->vuelo << "_" << fila->acceso->ciudad << " [dir=both, constraint=false];\n";

                //Nodo -> Nodo Derecha
                NodoMatriz* actual = fila->acceso;
                while (actual->derecha) {
                    archivo << "N_" << actual->vuelo << "_" << actual->ciudad << " -> "
                            << "N_" << actual->derecha->vuelo << "_" << actual->derecha->ciudad << " [dir=both, constraint=false];\n";
                    actual = actual->derecha;
                }
            }
            fila = fila->siguiente;
        }

        archivo << "}\n";
        archivo.close();

        cout << "Reporte de Matriz Dispersa generado exitosamente: " << nombreArchivo << ".dot" << endl;
        string comando = "dot -Tpng " + nombreArchivo + ".dot -o " + nombreArchivo + ".png";
        system(comando.c_str());
        system("start matriz_dispersa.png");
    }
};

#endif