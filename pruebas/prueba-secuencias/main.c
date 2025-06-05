#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../../librerias/secuencias/secuencias.h"

typedef struct
{
    const char *entrada;
    const char *esperado;
} CasoPrueba;

void pruebaFormatearFecha();
void pruebaNormalizar();
void pruebaConvertirComa();
void pruebaDesencriptarPorPos();

int main()
{
    system("chcp 65001");


    pruebaFormatearFecha();
    pruebaNormalizar();
    pruebaConvertirComa();
    pruebaDesencriptarPorPos();

    return 0;
}

void pruebaFormatearFecha()
{
    CasoPrueba fechas[] =
    {
        {"1/4/2004",    "2004/4/1"},
        {"01/04/2004",  "2004/04/01"},
        {"1/04/3004",   "3004/04/1"},
        {"10/12/1999",  "1999/12/10"},
        {"9/9/2022",    "2022/9/9"},
        {"31/12/2023",  "2023/12/31"},
        {"7/11/1980",   "1980/11/7"},
        {"3/3/2000",   "2000/3/3"}
    };

    char salida[100]; // AAAA/MM/DD + '\0'
    int total = sizeof(fechas) / sizeof(fechas[0]);
    int errores = 0;

    printf("\nEjecutando pruebas para formatearFecha...\n");

    for (int i = 0; i < total; i++)
    {
        convertirFecha(salida, fechas[i].entrada);
        if (strcmp(salida, fechas[i].esperado) != 0)
        {
            printf("prueba %d fallo: entrada='%s' --> salida='%s' (esperado='%s')\n",
                   i + 1, fechas[i].entrada, salida, fechas[i].esperado);
            errores++;
        }
        else
        {
            printf("prueba %d paso: %s --> %s\n", i + 1, fechas[i].entrada, salida);
        }
    }

    printf("\nResumen: %d pasaron, %d fallaron.\n", total - errores, errores);
    assert(errores == 0 && "Al menos un prueba fallo en formatear_fecha.");
}

void pruebaNormalizar()
{
    CasoPrueba casos[] =
    {
        {"materiales_para_la_construCcion", "Materiales para la construccion"},
        {"mano_de_obra",                    "Mano de obra"},
        {"gastos_generales",                "Gastos generales"},
        {"EQUIPAMIENTO",                    "Equipamiento"},
        {"servicios_varios",               "Servicios varios"},
        {"costos_DIRECTOS",                "Costos directos"},
        {"costo_total",                    "Costo total"},
        {"INSTALACIONES_electricas",       "Instalaciones electricas"},
        {"obras_de_albanileria",           "Obras de albanileria"},
        {"acabados_exteriores",            "Acabados exteriores"},
        {"estructURA_de_hormigon",         "Estructura de hormigon"},
        {"infrAesTruCtura_basica",         "Infraestructura basica"},
        {"componentes_Industrializados",   "Componentes industrializados"},
    };

    char salida[100];
    int total = sizeof(casos) / sizeof(casos[0]);
    int errores = 0;

    printf("\n\nEjecutando pruebas para normalizar...\n");

    for (int i = 0; i < total; i++)
    {
        strcpy(salida, casos[i].entrada);
        normalizar(salida);
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
    assert(errores == 0 && "Al menos un prueba fallo en normalizar.");
}

void pruebaConvertirComa()
{
    CasoPrueba casos[] =
    {
        {"100",               "100"},
        {"103,809635871582",  "103.809635871582"},
        {"103,461973487762",  "103.461973487762"},
        {"104,20903483914",   "104.20903483914"},
        {"103,622082838899",  "103.622082838899"},
        {"108,957034113846",  "108.957034113846"},
        {"107,610731574899",  "107.610731574899"},
        {"110,388768498453",  "110.388768498453"},
        {"108,74966701378",   "108.74966701378"},
        {"111,477783912457",  "111.477783912457"},
        {"112,466181061394",  "112.466181061394"},
        {"110,436924672631",  "110.436924672631"},
        {"111,575811880948",  "111.575811880948"},
        {"118,877112315922",  "118.877112315922"},
        {"117,432927656879",  "117.432927656879"},
        {"120,535830045748",  "120.535830045748"},
        {"118,083775296862",  "118.083775296862"},
        {"126,709991582415",  "126.709991582415"},
        {"123,566031760395",  "123.566031760395"},
        {"130,22540793836",   "130.22540793836"},
        {"125,428845889941",  "125.428845889941"},
    };

    char salida[100];
    int total = sizeof(casos) / sizeof(casos[0]);
    int errores = 0;

    printf("\n\nEjecutando pruebas para convertirComa...\n");

    for (int i = 0; i < total; i++)
    {
        strcpy(salida, casos[i].entrada);
        convertirComa(salida);
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
    assert(errores == 0 && "Al menos un prueba fallo en convertirComa.");
}

void pruebaDesencriptarPorPos()
{
    CasoPrueba casos[] =
    {
        {"jgrch_ccjcnyh",           "nivel_general"},
        {"iypcngwjaq",              "materiales"},
        {"iyjm_ba_kzny",            "mano_de_obra"},
        {"cyorkq_ealapwjaq",        "gastos_generales"},

        {"jgrch_ccjcnyh",           "nivel_general"},
        {"iypcngwjaq",              "materiales"},
        {"iyjm_ba_kzny",            "mano_de_obra"},
        {"cyorkq_ealapwjaq",        "gastos_generales"},

        {"jgrch_ccjcnyh",           "nivel_general"},
        {"iypcngwjaq",              "materiales"},
        {"iyjm_ba_kzny",            "mano_de_obra"},
        {"cyorkq_ealapwjaq",        "gastos_generales"},

        {"jgrch_ccjcnyh",           "nivel_general"},
        {"iypcngwjaq",              "materiales"},
        {"iyjm_ba_kzny",            "mano_de_obra"},
        {"cyorkq_ealapwjaq",        "gastos_generales"},

        {"jgrch_ccjcnyh",           "nivel_general"},
        {"iypcngwjaq",              "materiales"},
        {"iyjm_ba_kzny",            "mano_de_obra"},
        {"cyorkq_ealapwjaq",        "gastos_generales"},

        {"jgrch_ccjcnyh",           "nivel_general"},
        {"iypcngwjaq",              "materiales"}
    };

    char salida[100];
    int total = sizeof(casos) / sizeof(casos[0]);
    int errores = 0;

    printf("\n\nEjecutando pruebas para normalizar...\n");

    for (int i = 0; i < total; i++)
    {
        strcpy(salida, casos[i].entrada);
        desencriptarPorPos(salida);
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
    assert(errores == 0 && "Al menos un prueba fallo en normalizar.");
}
