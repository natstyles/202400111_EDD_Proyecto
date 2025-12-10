#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
using namespace std;

inline string limpiar(string texto) {
    while (!texto.empty() && (texto[0] == ' ' || texto[0] == '"'))
        texto.erase(0, 1);

    while (!texto.empty() &&
          (texto.back() == ' ' || texto.back() == '"' ||
           texto.back() == ',' || texto.back() == '\r'))
        texto.pop_back();

    return texto;
}

#endif
