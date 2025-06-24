#include "secuencias.h"

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
