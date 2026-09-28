//funcion para verificar si la cadena esta balanceada
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

bool verificacion(std::string cadena){
    std::stack<char> pila;
    for (auto i = cadena.begin(); i !=cadena.end(); i++){
        if (*i=='{'||*i=='['||*i=='('){
            pila.push(*i);
        }
        if (*i==')'||*i==']'||*i=='}'){
            if (pila.empty()){
                return false;//no esta balanceada ya que no hay apertura
            }
            char top= pila.top();//se obtiene el tope de la pila
            //se verifica si el tope y el caracter actual son del mismo tipo
            if ((*i==')' && top=='(') || (*i==']' && top=='[') || (*i=='}' && top=='{')){
                //si son del mismo tipo esta balanceada
                pila.pop();//se elimina el tope de la pila
            }else{
                return false;//no estan balanceadas 
            }
        }
    }
     if (pila.empty()){
            return true;//esta balanceada
        }else{
            return false;//no esta balanceada
        }
}

string longestPalindrome(string s) {
    if(s.empty()){
        return "";
    }else{
        int inicio=0;
        int fin=0;
        for (int i=0; i!=s.length(); i++){
             // Caso impar: centro en i
            int len1 = expandirDesdeCentro(s, i, i);
            // Caso par: centro entre i e i+1
            int len2 = expandirDesdeCentro(s, i, i + 1);
            //se evalua la longitud maxima del palindromo
            int lenMax = max(len1, len2);//max es una funcion que devuelve el mayor de dos valores
            if (lenMax > fin-inicio){//se evalua si la longitud maxima es mayor a 0
                inicio = i - (lenMax - 1) / 2; //calculo del indice de inicio del palindromo
                fin = i + lenMax / 2; //calculo del indice final del palindromo se divide entre dos para poder obtener la mitad de la longitud del palindromo para restarla o sumarla al indice central
            }
        }
         return s.substr(inicio, fin - inicio + 1); //se devuelve la subcadena que es el palindromo mas largo encontrado
        
    }
}

int expandirDesdeCentro(const string s,int izquierda, int derecha){
    while(izquierda>=0&& derecha<s.length()&& s[izquierda]==s[derecha]){
        izquierda--;
        derecha++;
    }
    return derecha-izquierda-1; //es menos 1 porque la iteracion final le agrega 1 de mas a derecha y le quita 1 de mas a izquierda 
}

