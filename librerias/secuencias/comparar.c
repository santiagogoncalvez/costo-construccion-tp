#include "secuencias.h"

int comparar(const char* cad1, const char* cad2)
{
    while (*cad1 && *cad2 && *cad1 == *cad2)
    {
        cad1++;
        cad2++;
    }

    return (unsigned char)*cad1 - (unsigned char)*cad2;
}
