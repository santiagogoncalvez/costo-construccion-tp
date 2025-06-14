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

int main()
{
    system("chcp 65001");


    pruebaAgregarClasificador();
    pruebaAgregarClasificadorItems();
    pruebaOrdenarPorPerYClas();
    pruebaVariacionMensual();


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

void doubleToStr(double val, char *str, int size)
{
    snprintf(str, size, "%.2f", val);
}

void pruebaVariacionMensual()
{
    printf("\nEjecutando pruebas para calcularVariacionMensual...\n");

    CasoVarMensual casos[] = //valores sacados de la pagina que calcula las variaciones
    {
        {"2022-01-01", "Nivel General", "100", "0.00"},
        {"2022-01-01", "Materiales", "100", "0.00"},
        {"2022-01-01", "Mano de Obra", "100", "0.00"},
        {"2022-01-01", "Gastos generales", "100", "0.00"},
        {"2022-01-01", "Movimiento de tierras", "100", "0.00"},
        {"2022-01-01", "Estructura", "100", "0.00"},
        {"2022-01-01", "Albanileria", "100", "0.00"},
        {"2022-01-01", "Yeseria", "100", "0.00"},
        {"2022-01-01", "Instalacion sanitaria y contraincendio", "100", "0.00"},
        {"2022-01-01", "Instalacionde gas", "100", "0.00"},
        {"2022-01-01", "Instalacion electrica", "100", "0.00"},
        {"2022-01-01", "Carpinteria metalica y herreria", "100", "0.00"},
        {"2022-01-01", "Carpinteria de madera", "100", "0.00"},
        {"2022-01-01", "Ascensores", "100", "0.00"},
        {"2022-01-01", "Vidrios", "100", "0.00"},
        {"2022-01-01", "Pinturas", "100", "0.00"},
        {"2022-01-01", "Otros trabajos y gastos", "100", "0.00"},
        {"2022-02-01", "Nivel General", "103.809636", "3.81"},
        {"2022-02-01", "Materiales", "103.461974", "3.46"},
        {"2022-02-01", "Mano de Obra", "104.209035", "4.21"},
        {"2022-02-01", "Gastos generales", "103.622083", "3.62"},
        {"2022-02-01", "Movimiento de tierras", "103.812933254688", "3.81"},
        {"2022-02-01", "Estructura", "104.410773484463", "4.41"},
        {"2022-02-01", "Albanileria", "103.927129746759", "3.93"},
        {"2022-02-01", "Yeseria", "104.401086250664", "4.40"},
        {"2022-02-01", "Instalacion sanitaria y contraincendio", "103.745420563839", "3.75"},
        {"2022-02-01", "Instalacionde gas", "101.542653418102", "1.54"},
        {"2022-02-01", "Instalacion electrica", "103.949007322413", "3.95"},
        {"2022-02-01", "Carpinteria metalica y herreria", "105.61061404405", "5.61"},
        {"2022-02-01", "Carpinteria de madera", "104.348301581399", "4.35"},
        {"2022-02-01", "Ascensores", "100.573196712996", "0.57"},
        {"2022-02-01", "Vidrios", "102.077324810975", "2.08"},
        {"2022-02-01", "Pinturas", "101.735606808807", "1.74"},
        {"2022-02-01", "Otros trabajos y gastos", "103.472367445486", "3.47"}
    };

    int total = sizeof(casos) / sizeof(casos[0]);
    Indice indices[34];

    for(int i = 0; i < total; i++)
    {
        strcpy(indices[i].nivelGeneralAperturas, casos[i].nivelGeneralAperturas);
        indices[i].indice = atof(casos[i].indice);
        indices[i].variacion_mensual = 0;
    }

    calcularVarMensual(indices, total);

    int errores = 0;
    char salida[20];

    for (int i = 0; i < total; i++)
    {
        doubleToStr(indices[i].variacion_mensual, salida, sizeof(salida));

        if (strcmp(salida, casos[i].variacionMensual) != 0)
        {
            printf("prueba %d fallo: periodo='%s', nivel='%s' --> salida='%s' (esperado='%s')\n",
                   i + 1, casos[i].periodo, casos[i].nivelGeneralAperturas, salida, casos[i].variacionMensual);
            errores++;
        }
        else
        {
            printf("prueba %d paso: periodo='%s', nivel='%s' --> salida='%s'  (esperado='%s')  \n", i + 1, casos[i].periodo, casos[i].nivelGeneralAperturas, salida,casos[i].variacionMensual);
        }
    }

    printf("\nResumen: %d pasaron, %d fallaron.\n", total - errores, errores);
    assert(errores == 0 && "Al menos un prueba fallo en calcularVarMensual.");
}
