/*
 * ÁRBOL AVL - Árbol Binario de Búsqueda Auto-Balanceado
 * 
 * ¿QUÉ ES UN ÁRBOL AVL?
 * Es un árbol binario de búsqueda (BST) que se mantiene balanceado
 * automáticamente. Fue inventado por Adelson-Velsky y Landis en 1962.
 * 
 * PROPIEDAD AVL:
 * Para cada nodo, la diferencia de alturas entre su subárbol izquierdo
 * y derecho (factor de balance) es -1, 0 o 1.
 * 
 * Factor de Balance = altura(izquierdo) - altura(derecho)
 * 
 * ROTACIONES:
 * Cuando se viola la propiedad AVL, se aplican rotaciones:
 * - Rotación Simple Derecha (LL)
 * - Rotación Simple Izquierda (RR)
 * - Rotación Doble Izquierda-Derecha (LR)
 * - Rotación Doble Derecha-Izquierda (RL)
 * 
 * COMPLEJIDAD:
 * - Inserción: O(log n)
 * - Eliminación: O(log n)
 * - Búsqueda: O(log n)
 */

#include <iostream>
#include <queue>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

// Estructura del nodo AVL
struct NodoAVL {
    int dato;
    int altura;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    
    NodoAVL(int valor) {
        dato = valor;
        altura = 1;
        izquierdo = nullptr;
        derecho = nullptr;
    }
};

class ArbolAVL {
private:
    NodoAVL* raiz;
    
    // Obtener altura de un nodo
    int obtenerAltura(NodoAVL* nodo) {
        if (nodo == nullptr) return 0;
        return nodo->altura;
    }
    
