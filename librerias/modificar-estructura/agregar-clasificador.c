#include "modificar-estructura.h"

void agregarClasificador(Indice *indice)
{
    char text[]="Nivel general";
    char text2[]="Capitulos";

    if(comparar(indice->nivelGeneralAperturas, text) == 0)
    {
        copiar(indice->clasificador, text);
    }
    else
    {
        copiar(indice->clasificador, text2);
    }
}
