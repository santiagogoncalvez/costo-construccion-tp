#include "secuencias.h"

void copiar(char* cadDestinio,char* cadOrigen)
{
    while(*cadOrigen!='\0')
    {
        *cadDestinio=*cadOrigen;
        cadOrigen++;
        cadDestinio++;
    }
    *cadDestinio='\0';
}
