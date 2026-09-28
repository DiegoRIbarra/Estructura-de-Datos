
# Scope
el scope es el alcance de la variable

**global**: es aquella variable que existe globalmente y puede ser accedida desde cualquier punto del programa
**local**: es aquella que se define internamente en las funciones (si, main es una) y su ciclo de vida solo es desde que se define y acaba la funcion
**bloque**: es aquella  que solo existe durante la ejecucion de un bloque de codigo por ejemplo cuando se declara el int i dentro de un for


##  Parametros?

los parametros de tipo valor son considerados de tipo local, cuando es de referencia es decir es puntero, deja de existir cuando el dato referenciado deja de existir 
un struct es un tipo de clase "primitiva" ya que no tiene metodos  y solo guarda una serie de variables

### Fibonacci en c

``` c
//en este programa se calcula la sucesion de fibonacci en c
//el mejor tambalache de variables que se me pudo ocurrir
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n, a = 0, b = 1, c;
    printf("Ingrese el numero de elementos que se calcularan de la sucesion: ");
    scanf("%d", &n);
    printf("0 1 ");
    for (int i = 2; i < n; i++){
        c = a + b;
        printf("%d ", c);
        a = b;
        b = c;
    }
    return EXIT_SUCCESS;
}
```


### Clase Jueves 18

**arrays dinamicos**, para agrandar un array sin perder datos se crea un nuevo array con la nueva dimension y se copian los datos antiguos al nuevo array obvio se usan punteros

``` c++

#include<iostream>

int main(){
    int *ptr_a;
    int tam=4;
    int *ptr_aux=nullptr;
    ptr_a=nullptr;
    ptr_a =new int[1];
    tam++;

    ptr_a[0]=3;

    ptr_aux=new int[tam];
    for (int i = 0; i <1; i++)
    {
        ptr_aux[1]=ptr_a[i];
    }
    delete[] ptr_a;
    ptr_a=ptr_aux;
    ptr_aux=nullptr;

   for (int i = 0; i < tam; i++){
       std::cout << ptr_a[i] << std::endl;
   }
   std::cout<<"se redimensiona el array"<<std::endl;
   tam=3;

   ptr_aux= new int[tam];
    for (int i = 0; i < 2; i++){
        ptr_aux[i]=ptr_a[i];
    }
   delete[] ptr_a;
   ptr_a=ptr_aux;
   ptr_aux=nullptr;
    for (int i = 0; i < tam; i++){
       std::cout << ptr_a[i] << std::endl;
   }

    return 0;
}

```