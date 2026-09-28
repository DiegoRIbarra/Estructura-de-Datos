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

//    for (int i = 0; i < tam; i++){
//        std::cout << ptr_a[i] << std::endl;
//    }
//    std::cout<<"se redimensiona el array"<<std::endl;
//    tam=6;

//    ptr_aux= new int[tam];
//     for (int i = 0; i < 2; i++){
//         ptr_aux[i]=ptr_a[i];
//     }
//    delete[] ptr_a;
//    ptr_a=ptr_aux;
//    ptr_aux=nullptr;


   
//     for (int i = 0; i < tam; i++){
//        std::cout << ptr_a[i] << std::endl;
//    }


    //disminuimos el array
     //se crea un nuevo array con tam-1
   

    ptr_aux=new int[--tam];
    //copiamos los elementos del viejo array al nuevo
    for (int i = 0; i < tam; i++){
        ptr_aux[i]=ptr_a[i];
    }
    //se limpia memoria y reacomoda el array con los valores y nuevo tamaño  en ptr_a
    delete[] ptr_a;
    ptr_a=ptr_aux;
    ptr_aux=nullptr;

    return 0;
}