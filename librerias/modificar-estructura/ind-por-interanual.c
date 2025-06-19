#include "modificar-estructura.h"

#include "math.h"

void calcIndVarInteranual(Indice* indices, int ce)
{
    float antIndice;
    float VInteranual;

    for(int i = 0; i < ce; i++)
    {
        if(indices[i].periodo.a > 2022)
        {
            antIndice = buscarIndAnterior(indices, &indices[i], ce);
            if(antIndice > 0.0)
            {
                VInteranual = redondear2decimales(((indices[i].indice / antIndice) - 1) * 100);
                indices[i].varInteranual = VInteranual;
            }
            else
            {
                indices[i].varInteranual = 0.0;
            }


        }
        else
        {
            indices[i].varInteranual = 0.0;
        }
    }
}

float buscarIndAnterior(Indice *indices, Indice *actIndice, int ce)
{
    int i = 0;
    Indice *pIndices = indices;
    tFecha antPeriodo = fechaRestarMeses(&actIndice->periodo, 12);

    while ((i < ce) &&
            (fechaComparar(&pIndices->periodo, &antPeriodo) != 0 ||
             !comparar(pIndices->clasificador, actIndice->clasificador)))
    {
        pIndices++;
        i++;
    }

    if (i == ce)
    {
        // No se encontró coincidencia
        return -1.0f; // o NAN, o manejarlo de otra forma según tu diseño
    }

    return pIndices->indice;
}
