#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../librerias/estructura_indice/estructura_indice.h"
#include "../../librerias/TDA_fecha/fecha.h"
#include "../../librerias/TDA_vector/vector.h"
#include "../../librerias/secuencias/secuencias.h"

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
void ordenarIndices(Indice *indices, int ce);
void mostrarVIndices(const Indice* vector, int ce);
void pruebaCalcVariacion();

int main()
{
    system("chcp 65001");

    pruebaAgregarClasificador();
    pruebaAgregarClasificadorItems();
    pruebaOrdenarPorPerYClas();
    pruebaCalcVariacion();

    return 0;
}

void pruebaAgregarClasificador()
{
    Indice indices[] =
    {
        {{11, 4, 2023}, "Nivel general", 0.0, "Nivel general", 0.0, false, 0.0, false},
        {{6, 10, 2025}, "Vidrio", 0.0, "Materiales", 0.0, false, 0.0, false},
        {{21, 12, 2022}, "Metal", 0.0, "Mano de obra", 0.0, false, 0.0, false},
        {{1, 7, 2020}, "Carpinteria", 0.0, "Gastos generales", 0.0, false, 0.0, false},
    };
    Indice esperados[] =
    {
        {{11, 4, 2023}, "Nivel general", 0.0, "Nivel general", 0.0, false, 0.0, false},
        {{6, 10, 2025}, "Vidrio", 0.0, "Capitulos", 0.0, false, 0.0, false},
        {{21, 12, 2022}, "Metal", 0.0, "Capitulos", 0.0, false, 0.0, false},
        {{1, 7, 2020}, "Carpinteria", 0.0, "Capitulos", 0.0, false, 0.0, false},
    };

    int total = sizeof(indices) / sizeof(indices[0]);
    int errores = 0;
    int i = 1;
    Indice* p;
    Indice* fin = indices + total;
    Indice *pInd = indices;
    Indice *pEsp = esperados;

    for (p = indices; p < fin; p++)
    {
        agregarClasificador(p);
    }

    printf("\nEjecutando pruebas para agregarClasificador...\n");

    while (pInd < indices + total)
    {
        if (comparar(pInd->clasificador, pEsp->clasificador) != 0)
        {
            printf("prueba %d fallo: entrada='%s' --> salida='%s' (esperado='%s')\n",
                   i, "", pInd->clasificador, pEsp->clasificador);
            errores++;
        }
        else
        {
            printf("prueba %d paso: %s --> %s\n", i, "", pEsp->clasificador);
        }

        pInd++;
        pEsp++;
        i++;
    }

    printf("\nResumen: %d pasaron, %d fallaron.\n", total - errores, errores);
    assert(errores == 0 && "Al menos un prueba fallo en agregarClasificador.");
}

