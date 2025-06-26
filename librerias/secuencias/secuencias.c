#include "secuencias.h"

int comparar(const char* cad1, const char* cad2)
{
    while (*cad1 && *cad2 && *cad1 == *cad2)
    {
        cad1++;
        cad2++;
    }

    return (unsigned char)*cad1 - (unsigned char)*cad2;
}

int compararClasificador(const char* cadClas1, const char* cadClas2)
{
    char clasificadores[3][15] = {{"Items\0"}, {"Capitulos\0"}, {"Nivel general\0"}};

    int posCadClas1 = buscarMatriz(clasificadores, cadClas1, 3);
    int posCadClas2 = buscarMatriz(clasificadores, cadClas2, 3);

    if(posCadClas1 < posCadClas2)
    {
        return -1;
    }

    if(posCadClas1 > posCadClas2)
    {
        return 1;
    }

    return 0;
}

int buscarMatriz (const char matriz[][15], const char *cadBuscar, int ce)
{
    int pos = -1;
    for (int i = 0; i < ce; i++)
    {
        if(comparar(cadBuscar, matriz[i]) == 0)
        {
            pos = i;
        }
    }

    return pos;
}

int compararTipoVariable(const char* cadClas1, const char* cadClas2)
{
    char tiposVariables[3][15] = {{"var_interanual\0"}, {"var_mensual\0"}, {"indice_icc\0"}};

    int posCadClas1 = buscarMatriz(tiposVariables, cadClas1, 3);
    int posCadClas2 = buscarMatriz(tiposVariables, cadClas2, 3);

    if(posCadClas1 < posCadClas2)
    {
        return -1;
    }

    if(posCadClas1 > posCadClas2)
    {
        return 1;
    }

    return 0;
}

void convertirComa(char *cad)
{
    int convertido = 0;
    char *pCad = cad;

    while (*pCad != '\0')
    {
        if (*pCad == ',' && !convertido)
        {
            *pCad = '.';       // Solo reemplaza la primera coma por punto
            convertido = 1;
        }
        pCad++;
    }
}

void copiar(char* cadDestinio,char* cadOrigen)
{
    while(*cadOrigen!='\0')
    {
        *cadDestinio=*cadOrigen;
        cadOrigen++;
        cadDestinio++;
    }
    *cadDestinio='\0';
}

void desencriptarPorCaso(char *cad)
{
    char *iCad = cad;
    while(*iCad != '\0')
    {
        switch(*iCad)
        {
        case '@':
            *iCad='a';
            break;

        case '8':
            *iCad='b';
            break;

        case '3':
            *iCad='e';
            break;

        case '1':
            *iCad='i';
            break;

        case '0':
            *iCad='o';
            break;

        case '$':
            *iCad='s';
            break;

        case '7':
            *iCad='t';
            break;

        case '|':
            *iCad='l';
            break;

        case '5':
            *iCad='m';
            break;

        case '9':
            *iCad='n';
            break;
        }

        iCad++;
    }
}

void desencriptarPorPos(char* cadoriginal)
{
    char* cadcopia=cadoriginal;
    while(*cadcopia!='\0')
    {
        if(espalabra(*cadcopia))
        {
            *cadcopia=abcdario(*cadcopia,(cadcopia-cadoriginal));
        }
        cadcopia++;
    }
}

bool espalabra(char cadcopia)
{
    return (cadcopia>='a' && cadcopia<='z') || (cadcopia>='A' && cadcopia<='Z');
}

char abcdario(char cad, int pos)
{
    char abc[27] =
    {
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n',
        'o','p','q','r','s','t','u','v','w','x','y','z','\0'
    };

    int num = 0;

    // Buscar la letra en abc usando punteros
    while (toLowerProp(cad) != *(abc + num))
    {
        num++;
    }

    // Avanzar 4 o 2 posiciones seg�n paridad de pos
    int saltos = (pos % 2 == 0) ? 4 : 2;

    for (int i = 0; i < saltos; i++)
    {
        num++;
        if (*(abc + num) == '\0')
        {
            num = 0;
        }
    }

    // Devolver en may�scula si corresponde
    if (isLowerProp(cad))
    {
        return *(abc + num);
    }
    else
    {
        return toUpperProp(*(abc + num));
    }
}


void eliminarTodasLasComillas(char *cad)
{
    char *pLectura = cad;
    char *pEscritura = cad;

    while (*pLectura != '\0')
    {
        if (*pLectura != '"')
        {
            *pEscritura = *pLectura;
            pEscritura++;
        }
        // Si es comilla, simplemente no la copiamos
        pLectura++;
    }

    *pEscritura = '\0'; // Terminamos la cadena correctamente
}

