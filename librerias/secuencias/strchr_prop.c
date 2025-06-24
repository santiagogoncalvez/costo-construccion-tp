#include "secuencias.h"

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
