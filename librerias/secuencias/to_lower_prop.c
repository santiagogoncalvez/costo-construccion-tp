#include "secuencias.h"

char toLowerProp(char c)//mayuscula en minuscula
{
    if(c>='A' && c<='Z')
    {
         c+=32;
         return c;
    }
    return c;
}
