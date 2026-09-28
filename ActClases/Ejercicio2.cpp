#include <iostream>
#include <string>

int buscarAlumno(std::string matricula);
std::string matriculas[5];

int main(){
    //declaramos los arrays
    
    int U1[5];
    int U2[5];
    int U3[5];
    int U4[5];
    std::string aux;
    int aux1=0,aux2=0,aux3=0;

    float prom;

    for (int i = 0; i < 5; i++){
        std::cout<<"ingrese la matricula del alumno "<<i<<std::endl;
        std::cin>>matriculas[i];
        std::cout<<"ingrese la calificacion de la unidad uno del alumno "<<matriculas[i]<<std::endl;
        std::cin>>U1[i];
        std::cout<<"ingrese la calificacion de la unidad dos del alumno "<<matriculas[i]<<std::endl;
        std::cin>>U2[i];
        std::cout<<"ingrese la calificacion de la unidad tres del alumno "<<matriculas[i]<<std::endl;
        std::cin>>U3[i];
        std::cout<<"ingrese la calificacion de la unidad cuatro del alumno "<<matriculas[i]<<std::endl;
        std::cin>>U4[i];
    }
    int control;
    do{
        std::cout<<"que desea hacer"<<std::endl;
        std::cout<<"1.-Ver Calificaciones Generales 2.-Editar Calificacion 3.-Promedio del alumno"<<std::endl;
        std::cout<<"4.-Promedio por Unidad  0.-Salir"<<std::endl;
        std::cin>>control;
        switch (control){
        case 1:
            for (int i = 0; i < 5; i++){
                std::cout<<"Matricula: "<<matriculas[i]<<" U1: "<<U1[i]<<" U2: "<<U2[i]<<" U3: "<<U3[i]<<" U4: "<<U4[i]<<std::endl;
            }
            break;
        case 2: 
            std::cout<<"Ingrese la matricula del alumno a buscar"<<std::endl;
            std::cin>>aux;
            aux1=buscarAlumno(aux);
            if (aux1==10){
                std::cout<<"El alumno no existe";
            }else{
                std::cout<<"Ingrese la unidad que quiere modificar: ";
                std::cin>>aux2;
                std::cout<<"Ingrese la nueva calificacion";
                std::cin>>aux3;
                switch (aux2){
                    case 1:
                        U1[aux1]=aux3;
                        break;
                    case 2:
                        U2[aux1]=aux3;
                        break;
                    case 3:
                        U3[aux1]=aux3;
                        break;
                    case 4:
                        U4[aux1]=aux3;
                        break;
                    default:
                        std::cout<<"Ingrese una unidad valida";
                        break;
                }
            }
            break;
        case 3:
            std::cout<<"Ingrese la matricula del alumno a buscar"<<std::endl;
            std::cin>>aux;
            aux1=buscarAlumno(aux);
            if (aux1==10){
                std::cout<<"El alumno no existe";
            }else{
            prom=(U1[aux1]+U2[aux1]+U3[aux1]+U4[aux1])/4;
            std::cout<<"el promedio del alumno es: "<<prom<<std::endl;
            }
            break;
        case 4:
            std::cout<<"Ingrese la unidad de la que quiere obtener el promedio"<<std::endl;
            std::cin>>aux1;
            if (aux1>4){
                std::cout<<"Ingrese una opcion valida";
            }else{
                 switch (aux1){
                    case 1:
                        prom=(U1[0]+U1[1]+U1[2]+U1[3]+U1[4])/5;
                        std::cout<<"el promedio de la unidad es: "<<prom<<std::endl;
                        break;
                    case 2:
                        prom=(U2[0]+U2[1]+U2[2]+U2[3]+U2[4])/5;
                        std::cout<<"el promedio de la unidad es: "<<prom<<std::endl;
                        break;
                    case 3:
                        prom=(U3[0]+U3[1]+U3[2]+U3[3]+U3[4])/5;
                        std::cout<<"el promedio de la unidad es: "<<prom<<std::endl;
                        break;
                    case 4:
                        prom=(U4[0]+U4[1]+U4[2]+U4[3]+U4[4])/5;
                        std::cout<<"el promedio de la unidad es: "<<prom<<std::endl;
                        break;
                    default:
                        std::cout<<"Ingrese una unidad valida";
                        break;
                }
            }
            break;
            
        case 0:
            std::cout<<"Saliendo..."<<std::endl;
            control=0;
            break;
        default:
            std::cout<<"Ingrese una opcion Valida"<<std::endl;
            break;
        }
    } while (control!=0);
}


int buscarAlumno(std::string matricula){
    int n=10;
    for (int i = 0; i < 5; i++){
        if (matricula==matriculas[i]){
            n=i;
        }
    }
    return n;
}