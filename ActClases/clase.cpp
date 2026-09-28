#include <iostream>
#include <vector>
#include <string>

typedef struct alumno{
    std::string nombre;
    int cal_U1;
    int cal_U2;
    float prom;
}ALUMNO;

typedef struct alumno* PTR_ALUMNO;

typedef int* PTR_INT;

int main(){
    PTR_INT ptr_U1;


    ALUMNO cesar;

    PTR_ALUMNO ptr_cesar=&cesar;
    struct alumno sofi;
    sofi.nombre="sofia";
    sofi.cal_U1=80;
    sofi.cal_U2=100;
    sofi.prom=(sofi.cal_U1+sofi.cal_U2)/2;

    ptr_U1=&sofi.cal_U1;
    std::cout<<*ptr_U1<<std::endl;

    std::cout<<sofi.nombre<<" "<<sofi.prom<<std::endl;

   struct alumno  alumnos[5];
   alumnos[0].nombre= "gina";
   alumnos[0].cal_U1=100;
   alumnos[0].cal_U2=100;
   alumnos[0].prom=(alumnos[0].cal_U1+alumnos[0].cal_U2)/2;


   ptr_U1=&alumnos[0].cal_U1;
   std::cout<<*ptr_U1<<std::endl;

   ptr_cesar=&alumnos[0];
   std::cout<<(*ptr_cesar).nombre<<std::endl;
   alumnos[1].nombre= "Carlos";
   alumnos[1].cal_U1=100;
   alumnos[1].cal_U2=90;
   alumnos[1].prom=(alumnos[1].cal_U1+alumnos[1].cal_U2)/2;

   alumnos[2].nombre= "Angel";
   alumnos[2].cal_U1=50;
   alumnos[2].cal_U2=70;
   alumnos[2].prom=(alumnos[2].cal_U1+alumnos[2].cal_U2)/2;

   for (int i = 0; i < 3; i++){
    std::cout<<alumnos[i].nombre<<" "<<alumnos[i].prom<<std::endl;
   }
   

   

    return 0;
}