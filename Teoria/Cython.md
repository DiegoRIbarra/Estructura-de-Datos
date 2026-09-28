# Cython

cython es un lenguaje de programacion que nos permite escribir codigo con la sintaxis facil de python pero se ejecuta en c++, sirver para:
- optimizar partes lentas de un programa, especialmente bucles y calculos pesados
-  integrar python con librerias en x
- crear modulos compilados

el compilador  de cython convierte el codigo a C, realizando llamadas equivalentes a la API de Python/C permitiendo declarar paremtros y variables

## Como usarlo

se necesita: 
- instalar cython: **pip install cython**
- instalar un compilador en windows se pueden usar las buid tools de VS
- el codigo "wrapper" o archivos .pyx
- script de compilacion (setup.py) este script sirve para especificar que archivo de tipo pyx vamos a procesar 
- python setup.py buil_ext 