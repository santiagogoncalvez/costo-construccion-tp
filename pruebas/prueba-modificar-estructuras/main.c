#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../librerias/modificar-estructura/modificar-estructura.h"
#include "../../librerias/TDA-fecha/fecha.h"

typedef struct
{
    char entrada[20];
    char esperado[20];
} CasoPrueba;

typedef struct
{
    char periodo[11];
    char clasificador[20];
} CasoIndice;


void pruebaAgregarClasificador();
void pruebaAgregarClasificadorItems();
bool verificarOrden(const Indice datos[], int ce);
bool verificarOrden(const Indice datos[], int ce);
void pruebaOrdenarPorPerYClas();


int main()
{
    system("chcp 65001");


    pruebaAgregarClasificador();
    pruebaAgregarClasificadorItems();
    pruebaOrdenarPorPerYClas();


    return 0;
}

void pruebaAgregarClasificador()
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

void pruebaAgregarClasificadorItems()
{
    CasoPrueba casos[] =
    {
        {"", "Items"},
        {"", "Items"},
        {"", "Items"},
        {"", "Items"},
    };

    Indice indices[4];

    for(int i = 0; i < 4; i++)
    {
        strcpy(indices[i].clasificador, casos[i].entrada);
    }

    agregarClasificadorItems(indices, 4);

    char salida[100];
    int total = sizeof(casos) / sizeof(casos[0]);
    int errores = 0;

    printf("\nEjecutando pruebas para agregarClasificadorItems...\n");


    for (int i = 0; i < total; i++)
    {
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
    assert(errores == 0 && "Al menos un prueba fallo en agregarClasificadorItems.");
}

void probarFecha()
{
    tFecha fecha1, fecha2;

    fechaSetDesdeString(&fecha1, "2022-08-01");
    fechaSetDesdeString(&fecha2, "2020-08-01");

    fechaMostrar(&fecha1);
    fechaMostrar(&fecha2);

    printf("\nComparacion: %d", fechaComparar(&fecha1, &fecha2));
}

bool verificarOrden(const Indice datos[], int ce)
{
    printf("\nVerificando orden...");

    tFecha f1, f2;

    for (int i = 0; i < ce - 1; i++)
    {
        int cmpClas = compararClasificador(datos[i].clasificador, datos[i + 1].clasificador);

        // Clasificador desordenado
        if (cmpClas < 0)
            return false;

        if (cmpClas == 0)
        {
            fechaSetDesdeString(&f1, datos[i].periodo);
            fechaSetDesdeString(&f2, datos[i + 1].periodo);
            int cmpFecha = fechaComparar(&f1, &f2);

            // Mismo clasificador, pero fechas desordenadas
            if (cmpFecha > 0)
                return false;
        }
    }

    return true;
}

void pruebaOrdenarPorPerYClas()
{
    printf("\nEjecutando pruebas para ordenarPorPerYClas...");

    CasoIndice casos[] =
    {
        {"2023-04-11", "Items"},
        {"2025-10-06", "Capitulos"},
        {"2022-12-21", "Nivel general"},
        {"2020-07-01", "Capitulos"},
        {"2023-04-10", "Items"}
    };

    int total = sizeof(casos) / sizeof(casos[0]);
    Indice indices[total];

    for(int i = 0; i < total; i++)
    {
        strcpy(indices[i].periodo, casos[i].periodo);
        strcpy(indices[i].clasificador, casos[i].clasificador);
    }

    printf("\nAntes de orden\n");
    for(int i = 0; i < total; i++)
    {
        printf("%-20s%-20s\n", indices[i].periodo, indices[i].clasificador);
    }

    ordenarPorPerYClas(indices, total);

    printf("\nDespues de orden\n");
    for(int i = 0; i < total; i++)
    {
        printf("%-20s%-20s\n", indices[i].periodo, indices[i].clasificador);
    }

    if (verificarOrden(indices, total))
    {
        printf("\nOrden correcto\n");
    }
    else
    {
        printf("\nOrden incorrecto\n");
    }
}
