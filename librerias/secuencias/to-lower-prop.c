#include "secuencias.h"

char toLowerProp(char c)//mayuscula en minuscula
{
    char mayusculas[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','\0'};
    char minusculas[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\0'};
    int i=0;
    while(mayusculas[i]!='\0' && mayusculas[i]!=c)
    {
        i++;
    }
    if(mayusculas[i]==c)
    {
        return minusculas[i];
    }
    if(c=='Ñ')
    {
        return 'ñ';
    }
    if(mayusculas[i]=='\0')
    {
        return c;
    }

    return c;
}
