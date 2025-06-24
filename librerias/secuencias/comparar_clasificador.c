#include "secuencias.h"

int compararClasificador(const char* cadClas1, const char* cadClas2)
{
    char clasificadores[3][15] = {{"Items\0"}, {"Capitulos\0"}, {"Nivel general\0"}};

    int posCadClas1 = buscarMatriz(clasificadores, cadClas1, 3);
    int posCadClas2 = buscarMatriz(clasificadores, cadClas2, 3);

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

int buscarMatriz (const char matriz[][15], const char *cadBuscar, int ce)
{
    int pos = -1;
    for (int i = 0; i < ce; i++)
    {
        if(comparar(cadBuscar, matriz[i]) == 0)
        {
            pos = i;
        }
    }

    return pos;
}

