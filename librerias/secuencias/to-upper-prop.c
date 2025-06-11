#include "secuencias.h"

char toUpperProp(char c)
{
    char mayusculas[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','\0'};
    char minusculas[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\0'};
    int i=0;
    while(minusculas[i]!='\0' && minusculas[i]!=c)
    {
        i++;
    }
    if(minusculas[i]==c)
    {
        return mayusculas[i];
    }
    if(c=='ñ')
    {
        return 'Ñ';
    }
    if(minusculas[i]=='\0')
    {
        return c;
    }

    return c;
}
