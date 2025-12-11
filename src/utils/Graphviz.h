#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H

#include <string>
#include <cstdlib>
using namespace std;

void generarImagen(string dot, string png) {
    string comando = "dot -Tpng " + dot + " -o " + png;
    system(comando.c_str());

    // Abrir la imagen automaticamente
    system(png.c_str());
}

#endif
