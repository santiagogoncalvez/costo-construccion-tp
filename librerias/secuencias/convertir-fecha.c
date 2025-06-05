#include "secuencias.h"

void convertirFecha(char *cadOrigen)
{
    char *pCadOrigen = cadOrigen;
    char cadDestino[11];
    char *pCadDestino = cadDestino;

    // La funcion esta recorriendo de vuelta desde el ultimo elemento el string cada vez. Cuando podria guardar el puntero al elemento siguiente a la ultima barra '/' en cada vez que se recorre o llega a ese punto.
    int cantBarras = 0, cantDig =  0;
    for(int i = 3; i > 1; i--)
    {
        while(*pCadOrigen && cantBarras <  i - 1)
        {
            if(*pCadOrigen == '/')
            {
                cantBarras++;
            }
            pCadOrigen++;
        }

        while(*pCadOrigen && *pCadOrigen != '/')
        {
            *pCadDestino = *pCadOrigen;
            pCadOrigen++;
            pCadDestino++;
            cantDig++;
        }


        if(i == 2)
        {
            if(cantDig == 1)
            {
                *pCadDestino = *(pCadDestino - 1);
                *(pCadDestino - 1) = '0';
                pCadDestino++;
            }
        }
        *pCadDestino = '/';
        pCadDestino++;

        pCadOrigen = cadOrigen;
        cantBarras = 0;
        cantDig = 0;
    }

    while(*pCadOrigen && *pCadOrigen != '/')
    {
        *pCadDestino = *pCadOrigen;
        pCadOrigen++;
        pCadDestino++;
        cantDig++;
    }

    if(cantDig == 1)
    {
        *pCadDestino = *(pCadDestino - 1);
        *(pCadDestino - 1) = '0';
        pCadDestino++;
    }

    *pCadDestino = '\0';


// Reemplazar '/' por '-'
    pCadDestino = cadDestino;
    while(*pCadDestino)
    {
        if(*pCadDestino == '/')
        {
            *pCadDestino = '-';
        }
        pCadDestino++;
    };

// Reemplazar la nueva cadena en la cadena origianl
    pCadOrigen = cadOrigen;
    pCadDestino = cadDestino;
    while(*pCadDestino)
    {
        *pCadOrigen = *pCadDestino;
        pCadOrigen++;
        pCadDestino++;
    }
}
