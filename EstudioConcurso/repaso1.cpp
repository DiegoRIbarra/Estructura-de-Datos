#include <iostream>
//repasare listas enlazadas simples

typedef struct Nodo{
    int dato;
    Nodo *siguiente;
}Nodo;

void insertarLista(Nodo *&,int);
void mostrarLista(Nodo *);
void buscarLista(Nodo *,int);
void eliminarNodo(Nodo *&,int);
void vaciarlista(Nodo *&);
void invertirlista(Nodo *&);
int main(){
    //insertar elementos en una lista enlazada
    Nodo *lista=nullptr;//se crea la lista enlazada 
    int dato, con=0;
    do{
        //menu con las principales operaciones de una lista simplemente enlazada
        std::cout<<"1.- Insertar elemento a la lista 2.-Mostrar elementos"<<std::endl;
        std::cout<<"3.-Buscar elemento en la lista 4.-Eliminar elemento de la lista"<<std::endl;
        std::cout<<"5.- Vaciar lista 6.-Invertir lista  0.-Salir"<<std::endl;
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
            std::cout<<"Ingrese un numero a buscar: "<<std::endl;
            std::cin>>dato;
            buscarLista(lista,dato);
            break;
        case 4: 
            std::cout<<"Ingrese un numero de la lista a eliminar: "<<std::endl;
            std::cin>>dato;
            eliminarNodo(lista,dato);
            break;
        case 5:
            vaciarlista(lista);
            break;
        case 6:
            invertirlista(lista);
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

void insertarLista(Nodo *&lista,int n){//se insertan en orden ascendente
    Nodo *nuevo_nodo= new Nodo();//creamos un nuevo nodo
    nuevo_nodo->dato=n;//asignamos el valor al nodo
    Nodo *aux1=lista;
    Nodo *aux2;

    while (aux1!=nullptr && aux1->dato<n){
        aux2=aux1;//guardamos la posicion anterior
        aux1=aux1->siguiente;//avanzamos al siguiente nodo
    }

    if (lista == aux1){
        lista=nuevo_nodo;//insertamos al inicio de la lista si no entro en el while
    }else{
        aux2->siguiente=nuevo_nodo;//insertamos en medio o al final de la lista
    }
    nuevo_nodo->siguiente=aux1;//enlazamos el nuevo nodo con el siguiente

    std::cout<<"elemento "<<n<<" insertado a la lista correctamente"<<std::endl;
}

void buscarLista(Nodo *lista, int n){
    Nodo *actual=new Nodo();//creamos un nodo auxiliar
    int pos=0;
    bool band=false;//bandera para saber si se encontro el elemento
    actual=lista;//hacemos que actual apunte al inicio de la lista (primer elemento esto es siempre)
    while (actual!=nullptr && actual->dato<=n){//mientras el puntero no de null(fin lista) y nuestro dato sea menos o igual al dato a buscar
        if (actual->dato==n){//si encontramos el elemento
            band=true;//cambiamos la bandera
            exit;
        }
        actual=actual->siguiente;//avanzamos al siguiente nodo
        pos++;//aumentamos la posicion para saber en que posicion esta el elemento
    }
    if (band){
        std::cout<<"Elemento "<<n<<"si se encontro en la lista"<<std::endl;
        std::cout<<"Posicion: "<<pos<<std::endl;
    }else{
        std::cout<<"Elemento "<<n<<"no se encontro en la lista"<<std::endl;
    }
}
//busqueda recursiva
// bool buscarLista(Nodo *lista, int n){
//     if (lista!=nullptr){
//         if (lista->dato==n){
//             return true;
//         }else{
//             buscarLista(lista->siguiente,n);//llamada recursiva al siguiente nodo
//         }
//     }else{
//         return false;
//     }
// }
void eliminarNodo(Nodo *&lista,int n){
    if (lista!=nullptr){
        Nodo *aux_borrar;//nodo auxiliar para recorrer la lista
        Nodo *anterior=nullptr;//nodo anterior para guardar la posicion anterior al nodo a eliminar
        aux_borrar=lista;//hacemos que el nodo auxiliar apunte al inicio de la lista
        while (aux_borrar!=nullptr && aux_borrar->dato!=n){
            anterior=aux_borrar;//guardamos la posicion anterior
            aux_borrar=aux_borrar->siguiente;//avanzamos al siguiente nodo
        }
        if (aux_borrar==nullptr){//se recorrio toda la lista y nunca lo encontro
            std::cout<<"El elemento no existe en la lista"<<std::endl;
        }else if (anterior==nullptr){//el elemento a eliminar es el primer elemento
            lista=lista->siguiente;
            delete aux_borrar;
            std::cout<<"Elemento "<<n<<" eliminado de la lista"<<std::endl;
        }else{
            anterior->siguiente=aux_borrar->siguiente;//saltamos el nodo en el que se quedo anterior y lo enlazamos con el siguiente del nodo ya que es el que se quiere eliminar
            delete aux_borrar;//eliminamos el nodo
            std::cout<<"Elemento "<<n<<" eliminado de la lista"<<std::endl;
        }
    }else{
        std::cout<<"La lista esta vacia, no se puede eliminar ningun elemento"<<std::endl;
    }
}

void vaciarlista(Nodo *&lista){
    if (lista!=nullptr){
        Nodo *aux=lista;//nodo auxiliar para recorrer la lista
        while (aux!=nullptr){
            Nodo *temp=aux;//nodo temporal en el que se va guardando el nodo actual y se elimina
            aux=aux->siguiente;//avanzamos al siguiente nodo
            delete temp;//eliminamos el nodo actual guardado en temp
        }
        delete aux;//eliminamos el nodo auxiliar
        lista=nullptr;//hacemos que la lista apunte a null ya que esta vacia
        std::cout<<"Lista vaciada correctamente"<<std::endl;
    }else{
        std::cout<<"La lista ya esta vacia"<<std::endl;
    }   
}

void invertirlista(Nodo *&lista){
    //se invierte la lista con enfoque iterativo (3 punteros) para poder hacerlo con n elementos
   if (lista!=nullptr){//verificamos que la lista no este vacia si no lo esta procedemos a invertirla
     Nodo *prev=nullptr;//representara el nodo anterior al actual
     Nodo *act=lista;//nodo auxiliar para poder recorrer la lista (apunta al primer elemento)
     Nodo *next;//se usa para almacenar el proximo nodo antes de modificar ese puntero
     while (act!=nullptr){
         next=act->siguiente;//se guarda el siguiente nodo
         next:act->siguiente=prev;//invertimos el puntero
         // el operador : asigna la etiqueta next al operador invertido
         prev=act;//movemos los punteros
         act=next;//movemos los punteros
     }
     delete[] lista;//vaciamos la lista actual
     lista=prev;//la igualamos con la lista invertida prev es el ultimo nodo de la lista actual
     //pero como esta invertida ahora es el primer elemento
   }
   
}