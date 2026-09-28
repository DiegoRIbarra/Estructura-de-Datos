#include <iostream>
int main(){
    int a;
    int *l;
    l=new int[5];
    int z[3]={1,2,3};
    int b=2;
    int *ptr_a=nullptr;
    int *ptr_b=z;
    std::cout<<ptr_b<<std::endl;
    std::cout<<&z<<std::endl;
    if(ptr_a == nullptr){
        std::cout<<"es nulo"<<std::endl;
    }else{
        std::cout<<"no es nulo"<<std::endl;
    }

    for(int j=0;j<5;j++){
        l[j]=j+1;
    }

    for(int j=0;j<5;j++){
        std::cout<<l[j]<< std::endl;
    }
    ptr_a=&a;
    *(ptr_a)=5;
    std::cout<<ptr_a<<std::endl;
    std::cout<<a<<std::endl;
    std::cout<<&a<<std::endl;
    std::cout<<*ptr_a<<std::endl;
    std::cout<<&ptr_a<<std::endl;
    return 0;
}