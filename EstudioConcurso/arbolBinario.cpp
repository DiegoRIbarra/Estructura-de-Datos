#include <iostream>
//trabajo con arbol binario ABB -> Arbol Binario de Busqueda

typedef struct Nodo{
    int dato;
    Nodo *izq;
    Nodo *der;
    Nodo *padre;//para poder eliminar los nodos deben saber cual es su padre
} Nodo;


Nodo *crearNodo(int, Nodo *);
void insertarNodo(Nodo *&,int, Nodo *);
void mostrarArbol(Nodo *,int );
bool buscarNodo(Nodo *,int);
void preOrden(Nodo *);
void inOrden(Nodo *);
void postOrden(Nodo *);
void eliminar(Nodo *&, int);
void eliminarNodo(Nodo *&);
Nodo *minimo(Nodo *);//en los ABB es el mas a la izquierda
void reemplazar(Nodo *&, Nodo *);
void destruirNodo(Nodo *&);

Nodo *arbol=nullptr;//inicializamos el arbol como nulo
int main(){
    int con,dato,contador=0;
    do
    {
        std::cout<<"1.-Insertar un nodo al arbol 2.-Mostrar arbol completo"<<std::endl;
        std::cout<<"3.-Buscar nodo 4.-Recorrido en preOrden 5.-Recorrido en inOrden"<<std::endl;
        std::cout<<"6.-Recorrido en postOrden 7.-Eliminar Nodo del Arbol 0.-Salir"<<std::endl;
        std::cin>>con;
        switch (con)
        {
            case 1:
                std::cout<<"Ingrese el valor del nodo: ";
                std::cin>>dato;
                insertarNodo(arbol,dato,nullptr);
                break;
            case 2:
                std::cout<<"Arbol Completo: "<<std::endl<<std::endl;//damos dos saltos de linea para mejor vista
                mostrarArbol(arbol,contador);
                std::cout<<std::endl;//damos un salto de linea para mejor vista
                break;
            case 3:
                std::cout<<"Ingrese el valor a buscar en el arbol: ";
                std::cin>>dato;
                if (buscarNodo(arbol,dato)){
                    std::cout<<"El valor "<<dato<<" si se encuentra en el arbol"<<std::endl;
                }else{
                    std::cout<<"El valor "<<dato<<" no se encuentra en el arbol"<<std::endl;
                }
                break;
            case 4:
                std::cout<<"Recorrido en preOrden: ";
                preOrden(arbol);
                std::cout<<std::endl;
                break;
            case 5:
                std::cout<<"Recorrido en inOrden: ";
                inOrden(arbol);
                std::cout<<std::endl;
                break;
            case 6:
                std::cout<<"Recorrido en postOrden: ";
                postOrden(arbol);
                std::cout<<std::endl;
                break;
            case 7:
                std::cout<<"Ingrese el valor del nodo a eliminar: ";
                std::cin>>dato;
                eliminar(arbol,dato);
                break;
            case 0:
                std::cout<<"Saliendo..."<<std::endl;
                break;
            default:
                std::cout<<"Opcion no valida"<<std::endl;
                break;
        }
    } while (con!=0);
    return 0;
}

Nodo *crearNodo (int n, Nodo *padre){
    Nodo *nuevoNodo=new Nodo();//creamos nuevo nodo
    //asignamos los valores predeterminados
    nuevoNodo->dato=n;
    nuevoNodo->izq=nullptr;
    nuevoNodo->der=nullptr;
    nuevoNodo->padre=padre;
    return nuevoNodo;//retornamos el nodo creado
}

void insertarNodo(Nodo *&arbol,int n, Nodo *padre){
    if (arbol==nullptr){
        Nodo *nuevoNodo=crearNodo(n,padre);//si el arbol esta vacio, creamos un nuevo nodo y lo asignamos como raiz
        arbol=nuevoNodo;//asignamos el nuevo nodo a la raiz
    }else{//si no esta vacio es decir tiene uno o mas nodos
        int valorRaiz=arbol->dato;//obtenemos el valor del nodo raiz o del nodo actual
        if (n>valorRaiz){//comparamos el valor a insertar con el valor del nodo anterior ya sea raiz o no
            insertarNodo(arbol->der,n,arbol);//si es mayor va a la derecha por ser del tipo ABB
        }else{
            insertarNodo(arbol->izq,n,arbol);//si es menor va a la izquierda por ser tipo ABB
        }   
    }
}

