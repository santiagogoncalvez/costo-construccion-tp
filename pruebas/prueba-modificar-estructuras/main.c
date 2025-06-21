#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../librerias/modificar-estructura/modificar-estructura.h"
#include "../../librerias/TDA-fecha/fecha.h"

#include <math.h>

#define EPSILON 0.3f

typedef struct
{
    char periodo[11];
    char nivelGeneralAperturas[50];
    char indice[20];
    char variacionMensual[10];
} CasoVarMensual;

void pruebaAgregarClasificador();
void pruebaAgregarClasificadorItems();
bool verificarOrden(const Indice datos[], int ce);
bool verificarOrden(const Indice datos[], int ce);
void pruebaOrdenarPorPerYClas();
void pruebaVariacionMensual();
void pruebaCalcIndVarInteranual();
void pruebaAgregarVarMensual();

int main()
{
    system("chcp 65001");


    /*
    pruebaAgregarClasificador();
    pruebaAgregarClasificadorItems();
    pruebaVariacionMensual();
    probarFechaSumarMeses();
    probarFechaRestarMeses();
    pruebaIndPorInteranual();
    pruebaCalcIndVarInteranual();
    pruebaAgregarVarMensual();
    */

    pruebaOrdenarPorPerYClas();


    return 0;
}

void pruebaAgregarClasificador()
{
    Indice indices[] =
    {
        {{11, 4, 2023}, "", 0.0, "Nivel general", 0.0, 0.0},
        {{6, 10, 2025}, "", 0.0, "Materiales", 0.0, 0.0},
        {{21, 12, 2022}, "", 0.0, "Mano de obra", 0.0, 0.0},
        {{1, 7, 2020}, "", 0.0, "Gastos generales", 0.0, 0.0},
    };

    Indice esperados[] =
    {
        {{11, 4, 2023}, "", 0.0, "Nivel general", 0.0, 0.0},
        {{6, 10, 2025}, "", 0.0, "Capitulos", 0.0, 0.0},
        {{21, 12, 2022}, "", 0.0, "Capitulos", 0.0, 0.0},
        {{1, 7, 2020}, "", 0.0, "Capitulos", 0.0, 0.0},
    };

    int total = sizeof(indices) / sizeof(indices[0]);

    Indice* p;
    Indice* fin = indices + total;

    for (p = indices; p < fin; p++)
    {
       agregarClasificador(p);
    }

    int errores = 0;

    printf("\nEjecutando pruebas para agregarClasificador...\n");


    for (int i = 0; i < total; i++)
    {
        if (strcmp(indices[i].clasificador, esperados[i].clasificador) != 0)
        {
            printf("prueba %d fallo: entrada='%s' --> salida='%s' (esperado='%s')\n",
                   i + 1, "", indices[i].clasificador, esperados[i].clasificador);
            errores++;
        }
        else
        {
            printf("prueba %d paso: %s --> %s\n", i + 1, "", esperados[i].clasificador);
        }
    }

    printf("\nResumen: %d pasaron, %d fallaron.\n", total - errores, errores);
    assert(errores == 0 && "Al menos un prueba fallo en agregarClasificador.");
}

