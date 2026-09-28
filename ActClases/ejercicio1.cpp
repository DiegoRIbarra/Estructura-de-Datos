#include <iostream>
#include <string>

typedef struct alumno{
    std::string nombre;
    int cal_U1;
    int cal_U2;
    float prom;
}ALUMNO;

int main(){
    ALUMNO x[10];

    for (int i = 0; i < 10; i++){
        std::cout<<"ingrese el nombre del alumno"<<std::endl;
        std::cin>>x[i].nombre;
        std::cout<<"ingrese la calificacion de la unidad 1 del "<<x[i].nombre<<std::endl;
        std::cin>>x[i].cal_U1;
        std::cout<<"ingrese la calificacion de la unidad 2 del "<<x[i].nombre<<std::endl;
        std::cin>>x[i].cal_U2;
        x[i].prom= float(x[i].cal_U1+x[i].cal_U2)/2;
    }

    for (int i = 0; i < 10; i++){
        std::cout<<x[i].nombre<<" "<<"promedio: "<<x[i].prom<<std::endl;
    }
    return 0;
}