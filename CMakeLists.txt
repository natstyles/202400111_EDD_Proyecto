cmake_minimum_required(VERSION 4.0)
project(202400111_EDD_Proyecto)

set(CMAKE_CXX_STANDARD 20)

add_executable(202400111_EDD_Proyecto src/main.cpp
        src/estructuras/NodoDoble.h
        src/modelos/Avion.h
        src/modelos/Pasajero.h
        src/estructuras/NodoSimple.h
        src/estructuras/ColaPasajeros.h
        src/estructuras/PilaEquipaje.h
        src/estructuras/ListaCircularAviones.h
        src/estructuras/ListaDoblePasajeros.h
        src/cargadores/CargadorAviones.h
        src/cargadores/CargadorPasajeros.h
        src/cargadores/CargadorCambios.h
        src/utils/Utilidades.h
        src/utils/Graphviz.h
        src/modelos/Equipaje.h
        src/estructuras_no_lineales/ArbolBAviones.h
        src/modelos/Piloto.h
        src/estructuras_no_lineales/NodoArbolPiloto.h
        src/estructuras_no_lineales/ArbolPilotos.h
        src/cargadores/CargadorPilotos.h
        src/estructuras_no_lineales/TablaHashPilotos.h
        src/estructuras_no_lineales/ListaSimplePilotos.h
        src/estructuras_no_lineales/NodoRuta.h
        src/estructuras_no_lineales/NodoCiudad.h
        src/estructuras_no_lineales/GrafoRutas.h
        src/cargadores/CargadorRutas.h)