void normalizar(char* cad)
{
    char* iCad = cad;
    *iCad=toUpperProp(*iCad);
    iCad++;
    while(*iCad!='\0')
    {
        if('_'==*iCad)
        {
            *iCad=' ';
        }
        else
        {
            *iCad=toLowerProp(*iCad);
        }
        iCad++;
    }
}

void sacarAntYNormalizar(char *cad)
{
    char *iCad = cad;
    int encontrado = 0, lugaresAntesGuion = 0;
    while(*iCad != '\0' && !encontrado)
    {
        if(*iCad == '_')
        {
            encontrado = 1;
        }
        lugaresAntesGuion++;
        iCad++;
    }

    while(*iCad != '\0')
    {
        *(iCad - lugaresAntesGuion) = *iCad;
        iCad++;
    }

    *(iCad - lugaresAntesGuion) = '\0';

    normalizar(cad);
}

char *strrchrProp(const char *str, int c)
{
    const char *ultimo = NULL;

    while (*str != '\0')
    {
        if (*str == (char)c)
        {
            ultimo = str;  // Guardamos la direcci�n actual si hay coincidencia
        }
        str++;  // Avanzamos el puntero
    }

    // Considerar el caso en que c sea '\0'
    if ((char)c == '\0')
    {
        return (char *)str;  // str apunta al car�cter nulo al salir del while
    }

    return (char *)ultimo;
}

char *strchrProp(const char *str, int c)
{
    while (*str != '\0')
    {
        if (*str == (char)c)
            return (char *)str;
        str++;  // avanzar el puntero
    }

    // Si el car�cter buscado es el nulo '\0', tambi�n se considera v�lido
    if ((char)c == '\0')
        return (char *)str;

    return NULL;
}

char toLowerProp(char c)//mayuscula en minuscula
{
    if(c>='A' && c<='Z')
    {
        c+=32;
        return c;
    }
    return c;
}

char toUpperProp(char c)
{
    if(c>='a' && c<='z')
    {
        c-=32;
        return c;
    }
    return c;
}

int esDigito(char* c)
{
    return (*c >= '0' && *c <= '9');
}

void reemplazar3ComasPorPuntoYComa(char* cad)
{
    char* p = cad;
    int contador = 0;

    while (*p && contador < 3)
    {
        if (*p == ',')
        {
            *p = ';';
            contador++;
        }
        p++;
    }
}

void expandirFechaConGuion01(char* cad)
{
    char* p = cad;

    while (*p)
    {
        // Buscar patrC3n: aaaa-mm y detrC!s viene separador
        if (esDigito(p) && esDigito(p + 1) && esDigito(p + 2) && esDigito(p + 3) &&
                *(p + 4) == '-' &&
                esDigito(p + 5) && esDigito(p + 6) &&
                (*(p + 7) == ';' || *(p + 7) == ',' || *(p + 7) == ' ' || *(p + 7) == '\0'))
        {

            // Mover todo desde p+7 tres posiciones a la derecha
            char* fin = p;
            while (*fin) fin++;
            while (fin >= p + 7)
            {
                *(fin + 3) = *fin;
                fin--;
            }

            // Insertar "-01"
            *(p + 7) = '-';
            *(p + 8) = '0';
            *(p + 9) = '1';
            return;
        }

        p++;
    }
}

void agregarSMovimientoTierra(char* cad)
{
    const char* ref = "Movimiento de tierra";
    char* p = cad;

    while (*p)
    {
        char* q = p;
        const char* r = ref;

        while (*q && *r && *q == *r)
        {
            q++;
            r++;
        }

        // Si llegamos al final de la palabra buscada
        if (!*r && (*q == ';' || *q == ',' || *q == '\0' || *q == ' '))
        {
            if (*q != 's')
            {
                // Mover todo 1 posiciC3n hacia la derecha para insertar 's'
                char* fin = q;
                while (*fin) fin++;
                while (fin >= q)
                {
                    *(fin + 1) = *fin;
                    fin--;
                }
                *q = 's';
            }
            return;
        }

        p++;
    }
}

void modificarCadenaTxtIndec(char* cad)
{
    reemplazar3ComasPorPuntoYComa(cad);
    expandirFechaConGuion01(cad);
    agregarSMovimientoTierra(cad);
    convertirComa(cad);
}

int isLowerProp(char c)
{
    const char *letras = "abcdefghijklmnopqrstuvwxyz";
    const char *p = letras;

    while (*p != '\0') {
        if (c == *p) {
            return 1; // Es min�scula
        }
        p++;
    }

    return 0; // No es min�scula
}
