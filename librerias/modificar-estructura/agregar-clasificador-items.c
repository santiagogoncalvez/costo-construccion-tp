#include "modificar-estructura.h"

void agregarClasificadorItems(Indice indices[], int ce)
{
    for (int i = 0; i < ce; i++)
    {
        copiar(indices[i].clasificador, "Items");
    }
}

void agregarClasificadorItem(Indice *indice)
{
    copiar(indice->clasificador, "Items");
}
