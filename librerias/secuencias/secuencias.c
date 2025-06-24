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
	char *pDest = cad;

	while (*pCad != '\0')
	{
		if (*pCad == ',' && !convertido)
		{
			*pDest = '.';
			convertido = 1;
			pDest++;
		}
		else if (*pCad != ',')
		{
			*pDest = *pCad;
			pDest++;
		}

		pCad++;
	}

	*pDest = '\0';
}

void convertirFecha(char *cadOrigen)
{
    char *pCadOrigen = cadOrigen;
    char cadDestino[11];
    char *pCadDestino = cadDestino;

    // La funcion esta recorriendo de vuelta desde el ultimo elemento el string cada vez. Cuando podria guardar el puntero al elemento siguiente a la ultima barra '/' en cada vez que se recorre o llega a ese punto.
    int cantBarras = 0, cantDig =  0;
    for(int i = 3; i > 1; i--)
    {
        while(*pCadOrigen && cantBarras <  i - 1)
        {
            if(*pCadOrigen == '/')
            {
                cantBarras++;
            }
            pCadOrigen++;
        }

        while(*pCadOrigen && *pCadOrigen != '/')
        {
            *pCadDestino = *pCadOrigen;
            pCadOrigen++;
            pCadDestino++;
            cantDig++;
        }


        if(i == 2)
        {
            if(cantDig == 1)
            {
                *pCadDestino = *(pCadDestino - 1);
                *(pCadDestino - 1) = '0';
                pCadDestino++;
            }
        }
        *pCadDestino = '/';
        pCadDestino++;

        pCadOrigen = cadOrigen;
        cantBarras = 0;
        cantDig = 0;
    }

    while(*pCadOrigen && *pCadOrigen != '/')
    {
        *pCadDestino = *pCadOrigen;
        pCadOrigen++;
        pCadDestino++;
        cantDig++;
    }

    if(cantDig == 1)
    {
        *pCadDestino = *(pCadDestino - 1);
        *(pCadDestino - 1) = '0';
        pCadDestino++;
    }

    *pCadDestino = '\0';


// Reemplazar '/' por '-'
    pCadDestino = cadDestino;
    while(*pCadDestino)
    {
        if(*pCadDestino == '/')
        {
            *pCadDestino = '-';
        }
        pCadDestino++;
    };

// Reemplazar la nueva cadena en la cadena origianl
    pCadOrigen = cadOrigen;
    pCadDestino = cadDestino;
    while(*pCadDestino)
    {
        *pCadOrigen = *pCadDestino;
        pCadOrigen++;
        pCadDestino++;
    }

    *pCadOrigen = '\0';
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
        switch(*iCad){
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

char abcdario(char cad,int pos)
{
    char abc[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\0'};
    int num=0;

    while(tolower(cad)!=abc[num])
    {
        num++;
    }
    if(pos%2==0)
    {
        for(int i=0; i<4; i++)
        {
            num++;
            if(abc[num]=='\0')
            {
                num=0;
            }

        }
    }
    else
    {
        for(int i=0; i<2; i++)
        {
            num++;
            if(abc[num]=='\0')
            {
                num=0;
            }

        }
    }

    if(islower(cad))
    {
        return abc[num];

    }
    else
    {
        return toupper(abc[num]);
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
    *iCad=toupper(*iCad);
    iCad++;
    while(*iCad!='\0')
    {
        if('_'==*iCad)
        {
            *iCad=' ';
        }
        else
        {
            *iCad=tolower(*iCad);
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
        if(*iCad == '_') {
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
            ultimo = str;  // Guardamos la dirección actual si hay coincidencia
        }
        str++;  // Avanzamos el puntero
    }

    // Considerar el caso en que c sea '\0'
    if ((char)c == '\0')
    {
        return (char *)str;  // str apunta al carácter nulo al salir del while
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

    // Si el carácter buscado es el nulo '\0', también se considera válido
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
