#include "secuencias.h"

void sacarAntYNormalizar(char *cad)
{
    char *iCad = cad;
    int encontrado = 0, lugaresAntesGuion = 0;
    while(*iCad != '\0' && !encontrado)
    {
        if(*iCad == '_') {
            encontrado = 1;
        }
        lugaresAntesGuion++;
        iCad++;
    }

    while(*iCad != '\0')
    {
        *(iCad - lugaresAntesGuion) = *iCad;
        iCad++;
    }

    *(iCad - lugaresAntesGuion) = '\0';

    normalizar(cad);
}
