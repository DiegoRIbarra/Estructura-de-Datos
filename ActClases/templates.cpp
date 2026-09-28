#include <iostream>
#include <string>
#include <vector>

//part tres:
// template <typename K,typename V>

// class Par{
//     public: 
//         K clave;
//         V valor;

//         Par(K c, V v): clave(c), valor(v) {}

//         void mostrar(){
//             std::cout<<"Clave: "<<clave<<" Valor: "<<valor<<"\n";
//         }
// };

//part uno:

// int main(){
//     //lo hacemos con int
//     Par<int, int>constructor1(34,56);
//     constructor1.mostrar();

//     //string
//     Par<std::string, std::string>constructor2("Arturo", "femboy");
//     constructor2.mostrar();

//     //tipos de datos combinados
//     Par<int, std::string>constructor3(2430069, "femboy");
//     constructor3.mostrar();

// }

//parte dos:

// template <typename T>
// T encontrarMaximo(T a, T b){
//     return (a>b) ? a : b;
// }

// int main(){
//     //primero enteros
//     int num1=25;
//     int num2=50;
//     std::cout<<"El mayor de los int es: "<<encontrarMaximo(num1, num2)<<"\n";

//     //ahora con los float
//     float f1=34.5;
//     float f2=59;
//     std::cout<<"El mayor de los float es: "<<encontrarMaximo(f1, f2)<<"\n";

//     //se prueba con los string 
//     std::string palabra1="Hola";
//     std::string palabra2="Parangaricutimiricuaro";
//     std::cout<<"La palabra mas grande? es : "<<encontrarMaximo(palabra1, palabra2)<<"\n";
//     return 0;
// }


//parte cuatro

