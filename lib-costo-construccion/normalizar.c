#include "costo-construccion.h"

char* normalizar(char* cadorigen)
{
    char*inicio=cadorigen;
    *cadorigen=toupper(*cadorigen);
    cadorigen++;
    while(*cadorigen!='\0')
    {
        if('_'==*cadorigen)
        {
            *cadorigen=' ';
        }
        else
        {
            *cadorigen=tolower(*cadorigen);
        }
        cadorigen++;
    }

    return inicio ;
}
