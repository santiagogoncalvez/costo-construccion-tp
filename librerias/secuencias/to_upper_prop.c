#include "secuencias.h"

char toUpperProp(char c)
{
    if(c>='a' && c<='z')
    {
        c-=32;
        return c;
    }
    return c;
}