    // Calcular factor de balance
    int obtenerBalance(NodoAVL* nodo) {
        if (nodo == nullptr) return 0;
        return obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho);
    }
    
    // Actualizar altura de un nodo
    void actualizarAltura(NodoAVL* nodo) {
        nodo->altura = 1 + max(obtenerAltura(nodo->izquierdo), 
                               obtenerAltura(nodo->derecho));
    }
    
    /*
     * ROTACIÓN SIMPLE DERECHA (LL)
     * Se aplica cuando el desbalance está en el subárbol izquierdo del hijo izquierdo
     * 
     *       z                y
     *      / \             /   \
     *     y   T4   -->    x     z
     *    / \             / \   / \
     *   x   T3          T1 T2 T3 T4
     *  / \
     * T1  T2
     */
    NodoAVL* rotacionDerecha(NodoAVL* z) {
        cout << "  >> Rotación DERECHA en nodo " << z->dato << endl;
        
        NodoAVL* y = z->izquierdo;
        NodoAVL* T3 = y->derecho;
        
        // Realizar rotación
        y->derecho = z;
        z->izquierdo = T3;
        
        // Actualizar alturas
        actualizarAltura(z);
        actualizarAltura(y);
        
        return y;
    }
    
    /*
     * ROTACIÓN SIMPLE IZQUIERDA (RR)
     * Se aplica cuando el desbalance está en el subárbol derecho del hijo derecho
     * 
     *     z                    y
     *    / \                 /   \
     *   T1  y      -->      z     x
     *      / \             / \   / \
     *     T2  x           T1 T2 T3 T4
     *        / \
     *       T3  T4
     */
    NodoAVL* rotacionIzquierda(NodoAVL* z) {
        cout << "  >> Rotación IZQUIERDA en nodo " << z->dato << endl;
        
        NodoAVL* y = z->derecho;
        NodoAVL* T2 = y->izquierdo;
        
        // Realizar rotación
        y->izquierdo = z;
        z->derecho = T2;
        
        // Actualizar alturas
        actualizarAltura(z);
        actualizarAltura(y);
        
        return y;
    }
    
    // Insertar nodo recursivamente
    NodoAVL* insertar(NodoAVL* nodo, int dato) {
        // 1. Inserción normal de BST
        if (nodo == nullptr) {
            cout << "  Insertando " << dato << endl;
            return new NodoAVL(dato);
        }
        
        if (dato < nodo->dato) {
            nodo->izquierdo = insertar(nodo->izquierdo, dato);
        } else if (dato > nodo->dato) {
            nodo->derecho = insertar(nodo->derecho, dato);
        } else {
            cout << "  El valor " << dato << " ya existe" << endl;
            return nodo;  // No se permiten duplicados
        }
        
        // 2. Actualizar altura
        actualizarAltura(nodo);
        
        // 3. Obtener factor de balance
        int balance = obtenerBalance(nodo);
        
        cout << "  Nodo " << nodo->dato << ": balance = " << balance << endl;
        
        // 4. Si está desbalanceado, aplicar rotaciones
        
        // Caso LL: Desbalance izquierda-izquierda
        if (balance > 1 && dato < nodo->izquierdo->dato) {
            cout << "  Caso LL detectado" << endl;
            return rotacionDerecha(nodo);
        }
        
        // Caso RR: Desbalance derecha-derecha
        if (balance < -1 && dato > nodo->derecho->dato) {
            cout << "  Caso RR detectado" << endl;
            return rotacionIzquierda(nodo);
        }
        
        // Caso LR: Desbalance izquierda-derecha
        if (balance > 1 && dato > nodo->izquierdo->dato) {
            cout << "  Caso LR detectado" << endl;
            nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
            return rotacionDerecha(nodo);
        }
        
        // Caso RL: Desbalance derecha-izquierda
        if (balance < -1 && dato < nodo->derecho->dato) {
            cout << "  Caso RL detectado" << endl;
            nodo->derecho = rotacionDerecha(nodo->derecho);
            return rotacionIzquierda(nodo);
        }
        
        return nodo;
    }
    
    // Encontrar el nodo con valor mínimo
    NodoAVL* encontrarMinimo(NodoAVL* nodo) {
        NodoAVL* actual = nodo;
        while (actual->izquierdo != nullptr)
            actual = actual->izquierdo;
        return actual;
    }
    
    // Eliminar nodo recursivamente
    NodoAVL* eliminar(NodoAVL* nodo, int dato) {
        // 1. Eliminación normal de BST
        if (nodo == nullptr) {
            cout << "  Valor " << dato << " no encontrado" << endl;
            return nodo;
        }
        
        if (dato < nodo->dato) {
            nodo->izquierdo = eliminar(nodo->izquierdo, dato);
        } else if (dato > nodo->dato) {
            nodo->derecho = eliminar(nodo->derecho, dato);
        } else {
            // Nodo encontrado
            cout << "  Eliminando " << dato << endl;
            
            // Caso 1 y 2: Nodo con un hijo o sin hijos
            if (nodo->izquierdo == nullptr || nodo->derecho == nullptr) {
                NodoAVL* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;
                
                if (temp == nullptr) {
                    // Sin hijos
                    temp = nodo;
                    nodo = nullptr;
                } else {
                    // Un hijo
                    *nodo = *temp;
                }
                delete temp;
            } else {
                // Caso 3: Dos hijos
                NodoAVL* temp = encontrarMinimo(nodo->derecho);
                nodo->dato = temp->dato;
                nodo->derecho = eliminar(nodo->derecho, temp->dato);
            }
        }
        
        if (nodo == nullptr) return nodo;
        
        // 2. Actualizar altura
        actualizarAltura(nodo);
        
        // 3. Obtener factor de balance
        int balance = obtenerBalance(nodo);
        
        cout << "  Nodo " << nodo->dato << ": balance = " << balance << endl;
        
        // 4. Rebalancear si es necesario
        
        // Caso LL
        if (balance > 1 && obtenerBalance(nodo->izquierdo) >= 0) {
            cout << "  Caso LL detectado" << endl;
            return rotacionDerecha(nodo);
        }
        
        // Caso LR
        if (balance > 1 && obtenerBalance(nodo->izquierdo) < 0) {
            cout << "  Caso LR detectado" << endl;
            nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
            return rotacionDerecha(nodo);
        }
        
        // Caso RR
        if (balance < -1 && obtenerBalance(nodo->derecho) <= 0) {
            cout << "  Caso RR detectado" << endl;
            return rotacionIzquierda(nodo);
        }
        
        // Caso RL
        if (balance < -1 && obtenerBalance(nodo->derecho) > 0) {
            cout << "  Caso RL detectado" << endl;
            nodo->derecho = rotacionDerecha(nodo->derecho);
            return rotacionIzquierda(nodo);
        }
        
        return nodo;
    }
    
    // Buscar nodo
    bool buscar(NodoAVL* nodo, int dato) {
        if (nodo == nullptr) return false;
        
        if (dato == nodo->dato) return true;
        else if (dato < nodo->dato) return buscar(nodo->izquierdo, dato);
        else return buscar(nodo->derecho, dato);
    }
    
    // Recorrido InOrden
    void inOrden(NodoAVL* nodo) {
        if (nodo != nullptr) {
            inOrden(nodo->izquierdo);
            cout << nodo->dato << " ";
            inOrden(nodo->derecho);
        }
    }
    
    // Recorrido PreOrden
    void preOrden(NodoAVL* nodo) {
        if (nodo != nullptr) {
            cout << nodo->dato << " ";
            preOrden(nodo->izquierdo);
            preOrden(nodo->derecho);
        }
    }
    
    // Recorrido PostOrden
    void postOrden(NodoAVL* nodo) {
        if (nodo != nullptr) {
            postOrden(nodo->izquierdo);
            postOrden(nodo->derecho);
            cout << nodo->dato << " ";
        }
    }
    
    // Recorrido por niveles (BFS)
    void porNiveles() {
        if (raiz == nullptr) return;
        
        queue<NodoAVL*> cola;
        cola.push(raiz);
        
        while (!cola.empty()) {
            NodoAVL* actual = cola.front();
            cola.pop();
            cout << actual->dato << " ";
            
            if (actual->izquierdo != nullptr)
                cola.push(actual->izquierdo);
            if (actual->derecho != nullptr)
                cola.push(actual->derecho);
        }
    }
    
    // Imprimir árbol visual
    void imprimirArbol(NodoAVL* nodo, string prefijo = "", bool esIzquierdo = true) {
        if (nodo == nullptr) return;
        
        cout << prefijo;
        cout << (esIzquierdo ? "├──" : "└──");
        
        // Imprimir nodo con su balance
        int bal = obtenerBalance(nodo);
        cout << nodo->dato << " (h:" << nodo->altura << ", b:" << bal << ")" << endl;
        
        // Imprimir hijos
        if (nodo->izquierdo != nullptr || nodo->derecho != nullptr) {
            if (nodo->izquierdo)
                imprimirArbol(nodo->izquierdo, prefijo + (esIzquierdo ? "│   " : "    "), true);
            else
                cout << prefijo + (esIzquierdo ? "│   " : "    ") + "├──(null)" << endl;
            
            if (nodo->derecho)
                imprimirArbol(nodo->derecho, prefijo + (esIzquierdo ? "│   " : "    "), false);
            else
                cout << prefijo + (esIzquierdo ? "│   " : "    ") + "└──(null)" << endl;
        }
    }
    
    // Liberar memoria
    void destruir(NodoAVL* nodo) {
        if (nodo != nullptr) {
            destruir(nodo->izquierdo);
            destruir(nodo->derecho);
            delete nodo;
        }
    }