void mostrarArbol(Nodo *arbol,int cont){
    if (arbol==nullptr){
        return;
    }else{
       
        mostrarArbol(arbol->der,cont+1);//recorremos el arbol empezando por la derecha
        for (int i = 0; i < cont; i++){
            std::cout<<"   ";//imprimimos espacios para darle una mejor vista
        }
        std::cout<<arbol->dato<<std::endl;//imprimimos el valor del nodo
        mostrarArbol(arbol->izq,cont+1);//recorremos el arbol ahora por la izquierda
    }
    
}

bool buscarNodo(Nodo *arbol,int n){
    if (arbol==nullptr){
        return false;
    }else if(arbol->dato==n){
        return true;
    }else if( n<arbol->dato){
        return buscarNodo(arbol->izq,n);
    }else{
        return buscarNodo(arbol->der,n);
    }
}
//recorrido en profundidad modo: preOrden raiz,izq,der
void preOrden(Nodo *arbol){
    if (arbol==nullptr){//si el arbolesta  vacio
        return;
    }else{
        std::cout<<arbol->dato<<" -  ";//imprimimos la raiz primero
        preOrden(arbol->izq);//despues imprimimos el subarbol izquierdo
        preOrden(arbol->der);//por ultimo imprimimos el subarbol derecho
    }
}

//recorrido en profundidad: inOrden izq,raiz,der
void inOrden(Nodo *arbol){
    if (arbol==nullptr){
        return; 
    }else{
        inOrden(arbol->izq);
        std::cout<<arbol->dato<<" -  ";
        inOrden(arbol->der);
    }
    
}

//recorrido en profundidad modo: postOrden izq,der,raiz
void postOrden(Nodo *arbol){
    if (arbol==nullptr){
        return;
    }else{
        postOrden(arbol->izq);
        postOrden(arbol->der);
        std::cout<<arbol->dato<<" -  ";
    }
}

void eliminar(Nodo *&arbol, int n){
    if (arbol==nullptr){
        return;
    }else if(n<arbol->dato){
        eliminar(arbol->izq,n);
    }else if (n>arbol->dato){
        eliminar(arbol->der,n);
    }else if (n==arbol->dato){
        eliminarNodo(arbol);
    }
}

Nodo *minimo(Nodo *arbol){
    if (arbol==nullptr){
        return nullptr;
    }else if (arbol->izq!=nullptr){
        return minimo(arbol->izq);
    }else{
        return arbol;
    }
}

void reemplazar(Nodo *&arbol, Nodo *nuevoNodo){
    if (arbol->padre!=nullptr){
        if (arbol->dato==arbol->padre->izq->dato){
            arbol->padre->izq=nuevoNodo;
        }else if(arbol->dato==arbol->padre->der->dato){
            arbol->padre->der=nuevoNodo;
        }
        
    }
    if (nuevoNodo){
        nuevoNodo->padre=arbol->padre;
    }
}


void destruirNodo (Nodo *&nodoDestruir){
    nodoDestruir->izq=nullptr;
    nodoDestruir->der=nullptr;
    delete nodoDestruir;
    nodoDestruir=nullptr;
}

void eliminarNodo(Nodo *&nodoEliminar){
    if (nodoEliminar->der!=nullptr && nodoEliminar->izq!=nullptr){
        //eliminacion con dos hijos
        Nodo *menor= minimo(nodoEliminar->der);
        nodoEliminar->dato=menor->dato;
        eliminarNodo(menor);
    }else if (nodoEliminar->izq!=nullptr){
        //eliminacion con un hijo en este caso el hijo izquierdo
        reemplazar(nodoEliminar,nodoEliminar->izq);
        destruirNodo(nodoEliminar);
    }else if(nodoEliminar->der!=nullptr){
        //eliminacion con un hijo en este caso el hijo derecho
        reemplazar(nodoEliminar,nodoEliminar->der);
        destruirNodo(nodoEliminar);
    }else{
        reemplazar(nodoEliminar, nullptr);
        destruirNodo(nodoEliminar);
    }
    
}