#include <iostream>
int buscarDuplicidad(int a[], int s, int n);
void mostArr(int a[], int s);

int main(){
    int *ptr_a;
    int tam=4;
    int *ptr_aux=nullptr;
    ptr_a=nullptr;
    int cont=0,num=0,i=0;
    tam=1;
    ptr_a=new int[tam];
    do{
        std::cout<<"ingrese un numero";
        std::cin>>num;
        if (buscarDuplicidad(ptr_a,i,num)>0){
            std::cout<<"no se pueden ingresar numeros duplicados";
            i--;
            tam--;
        }else{
            if (i==0){
                ptr_a[i]=num;
            }else{
                ptr_aux=new int[tam];
                bool cent=false;
                for (int j = 0, k=0; j < tam-1; j++, k++){
                    if (num<ptr_a[j]){
                        ptr_aux[k]=num;
                        k++;
                        cent=true;
                    }
                    ptr_aux[k]=ptr_a[j];
                }
                if (!cent){
                    ptr_aux[tam-1]=num;
                }
                delete[] ptr_a;
                ptr_a=ptr_aux;
                ptr_aux=nullptr;
            }

        }
        std::cout<<"quiere ingresar otro numero 1.-si 0.-no";
        std::cin>>cont;
        if (cont==1){
            i++;
            tam++;
        }
    } while (cont!=0);
    mostArr(ptr_a,tam);
    

    delete[] ptr_a;
    ptr_a=nullptr;

    

}

int buscarDuplicidad(int a[], int s, int n){
    for (int i = 0; i <s; i++){
        if (a[i]==n){
            return 1;
        }
    }
    return -1;
}

void mostArr(int a[], int s){
     for (int i = 0; i < s; i++){
        std::cout<<a[i]<<std::endl;
    }
}