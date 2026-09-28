#include <iostream>
#include <vector>
#include <string>
//mostrar array atraves de funcion
//structs
//un struct es un tipo de clase "primitiva" ya que no tiene metodos  y solo guarda una serie de variables
//la declaracion es aqui, ya que su uso correcto es como variable de tipo global
struct myest{
     int a;
     float b;
     std::string n;
};

struct almn{
    std::string nombre;
    int cal1;
    int cal2;
};

//prototipo de la funcion
void mostArr(int a[], int s);

int main(){
    //array prellenado -> int arr[4]={0,1,2,3,4}
    //array vacio -> int arr2[4];
    int arr2[4]={};
    //asi se muestra un array por for simple
    //for (int i = 0; i < 4; i++){
      //  std::cout<<arr2[i]<<std::endl;
    //
    //instancia de un struct, por lo tanto los datos del struct varian de si tengo una instancia S a la instancia X
    struct myest x[5]; //declaracion de un array de structs
    //llenado de solo un elemento de array de structs
    x[0].a=10;
    x[0].b=3.14f;
    x[0].n="hola";
    struct almn s[5]; //declaracion de un array de structs
    //llenado del array de structs
    for (int i = 0; i < 5; i++){
        s[i].nombre="Alumno"+std::to_string(i+1);
        s[i].cal1=i+1;
        s[i].cal2=(i+1)*2.5;
    }
   
    //declaracion de un vector de structs
    std::vector<struct almn> alumnos;
    //se le agregan 5 structs al vector
    for (int i = 0; i < 5; i++){
        struct almn a;
        a.nombre="Alumno"+std::to_string(i+1);
        a.cal1=rand()%10+1;
        a.cal2=rand()%10+1;
        alumnos.push_back(a);
    }

    mostArr(arr2,4);
    return 0;
}
//funcion
void mostArr(int a[], int s){
     for (int i = 0; i < s; i++){
        std::cout<<a[i]<<std::endl;
    }
}


