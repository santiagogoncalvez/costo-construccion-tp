#include "secuencias.h"

void normalizar(char* cad)
{
    char* iCad = cad;
    *iCad=toupper(*iCad);
    iCad++;
    while(*iCad!='\0')
    {
        if('_'==*iCad)
        {
            *iCad=' ';
        }
        else
        {
            *iCad=tolower(*iCad);
        }
        iCad++;
    }
}
