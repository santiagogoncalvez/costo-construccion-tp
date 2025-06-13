#include "secuencias.h"

bool comparar(const char* cad1, const char* cad2)
{
    const char*i=cad1;
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
