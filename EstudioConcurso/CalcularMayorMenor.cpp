#include <iostream>

typedef struct Nodo{
    int dato;
    Nodo *siguiente;
}Nodo;

void insertarLista(Nodo *&,int);
void mostrarLista(Nodo *);
void mayorMenor(Nodo *);
void eliminarDuplicados(Nodo *&);

int main(){
    Nodo *lista=nullptr;//creamos la lista inicializandola en null
    int dato, con=0;
    do{
        std::cout<<"1.- Insertar elemento a la lista 2.-Mostrar elementos"<<std::endl;
        std::cout<<"3.-Determinar mayor y menor elemento de la lista"<<std::endl;
        std::cout<<"4.-Eliminar Duplicados"<<std::endl;
        std::cout<<" 0.-Salir"<<std::endl;
        std::cout<<"Ingrese una opcion: "<<std::endl;
        std::cin>>con;
        std::cout<<std::endl;
        switch (con){
        case 1:
            std::cout<<"Ingrese un numero: "<<std::endl;
            std::cin>>dato;
            insertarLista(lista,dato);
            break;
        case 2: 
            mostrarLista(lista);
            break;
        case 3:
            mayorMenor(lista);
            break;
        case 4:
            eliminarDuplicados(lista);
            break;
        case 0:
            std::cout<<"Saliendo..."<<std::endl;
            break;
        default:
            std::cout<<"Ingrese una opcion valida"<<std::endl;
            break;
        }
    } while (con!=0);
    return 0;
}
void mostrarLista(Nodo *lista){
    Nodo *actual = new Nodo();//creamos un nodo auxiliar
    actual=lista;//lo inicializamos con la lista

    while (actual!=nullptr){//se basa en que el ultimo nodo de la lista simple apunta a null
        std::cout<<actual->dato<<"->";//mostramos el dato del nodo actual
        actual=actual->siguiente;//avanzamos al siguiente nodo
    }
    std::cout<<std::endl;
}

void insertarLista(Nodo *&lista,int n){//guarda los elementos en orden de insercion
    Nodo *nuevo_nodo= new Nodo();//creamos un nuevo nodo
    nuevo_nodo->dato=n;//asignamos el valor al nodo
    Nodo *aux=lista;
    Nodo *aux2;
    if (lista == nullptr){
        lista=nuevo_nodo;//insertamos al inicio de la lista si no entro en el while
    }else{
        while (aux->siguiente!=nullptr){
            aux=aux->siguiente;//avanzamos al siguiente nodo
        }
        aux->siguiente=nuevo_nodo;//insertamos al final de la lista
    }
    nuevo_nodo->siguiente=nullptr;//el nuevo nodo apunta a null ya que es el ultimo nodo
    std::cout<<"elemento "<<n<<" insertado a la lista correctamente"<<std::endl;
}

//insercion de nuevo elemento pero de manera recursiva
// void insertarRecursivamente(Nodo *lista, int n){
//     if (lista->siguiente==nullptr){
//         lista->siguiente= new Nodo();//se genera e inserta un nuevo nodo al final
//         lista->siguiente->dato=n;//asignamos valor
//         lista->siguiente->siguiente=nullptr;//ponemos a nulo para saber que es el ultimo
//     }else{
//         insertarRecursivamente(lista->siguiente,n);//si no fue el final se llama a si misma pero checando ahora el siguiente nodo
//     }
// }

void mayorMenor(Nodo *lista){
    if (lista!=nullptr){
        Nodo *aux=lista;//puntero auxiliar que apunta al primer elemento para poder recorrer la lista
        int mayor=aux->dato, menor=aux->dato;//arbitrariamente asumimos que el primero puede ser ambos
        while (aux!=nullptr){
            if (aux->dato>mayor){
                mayor=aux->dato;//si hay uno mayor, se actualiza
            }else if (aux->dato<menor){
                menor=aux->dato;//si hay uno menor se actualiza
            }
            aux=aux->siguiente;//avanzamos al siguiente elemento
        }
        std::cout<<"Mayor: "<<mayor<<std::endl;
        std::cout<<"Menor: "<<menor<<std::endl;
    }else{
        std::cout<<"La lista esta vacia"<<std::endl;
    }
          
}
//solo elimina la primera aparicion necesita mejora
void eliminarDuplicados(Nodo *&lista){
    Nodo *aux=lista;
    Nodo *nexts;
    if (lista==nullptr || lista->siguiente==nullptr){
        std::cout<<"No se puede eliminar porque la lista esta vacia o solo tiene un elemento"<<std::endl;
        return;
    }else{
        while (aux!=nullptr){
            Nodo *anterior = aux;
            nexts = aux->siguiente;
            while (nexts!=nullptr){
                if(aux->dato==nexts->dato){
                    Nodo *temp=nexts;
                    anterior->siguiente=nexts->siguiente;
                    nexts=nexts->siguiente;
                    delete temp;
                }else{
                    anterior=nexts;
                    nexts= nexts->siguiente;
                }   
            }
            aux=aux->siguiente;
        }
    }
}