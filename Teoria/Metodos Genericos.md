# Metodos Genericos o Templates

## Que son? 

Una plantilla permite definir funciones o clases sin especificar los tipos de datos exactos sobre los que operan, es decir, actua como un plano o molde para crear funciones o clases genericas que pueden manejar cualquier tipo de dato sin tener que reescribir el codigo para cada tipo.

Para poder hacer estas plantillas se usa la palabra  clave `typename` o `class` por convencion se usa la letra `T` (de type)


``` c++
//comparacion de declaracion
void BubbleSort(int *a)//el tipo de dato se especifico como int

<template T>
void BubbleSort(T *a)//el tipo de dato al ser  ahora de tipo T acepta cualquier tipo de dato
```

## Aplicaciones

Las pantillas  de metodos se usan para
- Crear una unica funcion que pueda aplicar la misma logica con cualquier tipo de dato
- Hacer mas facil la reutilizacion de codigo al solo escribir una funcion

### Ejemplo de uso 

``` c++
#include <iostream>
#include <string>


template <typename T>

T encontrarMaximo(T a, T b){
    return (a>b) ? a : b;
}

int main(){
    //primero enteros
    int num1=25;
    int num2=50;
    std::cout<<"El mayor de los int es: "<<encontrarMaximo(num1, num2)<<"\n";

    //ahora con los float
    float f1=34.5;
    float f2=59;
    std::cout<<"El mayor de los float es: "<<encontrarMaximo(f1, f2)<<"\n";

    //se prueba con los string 
    std::string palabra1="Hola";
    std::string palabra2="Parangaricutimiricuaro";
    std::cout<<"La palabra mas grande? es : "<<encontrarMaximo(palabra1, palabra2)<<"\n";
    return 0;
}


```

## Convencion de nombres
- **Tipo T:** este tipo de dato es el principal de la clase y puede contener cualquier tipo

- **Tipos Secundarion:** Son datos genericos adicionales necesarios en la misma plantilla `template<typename T , typename U>`

- **Clave (Key):** Se usa para representar el tipo de la clave en estructuras asociativas `std::map <K, V>`

# Recursividad


la 

