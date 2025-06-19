#include "modificar-estructura.h"

void agregarClasificadores(Indice indices[], int ce)
{
    char text[]="Nivel general";
    char text2[]="Capitulos";

    for (int i = 0; i < ce; i++)
    {
        if(comparar(indices[i].clasificador, text))
        {
            copiar(indices[i].clasificador, text);
        }
        else
        {
            copiar(indices[i].clasificador, text2);
        }
    }
}

void agregarClasificador(Indice *indice)
{
    char text[]="Nivel general";
    char text2[]="Capitulos";

    if(comparar(indice->nivelGeneralAperturas, text))
    {
        copiar(indice->clasificador, text);
    }
    else
    {
        copiar(indice->clasificador, text2);
    }
}
