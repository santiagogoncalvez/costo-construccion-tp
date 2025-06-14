#include "modificar-estructura.h"

#include <math.h>
void calcularVarMensual(Indice indices[], int ce)
{
    float mesAnterior,mesActual;

    for(int i=0;i <ce-17;i++)
    {
        indices[i].variacion_mensual=0; // seria mejor que al hacer la struct en este campo se lo inicializara en 0
        mesAnterior=indices[i].indice;
        mesActual=(indices[i+17].indice);
        indices[i+17].variacion_mensual=round(((mesActual / mesAnterior - 1) * 100)* 100) / 100;//redondeo a 2 decimales

    }
}
