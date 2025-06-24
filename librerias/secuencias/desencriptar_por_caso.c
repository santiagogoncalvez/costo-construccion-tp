#include "secuencias.h"

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
