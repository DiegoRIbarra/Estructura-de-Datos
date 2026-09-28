//forma recursivas
#include <iostream>
typedef struct Nodo{
    int dato;
    Nodo *siguiente;
}Nodo;

bool buscarLista(Nodo *,int);
void insertarRecursivamente(Nodo *, int n);
int main(){
    Nodo *lista=nullptr;

    int op,n;
    do{
        std::cout<<"1.-Agregar Nodo 2.-Eliminar Nodo 3.-Eliminar Ultimo Nodo"<<"\n";
        std::cout<<"4.-Buscar Nodo  0.-Salir"<<"\n";
        std::cout<<"Ingresa una opcion: ";
        std::cin>>op;
        switch (op)
        {
        case 1:
            std::cout<<"Ingrese un elemento a insertar: ";
            std::cin>>n;
            insertarRecursivamente(lista,n);
            
            
            break;
        case 4: 
            std::cout<<"Ingrese un elemento a buscar: ";
            std::cin>>n;
            if (buscarLista(lista,n)){
                std::cout<<"elemento encontrado"<<"\n";
            }else{
                std::cout<<"El elemento no esta en la lista"<<"\n";
            }
            break;
        default:
            break;
        }
    } while (op!=0);
    
}
// void insertarRecursivamente(Nodo *lista, int n){
//     if (lista->siguiente==nullptr){
//         lista->siguiente= new Nodo();//se genera e inserta un nuevo nodo al final
//         lista->siguiente->dato=n;//asignamos valor
//         lista->siguiente->siguiente=nullptr;//ponemos a nulo para saber que es el ultimo
//     }else{
//         insertarRecursivamente(lista->siguiente,n);//si no fue el final se llama a si misma pero checando ahora el siguiente nodo
//     }
// }

bool buscarLista(Nodo *lista, int n){
    if (lista!=nullptr){
        if (lista->dato==n){
            return true;
        }else{
            buscarLista(lista->siguiente,n);//llamada recursiva al siguiente nodo
        }
    }else{
        return false;
    }
}
