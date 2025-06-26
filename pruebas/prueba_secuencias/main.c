#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../librerias/secuencias/secuencias.h"

typedef struct
{
    char *entrada;
    char *esperado;
} CasoPrueba;

void pruebaNormalizar();
void pruebaConvertirComa();
void pruebaDesencriptarPorPos();

int main()
{
    system("chcp 65001");

    pruebaNormalizar();
    pruebaConvertirComa();
    pruebaDesencriptarPorPos();

    return 0;
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
        CasoPrueba *caso = casos + i;
        copiar(salida, caso->entrada);
        normalizar(salida);
        if (comparar(salida, caso->esperado) != 0)
        {
            printf("prueba %d fallo: entrada='%s' --> salida='%s' (esperado='%s')\n",
                   i + 1, caso->entrada, salida, caso->esperado);
            errores++;
        }
        else
        {
            printf("prueba %d paso: %s --> %s\n", i + 1, caso->entrada, salida);
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
        CasoPrueba *caso = casos + i;
        copiar(salida, caso->entrada);
        convertirComa(salida);
        if (comparar(salida, caso->esperado) != 0)
        {
            printf("prueba %d fallo: entrada='%s' --> salida='%s' (esperado='%s')\n",
                   i + 1, caso->entrada, salida, caso->esperado);
            errores++;
        }
        else
        {
            printf("prueba %d paso: %s --> %s\n", i + 1, caso->entrada, salida);
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
        CasoPrueba *caso = casos + i;
        copiar(salida, caso->entrada);
        desencriptarPorPos(salida);
        if (comparar(salida, caso->esperado) != 0)
        {
            printf("prueba %d fallo: entrada='%s' --> salida='%s' (esperado='%s')\n",
                   i + 1, caso->entrada, salida, caso->esperado);
            errores++;
        }
        else
        {
            printf("prueba %d paso: %s --> %s\n", i + 1, caso->entrada, salida);
        }
    }

    printf("\nResumen: %d pasaron, %d fallaron.\n", total - errores, errores);
    assert(errores == 0 && "Al menos un prueba fallo en normalizar.");
}