public:
    ArbolAVL() : raiz(nullptr) {}
    
    ~ArbolAVL() {
        destruir(raiz);
    }
    
    void insertar(int dato) {
        cout << "\n--- Insertando " << dato << " ---" << endl;
        raiz = insertar(raiz, dato);
    }
    
    void eliminar(int dato) {
        cout << "\n--- Eliminando " << dato << " ---" << endl;
        raiz = eliminar(raiz, dato);
    }
    
    bool buscar(int dato) {
        return buscar(raiz, dato);
    }
    
    void mostrarRecorridos() {
        cout << "\n=== RECORRIDOS ===" << endl;
        cout << "InOrden:    "; inOrden(raiz); cout << endl;
        cout << "PreOrden:   "; preOrden(raiz); cout << endl;
        cout << "PostOrden:  "; postOrden(raiz); cout << endl;
        cout << "Por niveles: "; porNiveles(); cout << endl;
    }
    
    void mostrarArbol() {
        cout << "\n=== ÁRBOL AVL ===" << endl;
        if (raiz == nullptr) {
            cout << "(vacío)" << endl;
            return;
        }
        cout << "Raíz" << endl;
        imprimirArbol(raiz, "", false);
    }
    
    bool estaVacio() {
        return raiz == nullptr;
    }
    
    int obtenerAlturaArbol() {
        return obtenerAltura(raiz);
    }
};

void mostrarMenu() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║        ÁRBOL AVL INTERACTIVO          ║" << endl;
    cout << "╠════════════════════════════════════════╣" << endl;
    cout << "║  1. Insertar nodo                     ║" << endl;
    cout << "║  2. Eliminar nodo                     ║" << endl;
    cout << "║  3. Buscar nodo                       ║" << endl;
    cout << "║  4. Mostrar árbol                     ║" << endl;
    cout << "║  5. Mostrar recorridos                ║" << endl;
    cout << "║  6. Insertar varios nodos             ║" << endl;
    cout << "║  7. Ejemplo predefinido               ║" << endl;
    cout << "║  0. Salir                             ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << "Opción: ";
}

