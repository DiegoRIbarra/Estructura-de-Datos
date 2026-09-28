#include <iostream>

void fun_m(int w[][2],int s);

int main(){
    int matriz[2][2]={{1,2},{3,4}};
    fun_m(matriz,2);
    return 0;
}
void fun_m(int w[][2],int s){
    for(int i=0;i<s;i++){
        for(int j=0;j<2;j++){
            std::cout<<w[i][j]<< std::endl;
        }
    }
}