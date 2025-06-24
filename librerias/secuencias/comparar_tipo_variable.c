#include "secuencias.h"

int compararTipoVariable(const char* cadClas1, const char* cadClas2)
{
    char tiposVariables[3][15] = {{"var_interanual\0"}, {"var_mensual\0"}, {"indice_icc\0"}};

    int posCadClas1 = buscarMatriz(tiposVariables, cadClas1, 3);
    int posCadClas2 = buscarMatriz(tiposVariables, cadClas2, 3);

    if(posCadClas1 < posCadClas2)
    {
        return -1;
    }

    if(posCadClas1 > posCadClas2)
    {
        return 1;
    }

    return 0;
}

