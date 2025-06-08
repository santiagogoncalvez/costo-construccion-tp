#include "secuencias.h"

void generarClasificador(char *clasificador)
{
    const char *texto="Items";
    char *camp_clasif;

    camp_clasif =clasificador;

    while (*texto != '\0')
        {
            *camp_clasif = *texto;
            camp_clasif++;
            texto++;
        }
        *camp_clasif = '\0';

}
