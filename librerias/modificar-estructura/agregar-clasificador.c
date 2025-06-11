#include "modificar-estructura.h"

void agregarClasificador(Indice indices[], int ce)
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
