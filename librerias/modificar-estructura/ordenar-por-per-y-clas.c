#include "modificar-estructura.h"
#include "../TDA-fecha/fecha.h"

void ordenarPorPerYClas(Indice indices[], int ce)
{
    Indice *desordenado;
    Indice aux;
    Indice *pI;
    Indice *limite = indices + ce - 1;
    tFecha fecha1, fecha2;

    do
    {
        desordenado = NULL;
        for(pI = indices; pI < limite; pI++)
        {
            fechaSetDesdeString(&fecha1, pI->periodo);
            fechaSetDesdeString(&fecha2, (pI + 1)->periodo);

            int cmpClas = compararClasificador(pI->clasificador, (pI + 1)->clasificador);
            int cmpFecha = fechaComparar(&fecha1, &fecha2);

            // Clasificador es más importante (primero)
            if (cmpClas < 0 || (cmpClas == 0 && cmpFecha > 0))
            {
                aux = *pI;
                *pI = *(pI + 1);
                *(pI + 1) = aux;
                desordenado = pI;
            }
        }

        limite = desordenado;
    }
    while (desordenado);
}
