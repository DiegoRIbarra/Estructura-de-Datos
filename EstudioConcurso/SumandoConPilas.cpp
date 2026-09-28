#include <iostream>
#include <set>
#include <stack>
#include <queue>
#include <vector>

//suma de pilas->
// int main(){
//     int t, num,suma=0;
//     std::string orden;
//     std::cin>>t;
//     std::stack<int> pila;
//     for (int i = 1; i <=t; i++){
//         std::cin>>orden;
//         if (orden=="AGREGA"){
//             std::cin>>num;
//             pila.push(num);
//         }else if(orden=="CONSUME"){
//              suma+=pila.top();
//              pila.pop();
//              suma+=pila.top();
//              pila.pop();
//              pila.push(suma);
//              suma=0;
//         }else if(orden=="IMPRIME"){
//             std::cout<<pila.top()<<std::endl;
//         }

//    } 
// }

//Round Robin
// typedef struct tarea{
//     int id;
//     int time;
// }tarea;

// int main(){
    
//     std::queue<tarea> cola;
//     int t,tmp,id,time;
//     tarea aux;
//     std::cin>>t>>tmp;
    
//     while (t--){
//         std::cin>>id>>time;
//         cola.push({id, time});
//     }    

//     while (!cola.empty()){
//         aux=cola.front();
//         if (aux.time>tmp){
//             aux.time-=tmp;
//             cola.pop();
//             cola.push(aux);
//         }else{
//             std::cout<<aux.id<<std::endl;
//             cola.pop();
//         }
//     }    
// }

//el problema de los tacos
// int main(){
//     std::queue<int> cola;
//     int t, num,op,sum=0;
//     std::cin>>t;
//     for (int i = 1; i <=t; i++){
//         std::cin>>op;
//         switch(op){
//             case 1:
//                 std::cin>>num;
//                 cola.push(num);
//                 break;
//             case 2:
//                 if (!cola.empty()){
//                     sum+=cola.front();
//                     cola.pop();
//                 }
//                 break;
//             case 3:
//                 std::cout<<cola.size()<<std::endl;
//                 break;
//             case 4:
//                 std::cout<<sum<<std::endl;
//                 break; 
//         }    
//     }
// }

//Buscando una estrella
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::multiset<long long> participantes;
    int t;
    long long punt;
    char op;
    std::cin>>t;
    for (int i = 0; i < t; i++){
        std::cin>>op;
        switch (op){
        case 'R':
            std::cin>>punt;
            participantes.insert(punt);
            break;
        case 'S':
            if (participantes.size()<3){
                std::cout<<"NO HAY SUFICIENTES PUNTAJES"<<"\n";
            }else{
                auto it= participantes.begin();
                std::cout << *it << " ";
                    ++it;
                    std::cout << *it << " ";
                    ++it;
                    std::cout << *it << "\n";
                
            }
            break;
        case 'B':
            if (!participantes.empty()){
                participantes.erase(participantes.begin());
                break;
            }
            
        }
    }
    if (participantes.empty()){
        std::cout<<"NO HUBO GANADOR"<<std::endl;
    }else{
        std::cout<<"EL PUNTAJE MAS ALTO FUE "<<*participantes.rbegin()<<"\n";
    }
}

//version con map
// #include <iostream>
// #include <map>

// int main() {
//     std::ios_base::sync_with_stdio(false);
//     std::cin.tie(NULL);

//     std::map<long long, int> participantes;
//     int t;
//     long long punt;
//     char op;
//     int total_participantes = 0; 

//     std::cin >> t;
//     while (t--) {
//         std::cin >> op;
//         switch (op) {
//             case 'R':
//                 std::cin >> punt;
//                 participantes[punt]++;
//                 total_participantes++; 
//                 break;
//             case 'S':
//                 if (total_participantes < 3) {
//                     std::cout << "NO HAY SUFICIENTES PUNTAJES" << "\n";
//                 } else {
//                     auto it = participantes.begin();
//                     int impresos = 0;
//                     while (impresos < 3) {
//                         for (int i = 0; i < it->second && impresos < 3; ++i) {
//                             std::cout << it->first << (impresos == 2 ? "" : " ");
//                             impresos++;
//                         }
//                         ++it;
//                     }
//                     std::cout << "\n";
//                 }
//                 break;
//             case 'B':
//                 if (!participantes.empty()) {
//                     auto it = participantes.begin();
//                     it->second--; 
//                     total_participantes--; 
//                     if (it->second == 0) {
//                         participantes.erase(it);
//                     }
//                 }
//                 break;
//         }
//     }

//     if (participantes.empty()) {
//         std::cout << "NO HUBO GANADOR" << "\n";
//     } else {
//         std::cout << "EL PUNTAJE MAS ALTO FUE " << participantes.rbegin()->first ;
//     }
//     return 0;
// }

//Problema numeros de telefono y asistente ocupada susana distancias
// int main(){
//     std::cin.tie(nullptr);
//     std::ios_base::sync_with_stdio(false);
//     std::stack<long long> pila_papelitos;
//     std::vector<int> minutos;
//     std::vector<int> telefonos;
//     int t;
//     long long num;
//     std::cin>>t;
//     for (int i = 0; i < t; i++) {
//         std::cin>>num;
//         minutos.push_back(num);
//     }
//     for (int i = 0; i < t; i++) {
//         std::cin>>num;
//         telefonos.push_back(num);
//     }
//     int minuto_libre = 1;
//     int duraciones_usadas = 0;    
//     int telefonos_colocados = 0; 

//     for (int minuto=1; telefonos_colocados<t||!pila_papelitos.empty(); minuto++){
//         if (telefonos_colocados<t){
//             pila_papelitos.push(telefonos[telefonos_colocados]);
//             telefonos_colocados++;
//         }
//         if (minuto>=minuto_libre && !pila_papelitos.empty()){
//             std::cout<<pila_papelitos.top()<<"\n";
//             pila_papelitos.pop();
//             minuto_libre=minuto+minutos[duraciones_usadas];
//             duraciones_usadas++;
//         }
//     }
// }


 

