#include <stdbool.h>
#include <locale.h>

#include "secuencias.h"

char* encriptado(char* cadoriginal)
{
    char* cadcopia=cadoriginal;
    while(*cadcopia!='\0')
    {
        if(espalabra(*cadcopia))
        {
            *cadcopia=abcdario(*cadcopia,(cadcopia-cadoriginal)+1);
        }
        cadcopia++;
    }
    return cadoriginal;
}

bool espalabra(char cadcopia)
{
    return((cadcopia>='a' && cadcopia<='z') || (cadcopia>='A' && cadcopia<='Z')) || ('�'==cadcopia ||'�'==cadcopia);
}

char abcdario(char cad,int pos)
{
    char abc[28] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','�','o','p','q','r','s','t','u','v','w','x','y','z','\0'};
    int num=0;
    if(('�'==cad||'�'==cad))
    {

        return siesletra15(cad,pos);

    }
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
                num=0;;
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
        if(abc[num]=='�')
        {
            return '�';
        }
        return toupper(abc[num]);
    }

}

char siesletra15(char cad,int pos)
{
    if(pos%2==0)
    {
        if('�'==cad)
        {
            return 'r';
        }
        return 'R';

    }
    if('�'==cad)
    {
         return 'p';
    }
    return 'P';


}