int main() {
    ArbolAVL arbol;
    int opcion, valor;
    
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║          ÁRBOL AVL - Árbol Auto-Balanceado                ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  Un árbol AVL mantiene automáticamente su balance          ║" << endl;
    cout << "║  mediante rotaciones, garantizando O(log n) en todas      ║" << endl;
    cout << "║  las operaciones.                                         ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  h = altura, b = factor de balance                        ║" << endl;
    cout << "║  Balance válido: -1, 0, 1                                 ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    do {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                cout << "Ingresa el valor a insertar: ";
                cin >> valor;
                arbol.insertar(valor);
                arbol.mostrarArbol();
                break;
                
            case 2:
                if (arbol.estaVacio()) {
                    cout << "El árbol está vacío" << endl;
                } else {
                    cout << "Ingresa el valor a eliminar: ";
                    cin >> valor;
                    arbol.eliminar(valor);
                    arbol.mostrarArbol();
                }
                break;
                
            case 3:
                cout << "Ingresa el valor a buscar: ";
                cin >> valor;
                if (arbol.buscar(valor)) {
                    cout << "✓ El valor " << valor << " SÍ está en el árbol" << endl;
                } else {
                    cout << "✗ El valor " << valor << " NO está en el árbol" << endl;
                }
                break;
                
            case 4:
                arbol.mostrarArbol();
                break;
                
            case 5:
                if (arbol.estaVacio()) {
                    cout << "El árbol está vacío" << endl;
                } else {
                    arbol.mostrarRecorridos();
                }
                break;
                
            case 6: {
                cout << "¿Cuántos nodos quieres insertar? ";
                int n;
                cin >> n;
                cout << "Ingresa " << n << " valores separados por espacio: ";
                for (int i = 0; i < n; i++) {
                    cin >> valor;
                    arbol.insertar(valor);
                }
                arbol.mostrarArbol();
                break;
            }
                
            case 7: {
                // Ejemplo que muestra todas las rotaciones
                cout << "\n=== EJEMPLO PREDEFINIDO ===" << endl;
                cout << "Insertando: 10, 20, 30, 40, 50, 25" << endl;
                cout << "Esto mostrará las rotaciones en acción\n" << endl;
                
                arbol.insertar(10);
                arbol.mostrarArbol();
                
                arbol.insertar(20);
                arbol.mostrarArbol();
                
                arbol.insertar(30);  // Causa rotación izquierda
                arbol.mostrarArbol();
                
                arbol.insertar(40);
                arbol.mostrarArbol();
                
                arbol.insertar(50);  // Causa rotación izquierda
                arbol.mostrarArbol();
                
                arbol.insertar(25);  // Causa rotación doble
                arbol.mostrarArbol();
                
                arbol.mostrarRecorridos();
                break;
            }
                
            case 0:
                cout << "\n¡Hasta luego!" << endl;
                break;
                
            default:
                cout << "Opción inválida" << endl;
        }
        
    } while (opcion != 0);
    
    return 0;
}

/*
 * RESUMEN DE ROTACIONES:
 * 
 * LL (Izquierda-Izquierda):
 *   - Balance > 1 y el nuevo nodo está en el subárbol izquierdo del hijo izquierdo
 *   - Solución: Rotación simple a la derecha
 * 
 * RR (Derecha-Derecha):
 *   - Balance < -1 y el nuevo nodo está en el subárbol derecho del hijo derecho
 *   - Solución: Rotación simple a la izquierda
 * 
 * LR (Izquierda-Derecha):
 *   - Balance > 1 y el nuevo nodo está en el subárbol derecho del hijo izquierdo
 *   - Solución: Rotación izquierda + Rotación derecha
 * 
 * RL (Derecha-Izquierda):
 *   - Balance < -1 y el nuevo nodo está en el subárbol izquierdo del hijo derecho
 *   - Solución: Rotación derecha + Rotación izquierda
 * 
 * EJEMPLO VISUAL DE INSERCIÓN 10, 20, 30:
 * 
 *   10            10                  20
 *     \     ->      \       ->       /  \
 *      20            20             10   30
 *                      \
 *                       30
 *   (Desbalanceado)  (Rotación RR)  (Balanceado)
 */