void pruebaAgregarClasificadorItems()
{
    Indice indices[] =
    {
        {{11, 4, 2023}, "", 0.0, "", 0.0, 0.0},
        {{6, 10, 2025}, "", 0.0, "", 0.0, 0.0},
        {{21, 12, 2022}, "", 0.0, "", 0.0, 0.0},
        {{1, 7, 2020}, "", 0.0, "", 0.0, 0.0},
        {{10, 4, 2023}, "", 0.0, "", 0.0, 0.0}
    };

    int total = sizeof(indices) / sizeof(indices[0]);

    Indice* p;
    Indice* fin = indices + total;

    for (p = indices; p < fin; p++)
    {
       agregarClasificadorItem(p);
    }

    int errores = 0;

    printf("\nEjecutando pruebas para agregarClasificadorItems...\n");
    for (int i = 0; i < total; i++)
    {
        if (strcmp(indices[i].clasificador, "Items") != 0)
        {
            printf("prueba %d fallo: entrada='%s' --> salida='%s' (esperado='%s')\n",
                   i + 1, "", indices[i].clasificador, "Items");
            errores++;
        }
        else
        {
            printf("prueba %d paso: %s --> %s\n", i + 1, "", indices[i].clasificador);
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

void probarFechaSumarMeses(void)
{
    printf("\n\nSumar meses\n");

    tFecha fechasPrueba[] =
    {
        {31, 1, 2023},   // Enero 31 â†’ ver quÃ© pasa en febrero
        {28, 2, 2023},   // Febrero no bisiesto
        {28, 2, 2024},   // Febrero bisiesto
        {30, 11, 2022},  // Noviembre â†’ suma 3 meses
        {15, 6, 2021}    // Junio â†’ resta meses
    };
    int cantidades[] = {1, 1, 1, 3, 7};

    int n = sizeof(fechasPrueba) / sizeof(fechasPrueba[0]);

    for (int i = 0; i < n; i++)
    {
        tFecha nueva = fechaSumarMeses(&fechasPrueba[i], cantidades[i]);
        printf("Original: %02d/%02d/%04d + %d meses â†’ Resultado: %02d/%02d/%04d\n",
               fechasPrueba[i].d, fechasPrueba[i].m, fechasPrueba[i].a,
               cantidades[i],
               nueva.d, nueva.m, nueva.a);
    }
}

void probarFechaRestarMeses(void)
{
    printf("\n\nRestar meses\n");
    tFecha fechasPrueba[] =
    {
        {31, 1, 2023},   // Enero 31 â†’ ver quÃ© pasa en febrero
        {28, 2, 2023},   // Febrero no bisiesto
        {28, 2, 2024},   // Febrero bisiesto
        {30, 11, 2022},  // Noviembre â†’ suma 3 meses
        {15, 6, 2021}    // Junio â†’ resta meses
    };
    int cantidades[] = {1, 1, 1, 3, 7};

    int n = sizeof(fechasPrueba) / sizeof(fechasPrueba[0]);

    for (int i = 0; i < n; i++)
    {
        tFecha nueva = fechaRestarMeses(&fechasPrueba[i], cantidades[i]);
        printf("Original: %02d/%02d/%04d -  %d meses â†’ Resultado: %02d/%02d/%04d\n",
               fechasPrueba[i].d, fechasPrueba[i].m, fechasPrueba[i].a,
               cantidades[i],
               nueva.d, nueva.m, nueva.a);
    }
}

bool verificarOrden(const Indice datos[], int ce)
{
    printf("\nVerificando orden...");

    for (int i = 0; i < ce - 1; i++)
    {
        int cmpClas = compararClasificador(datos[i].clasificador, datos[i + 1].clasificador);

        // Clasificador desordenado
        if (cmpClas < 0)
            return false;

        if (cmpClas == 0)
        {
            int cmpFecha = fechaComparar(&datos[i].periodo, &datos[i + 1].periodo);

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

    Indice indices[] =
    {
        {{11, 4, 2023}, "", 0.0, "Items", 0.0, 0.0},
        {{6, 10, 2025}, "", 0.0, "Capitulos", 0.0, 0.0},
        {{21, 12, 2022}, "", 0.0, "Nivel general", 0.0, 0.0},
        {{1, 7, 2020}, "", 0.0, "Capitulos", 0.0, 0.0},
        {{10, 4, 2023}, "", 0.0, "Items", 0.0, 0.0}
    };

    int total = sizeof(indices) / sizeof(indices[0]);

    printf("\nAntes de orden\n");
    for(int i = 0; i < total; i++)
    {
        printf("%02d-%02d-%4d\t", indices[i].periodo.d, indices[i].periodo.m, indices[i].periodo.a);
        printf("%-20s\n",indices[i].clasificador);
    }

    //ordenarPorPerYClas(indices, total);

    printf("\nDespues de orden\n");
    for(int i = 0; i < total; i++)
    {
        printf("%02d-%02d-%4d\t", indices[i].periodo.d, indices[i].periodo.m, indices[i].periodo.a);
        printf("%-20s\n",indices[i].clasificador);
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

void doubleToStr(double val, char *str, int size)
{
    snprintf(str, size, "%.2f", val);
}

void pruebaIndPorInteranual()
{
    Indice indices[] =
    {
        {{1, 4, 2022}, "", 100.0, "Nivel general", 0.0, 0.0},  // Base
        {{1, 4, 2023}, "", 115.5, "Nivel general", 0.0, 0.0},  // +15.5%
        {{1, 4, 2022}, "", 200.0, "Items", 0.0, 0.0},          // Base
        {{1, 4, 2023}, "", 260.0, "Items", 0.0, 0.0},          // +30.0%
        {{1, 4, 2023}, "", 300.0, "Capitulos", 0.0, 0.0}       // Sin valor base â†’ no se puede calcular
    };

    Indice esperados[] =
    {
        {{1, 4, 2022}, "", 100.0, "Nivel general", 0.0, 0.0},     // Base, sin variaciÃ³n
        {{1, 4, 2023}, "", 115.5, "Nivel general", 0.0, 15.50},   // +15.5%
        {{1, 4, 2022}, "", 200.0, "Items", 0.0, 0.0},             // Base, sin variaciÃ³n
        {{1, 4, 2023}, "", 260.0, "Items", 0.0, 30.00},           // +30%
        {{1, 4, 2023}, "", 300.0, "Capitulos", 0.0, 0.0}
    };

    int total = sizeof(indices) / sizeof(indices[0]);

    Indice* p;
    Indice* fin = indices + total;

    for (p = indices; p < fin; p++)
    {
       calcVarInteranual(p, indices);
    }

    int errores = 0;

    printf("\nEjecutando pruebas para agregarClasificador...\n");


    for (int i = 0; i < total; i++)
    {
        if (indices[i].varInteranual != esperados[i].varInteranual)
        {
            printf("prueba %d fallo: entrada='%s' --> salida='%f' (esperado='%f')\n",
                   i + 1, "", indices[i].varInteranual, esperados[i].varInteranual);
            errores++;
        }
        else
        {
            printf("prueba %d paso: %s --> %f\n", i + 1, "", esperados[i].varInteranual);
        }
    }

    printf("\nResumen: %d pasaron, %d fallaron.\n", total - errores, errores);
    assert(errores == 0 && "Al menos un prueba fallo en agregarClasificador.");
}

void pruebaCalcIndVarInteranual()
{
    Indice indicesBase[] =
    {
        {{1,  1, 2022}, "Nivel general", 100.00f, "Capítulos", 0.0f, 0.0f},
        {{1,  2, 2022}, "Nivel general", 103.80f, "Capítulos", 0.0f, 0.0f},
        {{1,  3, 2022}, "Nivel general", 108.99f, "Capítulos", 0.0f, 0.0f},
        {{1,  4, 2022}, "Nivel general", 111.50f, "Capítulos", 0.0f, 0.0f},
        {{1,  5, 2022}, "Nivel general", 118.86f, "Capítulos", 0.0f, 0.0f},
        {{1,  6, 2022}, "Nivel general", 126.70f, "Capítulos", 0.0f, 0.0f},
        {{1,  7, 2022}, "Nivel general", 135.44f, "Capítulos", 0.0f, 0.0f},
        {{1,  8, 2022}, "Nivel general", 145.60f, "Capítulos", 0.0f, 0.0f},
        {{1,  9, 2022}, "Nivel general", 156.37f, "Capítulos", 0.0f, 0.0f},
        {{1, 10, 2022}, "Nivel general", 167.79f, "Capítulos", 0.0f, 0.0f},
        {{1, 11, 2022}, "Nivel general", 179.03f, "Capítulos", 0.0f, 0.0f},
        {{1, 12, 2022}, "Nivel general", 186.73f, "Capítulos", 0.0f, 0.0f},
        {{1,  1, 2023}, "Nivel general", 199.24f, "Capítulos", 0.0f, 0.0f},
        {{1,  2, 2023}, "Nivel general", 211.20f, "Capítulos", 0.0f, 0.0f},
        {{1,  3, 2023}, "Nivel general", 221.12f, "Capítulos", 0.0f, 0.0f},
        {{1,  4, 2023}, "Nivel general", 239.03f, "Capítulos", 0.0f, 0.0f},
        {{1,  5, 2023}, "Nivel general", 257.68f, "Capítulos", 0.0f, 0.0f},
        {{1,  6, 2023}, "Nivel general", 272.62f, "Capítulos", 0.0f, 0.0f},
        {{1,  7, 2023}, "Nivel general", 295.52f, "Capítulos", 0.0f, 0.0f},
        {{1,  8, 2023}, "Nivel general", 339.26f, "Capítulos", 0.0f, 0.0f},
        {{1,  9, 2023}, "Nivel general", 389.13f, "Capítulos", 0.0f, 0.0f},
        {{1, 10, 2023}, "Nivel general", 416.76f, "Capítulos", 0.0f, 0.0f},
        {{1, 11, 2023}, "Nivel general", 464.69f, "Capítulos", 0.0f, 0.0f},
        {{1, 12, 2023}, "Nivel general", 606.88f, "Capítulos", 0.0f, 0.0f}
    };

    Indice indicesEsperados[] =
    {
        // Año 2022
        {{1,  1, 2022}, "Nivel general", 100.00f, "Capítulos", 0.0f, 0.0f},
        {{1,  2, 2022}, "Nivel general", 103.80f, "Capítulos", 0.0f, 0.0f},
        {{1,  3, 2022}, "Nivel general", 108.99f, "Capítulos", 0.0f, 0.0f},
        {{1,  4, 2022}, "Nivel general", 111.50f, "Capítulos", 0.0f, 0.0f},
        {{1,  5, 2022}, "Nivel general", 118.86f, "Capítulos", 0.0f, 0.0f},
        {{1,  6, 2022}, "Nivel general", 126.70f, "Capítulos", 0.0f, 0.0f},
        {{1,  7, 2022}, "Nivel general", 135.44f, "Capítulos", 0.0f, 0.0f},
        {{1,  8, 2022}, "Nivel general", 145.60f, "Capítulos", 0.0f, 0.0f},
        {{1,  9, 2022}, "Nivel general", 156.37f, "Capítulos", 0.0f, 0.0f},
        {{1, 10, 2022}, "Nivel general", 167.79f, "Capítulos", 0.0f, 0.0f},
        {{1, 11, 2022}, "Nivel general", 179.03f, "Capítulos", 0.0f, 0.0f},
        {{1, 12, 2022}, "Nivel general", 186.73f, "Capítulos", 0.0f, 0.0f},

        // Año 2023 (con valores de variación interanual esperados)
        {{1,  1, 2023}, "Nivel general", 199.24f, "Capítulos", 0.0f, 99.4f},
        {{1,  2, 2023}, "Nivel general", 211.20f, "Capítulos", 0.0f, 103.6f},
        {{1,  3, 2023}, "Nivel general", 221.12f, "Capítulos", 0.0f, 103.1f},
        {{1,  4, 2023}, "Nivel general", 239.03f, "Capítulos", 0.0f, 114.6f},
        {{1,  5, 2023}, "Nivel general", 257.68f, "Capítulos", 0.0f, 116.9f},
        {{1,  6, 2023}, "Nivel general", 272.62f, "Capítulos", 0.0f, 115.3f},
        {{1,  7, 2023}, "Nivel general", 295.52f, "Capítulos", 0.0f, 118.3f},
        {{1,  8, 2023}, "Nivel general", 339.26f, "Capítulos", 0.0f, 133.1f},
        {{1,  9, 2023}, "Nivel general", 389.13f, "Capítulos", 0.0f, 148.8f},
        {{1, 10, 2023}, "Nivel general", 416.76f, "Capítulos", 0.0f, 148.4f},
        {{1, 11, 2023}, "Nivel general", 464.69f, "Capítulos", 0.0f, 159.6f},
        {{1, 12, 2023}, "Nivel general", 606.88f, "Capítulos", 0.0f, 225.2f}
    };

    int total = sizeof(indicesBase) / sizeof(indicesBase[0]);

    // Ejecuta la función a probar
    Indice* p;
    Indice* fin = indicesBase + total;

    for (p = indicesBase; p < fin; p++)
    {
       calcVarInteranual(p, indicesBase);
    }

    printf("\nEjecutando pruebas para pruebaCalcIndVarInteranual...\n");
    int errores = 0;

    for (int i = 0; i < total; i++)
    {
        float dif = fabs(indicesBase[i].varInteranual - indicesEsperados[i].varInteranual);
        if (dif > EPSILON)
        {
            printf("Error en indice %d (%d-%02d): esperado %.2f, obtenido %.2f\n",
                   i,
                   indicesBase[i].periodo.a, indicesBase[i].periodo.m,
                   indicesEsperados[i].varInteranual, indicesBase[i].varInteranual);
            errores++;
        }
        else
        {
            printf("Indice %d (%d-%02d) OK: %.2f\n", i, indicesBase[i].periodo.a, indicesBase[i].periodo.m, indicesBase[i].varInteranual);
        }
    }

    if (errores == 0)
    {
        printf("¡Todos los tests pasaron correctamente!\n");
    }
    else
    {
        printf("Cantidad de errores: %d\n", errores);
    }
}

void pruebaAgregarVarMensual()
{
    Indice indicesBase[] =
    {
        {{1,  1, 2022}, "Nivel general", 100.00f, "Capítulos", 0.0f, 0.0f},
        {{1,  2, 2022}, "Nivel general", 103.80f, "Capítulos", 0.0f, 0.0f},
        {{1,  3, 2022}, "Nivel general", 108.99f, "Capítulos", 0.0f, 0.0f},
        {{1,  4, 2022}, "Nivel general", 111.50f, "Capítulos", 0.0f, 0.0f},
        {{1,  5, 2022}, "Nivel general", 118.86f, "Capítulos", 0.0f, 0.0f},
        {{1,  6, 2022}, "Nivel general", 126.70f, "Capítulos", 0.0f, 0.0f},
        {{1,  7, 2022}, "Nivel general", 135.44f, "Capítulos", 0.0f, 0.0f},
        {{1,  8, 2022}, "Nivel general", 145.60f, "Capítulos", 0.0f, 0.0f},
        {{1,  9, 2022}, "Nivel general", 156.37f, "Capítulos", 0.0f, 0.0f},
        {{1, 10, 2022}, "Nivel general", 167.79f, "Capítulos", 0.0f, 0.0f},
        {{1, 11, 2022}, "Nivel general", 179.03f, "Capítulos", 0.0f, 0.0f},
        {{1, 12, 2022}, "Nivel general", 186.73f, "Capítulos", 0.0f, 0.0f},
        {{1,  1, 2023}, "Nivel general", 199.24f, "Capítulos", 0.0f, 0.0f},
        {{1,  2, 2023}, "Nivel general", 211.20f, "Capítulos", 0.0f, 0.0f},
        {{1,  3, 2023}, "Nivel general", 221.12f, "Capítulos", 0.0f, 0.0f},
        {{1,  4, 2023}, "Nivel general", 239.03f, "Capítulos", 0.0f, 0.0f},
        {{1,  5, 2023}, "Nivel general", 257.68f, "Capítulos", 0.0f, 0.0f},
        {{1,  6, 2023}, "Nivel general", 272.62f, "Capítulos", 0.0f, 0.0f},
        {{1,  7, 2023}, "Nivel general", 295.52f, "Capítulos", 0.0f, 0.0f},
        {{1,  8, 2023}, "Nivel general", 339.26f, "Capítulos", 0.0f, 0.0f},
        {{1,  9, 2023}, "Nivel general", 389.13f, "Capítulos", 0.0f, 0.0f},
        {{1, 10, 2023}, "Nivel general", 416.76f, "Capítulos", 0.0f, 0.0f},
        {{1, 11, 2023}, "Nivel general", 464.69f, "Capítulos", 0.0f, 0.0f},
        {{1, 12, 2023}, "Nivel general", 606.88f, "Capítulos", 0.0f, 0.0f}
    };

    Indice indicesEsperados[] =
    {
        {{1,  1, 2022}, "Nivel general", 100.00f, "Capítulos", 0.0f, 0.0f},
        {{1,  2, 2022}, "Nivel general", 103.80f, "Capítulos", 3.8f, 0.0f},
        {{1,  3, 2022}, "Nivel general", 108.99f, "Capítulos", 5.0f, 0.0f},
        {{1,  4, 2022}, "Nivel general", 111.50f, "Capítulos", 2.3f, 0.0f},
        {{1,  5, 2022}, "Nivel general", 118.86f, "Capítulos", 6.6f, 0.0f},
        {{1,  6, 2022}, "Nivel general", 126.70f, "Capítulos", 6.6f, 0.0f},
        {{1,  7, 2022}, "Nivel general", 135.44f, "Capítulos", 6.9f, 0.0f},
        {{1,  8, 2022}, "Nivel general", 145.60f, "Capítulos", 7.5f, 0.0f},
        {{1,  9, 2022}, "Nivel general", 156.37f, "Capítulos", 7.4f, 0.0f},
        {{1, 10, 2022}, "Nivel general", 167.79f, "Capítulos", 7.3f, 0.0f},
        {{1, 11, 2022}, "Nivel general", 179.03f, "Capítulos", 6.7f, 0.0f},
        {{1, 12, 2022}, "Nivel general", 186.73f, "Capítulos", 4.3f, 0.0f},
        {{1,  1, 2023}, "Nivel general", 199.24f, "Capítulos", 6.7f, 0.0f},
        {{1,  2, 2023}, "Nivel general", 211.20f, "Capítulos", 6.0f, 0.0f},
        {{1,  3, 2023}, "Nivel general", 221.12f, "Capítulos", 4.7f, 0.0f},
        {{1,  4, 2023}, "Nivel general", 239.03f, "Capítulos", 8.1f, 0.0f},
        {{1,  5, 2023}, "Nivel general", 257.68f, "Capítulos", 7.8f, 0.0f},
        {{1,  6, 2023}, "Nivel general", 272.62f, "Capítulos", 5.8f, 0.0f},
        {{1,  7, 2023}, "Nivel general", 295.52f, "Capítulos", 8.4f, 0.0f},
        {{1,  8, 2023}, "Nivel general", 339.26f, "Capítulos", 14.8f, 0.0f},
        {{1,  9, 2023}, "Nivel general", 389.13f, "Capítulos", 14.7f, 0.0f},
        {{1, 10, 2023}, "Nivel general", 416.76f, "Capítulos", 7.1f, 0.0f},
        {{1, 11, 2023}, "Nivel general", 464.69f, "Capítulos", 11.5f, 0.0f},
        {{1, 12, 2023}, "Nivel general", 606.88f, "Capítulos", 30.6f, 0.0f}
    };

    int total = sizeof(indicesBase) / sizeof(indicesBase[0]);

    // Llamamos a la función que llena varMensual
    Indice* p;
    Indice* fin = indicesBase + total;

    for (p = indicesBase; p < fin; p++)
    {
       calcVarMensual(p, indicesBase);
    }

    printf("\nEjecutando pruebas para pruebaAgregarVarMensual...\n");
    int errores = 0;

    for (int i = 0; i < total; i++)
    {
        float dif = fabs(indicesBase[i].varMensual - indicesEsperados[i].varMensual);
        if (dif > EPSILON)
        {
            printf("Error en indice %d (%d-%02d): esperado %.2f, obtenido %.2f\n",
                   i,
                   indicesBase[i].periodo.a, indicesBase[i].periodo.m,
                   indicesEsperados[i].varMensual, indicesBase[i].varMensual);
            errores++;
        }
        else
        {
            printf("Indice %d (%d-%02d) OK: %.2f\n", i,
                   indicesBase[i].periodo.a, indicesBase[i].periodo.m,
                   indicesBase[i].varMensual);
        }
    }

    if (errores == 0)
    {
        printf("Todos los tests para varMensual pasaron correctamente!\n");
    }
    else
    {
        printf("Cantidad de errores: %d\n", errores);
    }
}
