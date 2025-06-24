# Indices del costo de la contrucción - TP de Tópicos (2025)

## Qué hace el proyecto

Permite **procesar índices y variaciones** del indicador económico de **Costo de la Construcción**, generando un archivo binario final con los datos procesados.

## Estructura del proyecto

`/src`: va a contener el proyecto principal encargado de procesar los datos y generar el archivo binario.

`/librerias`: va a contener las librerías que se utilicen.

`/datos`: va a contetner los archivos de datos que serán procesados.

`/salida`: va a ser la carpeta destino del archivo binario que se va a generar.

`/documentos`: va a contener las consignas y documentos del trabajo.

`/pruebas`: va a contener las funciones y códigos que prueben y examinen el proyecto principal y las librerías.

## Librerías

- `estructura_indice`: contiene la estructura Indice y las funciones que se encargan de modificar esta estructura.

- `secuencias`: contiene funciones de modificación y manejo de cadenas.

- `TDA_fecha`: contiene el TDA para manejo de fechas.

- `TDA_fecha`: contiene el TDA para manejo de vectores mediante memoria dinámica.


# Cómo compilar en Code::Blocks

## Opción recomendada: Usar el workspace

1. Abrí el archivo `gen_indice_bin.workspace` con Code::Blocks.
2. Hacé **Click derecho en Workspace → Build Workspace** para compilar todos los proyectos (librerías y proyecto principal) en orden.
3. Ejecutá el proyecto `gen_indice_bin` desde el workspace (clic derecho → **Run project** o botón Run).

## Opción alternativa: Compilar proyectos individualmente

1. Abrí los archivos `.cbp` de cada librería y del proyecto principal uno por uno.
2. Hacé build a cada proyecto por separado, respetando el orden de las dependencias (primero las librerías, después el proyecto principal).
3. Ejecutá el proyecto `gen_indice_bin` después de compilar todo.


## 📌 Reglas y Requerimientos

-  Cada función va a tener su propio archivo separado: `nombre-funcion.c`. Estas van a estar incluidas dentro de un archivo `proyecto.h`.
-  Las funciones tienen que funcionar mínimo para todos los casos de prueba que presentan.
-  Vectores y cadenas de texto deberán ser manipulados utilizando aritmética de punteros.
-  Las soluciones tienen que ser eficientes:
   En el uso de memoria: no declarar vectores o matrices auxiliares si no es necesario.
   En cantidad de ciclos de procesador y en el caso de matrices las soluciones deben ser óptimas.
   En recorridos de archivos: estos tienen que ser mínimos.
-  Nunca acceder a memoria que no nos pertenece
-  Declarar variables al inicio del bloque y no utilizar VLA (Variable length arrays).
-  Código prolijo y dividido en funciones.
-  Poner nombres significativos a las variables.
-  Las soluciones tienen que estar desarrolladas en ANSI C para garantizar tanto como sea posible compatibilidad multiplataforma.
-  Nunca mezclar funciones de manipulación de archivos de texto con funciones de operación de archivos binarios.
-  Las funciones no deben tener errores ni warnings.

**Grupo:** LOS CIBERNÉTICOS  
**Cátedra:** Tópicos de Programación - 1C 2025 - Miércoles
