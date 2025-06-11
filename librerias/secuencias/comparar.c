#include "secuencias.h"

bool comparar(char* cad1,char* cad2)
{
    char*i=cad1;
    while(*i!='\0' && *cad2!='\0')
    {
        if(*i!=*cad2)
        {
            return false;
        }
        i++;
        cad2++;
    }
    return true;
}
