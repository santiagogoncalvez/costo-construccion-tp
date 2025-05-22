# TP_Topicos_2025_1c_miercoles_LOS_CIBERNETICOS

## Cómo compilar en Code::Blocks

Abrir `proyecto.cbp` y presionar F9.

**No subas archivos personales o temporales**

Evitá subir cosas como:

-  Rutas absolutas (como C:/Users/...). Usá rutas relativas al proyecto: `#include "../include/mis_funciones.h"`
-  `.cbp` con rutas específicas
-  Archivos temporales del compilador
-  Tu configuración de entorno
-  Ejecutables para Windows (.exe)

## Consignas del trabajo

Fecha de inicio: 18/05/2025
Fecha de entrega: 20/06/2025
Fecha de defensa: 26/05/2025

-  Las funciones tienen que funcionar mínimo para todos los casos de prueba que presentan.
-  Vectores y cadenas de texto deberán ser manipulados utilizando aritmética de punteros.
-  Las soluciones tienen que ser eficientes:
   En el uso de memoria: no declarar vectores o matrices auxiliares si no es necesario.
   En cantidad de ciclos de procesador y en el caso de matrices las soluciones deben ser óptimas.
   En recorridos de archivos: estos tienen que ser mínimos.
-  Nunca acceder a memoria que no nos pertenece
-  Declarar variables al inicio del bloque y no utilizar VLA (Variable length arrays).
- Código prolijo y dividido en funciones.
- Poner nombres significativos a las variables.
- Las soluciones tienen que estar desarrolladas en ANSI C para garantizar tanto como sea posible compatibilidad multiplataforma.
- Nunca mezclar funciones de manipulación de archivos de texto con funciones de operación de archivos binarios.
- Las funciones no deben tener errores ni warnings.