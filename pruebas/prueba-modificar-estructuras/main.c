#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../librerias/modificar-estructura/modificar-estructura.h"

typedef struct
{
    char entrada[20];
    char esperado[20];
} CasoPrueba;

void pruebaAgregarApertura();

int main()
{
    system("chcp 65001");


    pruebaAgregarApertura();

    return 0;
}

void pruebaAgregarApertura()
{
    CasoPrueba casos[] =
    {
        {"Nivel general", "Nivel general"},
        {"Materiales", "Capitulos"},
        {"Mano de obra", "Capitulos"},
        {"Gastos generales", "Capitulos"},
    };

    Indice indices[4];

    for(int i = 0; i < 4; i++)
    {
        strcpy(indices[i].clasificador, casos[i].entrada);
    }

    agregarClasificador(indices, 4);

    char salida[100];
    int total = sizeof(casos) / sizeof(casos[0]);
    int errores = 0;

    printf("\nEjecutando pruebas para agregarClasificador...\n");


    for (int i = 0; i < total; i++)
    {
        puts(indices[i].clasificador);
        strcpy(salida, indices[i].clasificador);
        if (strcmp(salida, casos[i].esperado) != 0)
        {
            printf("prueba %d fallo: entrada='%s' --> salida='%s' (esperado='%s')\n",
                   i + 1, casos[i].entrada, salida, casos[i].esperado);
            errores++;
        }
        else
        {
            printf("prueba %d paso: %s --> %s\n", i + 1, casos[i].entrada, salida);
        }
    }

    printf("\nResumen: %d pasaron, %d fallaron.\n", total - errores, errores);
    assert(errores == 0 && "Al menos un prueba fallo en agregarClasificador.");
}
