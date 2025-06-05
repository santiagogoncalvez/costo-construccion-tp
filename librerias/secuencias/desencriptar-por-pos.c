#include <stdbool.h>
#include <locale.h>

#include "secuencias.h"

void desencriptarPorPos(char* cadoriginal)
{
    char* cadcopia=cadoriginal;
    while(*cadcopia!='\0')
    {
        if(espalabra(*cadcopia))
        {
            *cadcopia=abcdario(*cadcopia,(cadcopia-cadoriginal));
        }
        cadcopia++;
    }
}

bool espalabra(char cadcopia)
{
    return (cadcopia>='a' && cadcopia<='z') || (cadcopia>='A' && cadcopia<='Z');
}

char abcdario(char cad,int pos)
{
    char abc[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\0'};
    int num=0;

    while(tolower(cad)!=abc[num])
    {
        num++;
    }
    if(pos%2==0)
    {
        for(int i=0; i<4; i++)
        {
            num++;
            if(abc[num]=='\0')
            {
                num=0;
            }

        }
    }
    else
    {
        for(int i=0; i<2; i++)
        {
            num++;
            if(abc[num]=='\0')
            {
                num=0;
            }

        }
    }

    if(islower(cad))
    {
        return abc[num];

    }
    else
    {
        return toupper(abc[num]);
    }

}
