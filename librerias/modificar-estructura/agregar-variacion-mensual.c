#include "modificar-estructura.h"

#include "math.h"

void agregarVarMensual(Indice indices[], int ce)
{
	// Tener en cuenta que esto se aplica al caso en el que el período de Nivel general de repetición es de 4 items.
    float mesAnterior,mesActual;

    indices[0].varMensual = 0;
    for(int i = 1; i < ce; i++)
    {

// seria mejor que al hacer la struct en este campo se lo inicializara en 0
        mesAnterior = indices[i-1].indice;
        mesActual = indices[i].indice;
        indices[i].varMensual = redondear2decimales(((mesActual / mesAnterior - 1) * 100)* 100 / 100);//redondeo a 2 decimales
    }
}

float redondear2decimales(float valor)
{
    return roundf(valor * 100.0f) / 100.0f;
}