void pruebaAgregarClasificadorItems()
{
    Indice indices[] =
    {
        {{11, 4, 2023}, "", 0.0, "", 0.0, false, 0.0, false},
        {{6, 10, 2025}, "", 0.0, "", 0.0, false, 0.0, false},
        {{21, 12, 2022}, "", 0.0, "", 0.0, false, 0.0, false},
        {{1, 7, 2020}, "", 0.0, "", 0.0, false, 0.0, false},
        {{10, 4, 2023}, "", 0.0, "", 0.0, false, 0.0, false}
    };
    int total = sizeof(indices) / sizeof(indices[0]);
    int errores = 0;
    int i = 1;
    Indice* p;
    Indice* fin = indices + total;

    for (p = indices; p < fin; p++)
    {
        agregarClasificadorItem(p);
    }


    printf("\nEjecutando pruebas para agregarClasificadorItems...\n");
    p = indices;
    fin = indices + total;
    while (p < fin)
    {
        if (comparar(p->clasificador, "Items") != 0)
        {
            printf("prueba %d fallo: entrada='%s' --> salida='%s' (esperado='%s')\n",
                   i, "", p->clasificador, "Items");
            errores++;
        }
        else
        {
            printf("prueba %d paso: %s --> %s\n", i, "", p->clasificador);
        }

        p++;
        i++;
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
    int total = sizeof(fechasPrueba) / sizeof(tFecha);
    int *pCant = cantidades;
    tFecha *pFecha = fechasPrueba;
    tFecha *fin = fechasPrueba + total;

    while (pFecha < fin)
    {
        tFecha nueva = fechaSumarMeses(pFecha, *pCant);

        printf("Original: %02d/%02d/%04d + %d meses → Resultado: %02d/%02d/%04d\n",
               pFecha->d, pFecha->m, pFecha->a,
               *pCant,
               nueva.d, nueva.m, nueva.a);

        pFecha++;
        pCant++;
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
    int total = sizeof(fechasPrueba) / sizeof(fechasPrueba);
    tFecha *pFecha = fechasPrueba;
    int *pCant = cantidades;
    tFecha *fin = fechasPrueba + total;


    while (pFecha < fin)
    {
        tFecha nueva = fechaRestarMeses(pFecha, *pCant);

        printf("Original: %02d/%02d/%04d - %d meses → Resultado: %02d/%02d/%04d\n",
               pFecha->d, pFecha->m, pFecha->a,
               *pCant,
               nueva.d, nueva.m, nueva.a);

        pFecha++;
        pCant++;
    }
}

bool verificarOrden(const Indice *datos, int ce)
{
    printf("\n\nVerificando orden...");

    int cmpFecha, cmpClas;
    const Indice *p = datos;
    const Indice *fin = datos + ce - 1;

    while (p < fin)
    {
        cmpFecha = fechaComparar(&p->periodo, &(p + 1)->periodo);

        if (cmpFecha > 0)
            return false;

        if (cmpFecha == 0)
        {
            cmpClas = compararClasificador(p->clasificador, (p + 1)->clasificador);

            if (cmpClas < 0)
                return false;
        }

        p++;
    }

    return true;
}

void pruebaOrdenarPorPerYClas()
{
    printf("\nEjecutando pruebas para ordenarPorPerYClas...");

    int total;
    Indice indicesBase[] =
    {
        {{11, 4, 2023}, "", 0.0, "Items", 0.0, false, 0.0, false},
        {{6, 10, 2021}, "", 0.0, "Capitulos", 0.0, false, 0.0, false},
        {{21, 12, 2022}, "", 0.0, "Nivel general", 0.0, false, 0.0, false},
        {{6, 10, 2021}, "", 0.0, "Items", 0.0, false, 0.0, false},
        {{10, 4, 2023}, "", 0.0, "Items", 0.0, false, 0.0, false},
        {{6, 10, 2021}, "", 0.0, "Nivel general", 0.0, false, 0.0, false},
        {{6, 10, 2021}, "", 0.0, "Items", 0.0, false, 0.0, false},
    };

    total = sizeof(indicesBase) / sizeof(Indice);

    printf("\n\nAntes de ordenar");
    mostrarVIndices(indicesBase, total);

    ordenarIndices(indicesBase, total);

    printf("\n\nDespues de ordenar");
    mostrarVIndices(indicesBase, total);

    if (verificarOrden(indicesBase, total))
    {
        printf("\nOrden correcto\n");
    }
    else
    {
        printf("\nOrden incorrecto\n");
    }
}

void ordenarIndices(Indice *indices, int ce)
{
    int i, j;
    Indice *minPtr;
    Indice *currPtr;
    Indice temp;

    for (i = 0; i < ce - 1; i++)
    {
        minPtr = indices + i;

        for (j = i + 1; j < ce; j++)
        {
            currPtr = indices + j;

            if (compararIndices(currPtr, minPtr) < 0)
            {
                minPtr = currPtr;
            }
        }

        if (minPtr != indices + i)
        {
            temp = *(indices + i);
            *(indices + i) = *minPtr;
            *minPtr = temp;
        }
    }
}

void mostrarVIndices(const Indice* vector, int ce)
{
    const Indice* ptr;
    const Indice* fin;

    fin = vector + ce;

    for (ptr = vector; ptr < fin; ptr++)
    {
        imprimirIndice(ptr);
    }
}


void doubleToStr(double val, char *str, int size)
{
    snprintf(str, size, "%.2f", val);
}


// Esta función busca el índice anterior (mes anterior) y calcula la variación mensual
void buscarIndAnt(Indice *actual, Indice *todos)
{
    for (Indice *p = todos; p < actual; p++)
    {
        if (comparar(actual->nivelGeneralAperturas, p->nivelGeneralAperturas) == 0 &&
                comparar(actual->clasificador, p->clasificador) == 0 &&
                ((actual->periodo.m == p->periodo.m + 1 && actual->periodo.a == p->periodo.a) ||
                 (actual->periodo.m == 1 && p->periodo.m == 12 && actual->periodo.a == p->periodo.a + 1)))
        {
            actual->varMensual = roundf(calcVariacion(actual->indice, p->indice) * 10) / 10;
            actual->varMensualExiste = true;
            return;
        }
    }
    // Si no se encontró mes anterior, no se calcula
    actual->varMensualExiste = false;
    actual->varMensual = 0.0f;
}

// Test propuesto
void pruebaCalcVariacion()
{
    Indice indicesBase[] =
    {
        {{1,  1, 2022}, "Nivel general", 100.00f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  2, 2022}, "Nivel general", 103.80f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  3, 2022}, "Nivel general", 108.99f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  4, 2022}, "Nivel general", 111.50f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  5, 2022}, "Nivel general", 118.86f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  6, 2022}, "Nivel general", 126.70f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  7, 2022}, "Nivel general", 135.44f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  8, 2022}, "Nivel general", 145.60f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  9, 2022}, "Nivel general", 156.37f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1, 10, 2022}, "Nivel general", 167.79f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1, 11, 2022}, "Nivel general", 179.03f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1, 12, 2022}, "Nivel general", 186.73f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  1, 2023}, "Nivel general", 199.24f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  2, 2023}, "Nivel general", 211.20f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  3, 2023}, "Nivel general", 221.12f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  4, 2023}, "Nivel general", 239.03f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  5, 2023}, "Nivel general", 257.68f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  6, 2023}, "Nivel general", 272.62f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  7, 2023}, "Nivel general", 295.52f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  8, 2023}, "Nivel general", 339.26f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1,  9, 2023}, "Nivel general", 389.13f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1, 10, 2023}, "Nivel general", 416.76f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1, 11, 2023}, "Nivel general", 464.69f, "Capitulos", 0.0f, false, 0.0f, false},
        {{1, 12, 2023}, "Nivel general", 606.88f, "Capitulos", 0.0f, false, 0.0f, false}
    };

    float esperados[] =
    {
        0.0f, 3.8f, 5.0f, 2.3f, 6.6f, 6.6f, 6.9f, 7.5f, 7.4f, 7.3f, 6.7f, 4.3f,
        6.7f, 6.0f, 4.7f, 8.1f, 7.8f, 5.8f, 8.4f, 14.8f, 14.7f, 7.1f, 11.5f, 30.6f
    };
    int total = sizeof(indicesBase) / sizeof(Indice);
    int errores = 0;
    float *pEsp = esperados;

    Indice *fin = indicesBase + total;

    // Calcular variaciones
    for (Indice *p = indicesBase; p < fin; p++)
    {
        buscarIndAnt(p, indicesBase);
    }

    // Verificar resultados
    printf("\n\nPrueba de calcVariacion() usando aritmetica de punteros\n");

    for (Indice *p = indicesBase; p < fin; p++, pEsp++)
    {
        float dif = fabs(p->varMensual - *pEsp);
        if (dif > EPSILON)
        {
            printf("Error en mes %02d/%d: esperado %.1f, obtenido %.1f\n",
                   p->periodo.m, p->periodo.a, *pEsp, p->varMensual);
            errores++;
        }
        else
        {
            printf("Mes %02d/%d OK: %.1f\n", p->periodo.m, p->periodo.a, p->varMensual);
        }
    }

    if (errores == 0)
        printf("Todos los tests pasaron correctamente.\n");
    else
        printf("otal de errores: %d\n", errores);
}
