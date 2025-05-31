#include "secuencias.h"

void convertirComa(char *cad)
{
    int convertido=0;
    char *iCad = cad;
    while(*iCad != '\0' && !convertido)
    {
        if(*iCad==',')
        {
            convertido = 1;
            *iCad='.';

        }
        iCad++;
    }
}