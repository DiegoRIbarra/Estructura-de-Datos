#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <functional>

enum Color { ROJO, NEGRO };

template <typename T>
struct Nodo {
    T dato;
    Color color;
    Nodo* izq;
    Nodo* der;
    Nodo* padre;
    
    // Posición para visualización
    float x, y;
    
    Nodo(T valor) : dato(valor), color(ROJO), izq(nullptr), der(nullptr), padre(nullptr), x(0), y(0) {}
};

template <typename T>
class ArbolRojoNegro {
private:
    Nodo<T>* raiz;
    Nodo<T>* TNULL; // Nodo centinela
    
    void rotarIzquierda(Nodo<T>* x) {
        Nodo<T>* y = x->der;
        x->der = y->izq;
        if (y->izq != TNULL) {
            y->izq->padre = x;
        }
        y->padre = x->padre;
        if (x->padre == nullptr) {
            raiz = y;
        } else if (x == x->padre->izq) {
            x->padre->izq = y;
        } else {
            x->padre->der = y;
        }
        y->izq = x;
        x->padre = y;
    }
    
    void rotarDerecha(Nodo<T>* x) {
        Nodo<T>* y = x->izq;
        x->izq = y->der;
        if (y->der != TNULL) {
            y->der->padre = x;
        }
        y->padre = x->padre;
        if (x->padre == nullptr) {
            raiz = y;
        } else if (x == x->padre->der) {
            x->padre->der = y;
        } else {
            x->padre->izq = y;
        }
        y->der = x;
        x->padre = y;
    }
    
    void corregirInsercion(Nodo<T>* k) {
        Nodo<T>* u;
        while (k->padre != nullptr && k->padre->color == ROJO) {
            if (k->padre == k->padre->padre->der) {
                u = k->padre->padre->izq;
                if (u->color == ROJO) {
                    u->color = NEGRO;
                    k->padre->color = NEGRO;
                    k->padre->padre->color = ROJO;
                    k = k->padre->padre;
                } else {
                    if (k == k->padre->izq) {
                        k = k->padre;
                        rotarDerecha(k);
                    }
                    k->padre->color = NEGRO;
                    k->padre->padre->color = ROJO;
                    rotarIzquierda(k->padre->padre);
                }
            } else {
                u = k->padre->padre->der;
                if (u->color == ROJO) {
                    u->color = NEGRO;
                    k->padre->color = NEGRO;
                    k->padre->padre->color = ROJO;
                    k = k->padre->padre;
                } else {
                    if (k == k->padre->der) {
                        k = k->padre;
                        rotarIzquierda(k);
                    }
                    k->padre->color = NEGRO;
                    k->padre->padre->color = ROJO;
                    rotarDerecha(k->padre->padre);
                }
            }
            if (k == raiz) {
                break;
            }
        }
        raiz->color = NEGRO;
    }
    
    void transplant(Nodo<T>* u, Nodo<T>* v) {
        if (u->padre == nullptr) {
            raiz = v;
        } else if (u == u->padre->izq) {
            u->padre->izq = v;
        } else {
            u->padre->der = v;
        }
        v->padre = u->padre;
    }
    
    Nodo<T>* minimo(Nodo<T>* nodo) {
        while (nodo->izq != TNULL) {
            nodo = nodo->izq;
        }
        return nodo;
    }
    
    void corregirEliminacion(Nodo<T>* x) {
        Nodo<T>* s;
        while (x != raiz && x->color == NEGRO) {
            if (x == x->padre->izq) {
                s = x->padre->der;
                if (s->color == ROJO) {
                    s->color = NEGRO;
                    x->padre->color = ROJO;
                    rotarIzquierda(x->padre);
                    s = x->padre->der;
                }
                if (s->izq->color == NEGRO && s->der->color == NEGRO) {
                    s->color = ROJO;
                    x = x->padre;
                } else {
                    if (s->der->color == NEGRO) {
                        s->izq->color = NEGRO;
                        s->color = ROJO;
                        rotarDerecha(s);
                        s = x->padre->der;
                    }
                    s->color = x->padre->color;
                    x->padre->color = NEGRO;
                    s->der->color = NEGRO;
                    rotarIzquierda(x->padre);
                    x = raiz;
                }
            } else {
                s = x->padre->izq;
                if (s->color == ROJO) {
                    s->color = NEGRO;
                    x->padre->color = ROJO;
                    rotarDerecha(x->padre);
                    s = x->padre->izq;
                }
                if (s->der->color == NEGRO && s->izq->color == NEGRO) {
                    s->color = ROJO;
                    x = x->padre;
                } else {
                    if (s->izq->color == NEGRO) {
                        s->der->color = NEGRO;
                        s->color = ROJO;
                        rotarIzquierda(s);
                        s = x->padre->izq;
                    }
                    s->color = x->padre->color;
                    x->padre->color = NEGRO;
                    s->izq->color = NEGRO;
                    rotarDerecha(x->padre);
                    x = raiz;
                }
            }
        }
        x->color = NEGRO;
    }
    
    void eliminarNodoAux(Nodo<T>* nodo, T key) {
        Nodo<T>* z = TNULL;
        Nodo<T>* x, *y;
        while (nodo != TNULL) {
            if (nodo->dato == key) {
                z = nodo;
            }
            if (nodo->dato <= key) {
                nodo = nodo->der;
            } else {
                nodo = nodo->izq;
            }
        }
        
        if (z == TNULL) {
            return;
        }
        
        y = z;
        Color yColorOriginal = y->color;
        if (z->izq == TNULL) {
            x = z->der;
            transplant(z, z->der);
        } else if (z->der == TNULL) {
            x = z->izq;
            transplant(z, z->izq);
        } else {
            y = minimo(z->der);
            yColorOriginal = y->color;
            x = y->der;
            if (y->padre == z) {
                x->padre = y;
            } else {
                transplant(y, y->der);
                y->der = z->der;
                y->der->padre = y;
            }
            transplant(z, y);
            y->izq = z->izq;
            y->izq->padre = y;
            y->color = z->color;
        }
        delete z;
        if (yColorOriginal == NEGRO) {
            corregirEliminacion(x);
        }
    }
    
    void limpiar(Nodo<T>* nodo) {
        if (nodo != TNULL && nodo != nullptr) {
            limpiar(nodo->izq);
            limpiar(nodo->der);
            delete nodo;
        }
    }
    
    int calcularAltura(Nodo<T>* nodo) {
        if (nodo == TNULL || nodo == nullptr) return 0;
        return 1 + std::max(calcularAltura(nodo->izq), calcularAltura(nodo->der));
    }
    
public:
    ArbolRojoNegro() {
        TNULL = new Nodo<T>(T());
        TNULL->color = NEGRO;
        TNULL->izq = nullptr;
        TNULL->der = nullptr;
        raiz = TNULL;
    }
    
    ~ArbolRojoNegro() {
        limpiar(raiz);
        delete TNULL;
    }
    
    void insertar(T key) {
        Nodo<T>* nodo = new Nodo<T>(key);
        nodo->padre = nullptr;
        nodo->izq = TNULL;
        nodo->der = TNULL;
        nodo->color = ROJO;
        
        Nodo<T>* y = nullptr;
        Nodo<T>* x = raiz;
        
        while (x != TNULL) {
            y = x;
            if (nodo->dato < x->dato) {
                x = x->izq;
            } else {
                x = x->der;
            }
        }
        
        nodo->padre = y;
        if (y == nullptr) {
            raiz = nodo;
        } else if (nodo->dato < y->dato) {
            y->izq = nodo;
        } else {
            y->der = nodo;
        }
        
        if (nodo->padre == nullptr) {
            nodo->color = NEGRO;
            return;
        }
        
        if (nodo->padre->padre == nullptr) {
            return;
        }
        
        corregirInsercion(nodo);
    }
    
    void eliminar(T key) {
        eliminarNodoAux(raiz, key);
    }
    
    bool buscar(T key) {
        Nodo<T>* actual = raiz;
        while (actual != TNULL) {
            if (key == actual->dato) {
                return true;
            } else if (key < actual->dato) {
                actual = actual->izq;
            } else {
                actual = actual->der;
            }
        }
        return false;
    }
    
    Nodo<T>* getRaiz() { return raiz; }
    Nodo<T>* getTNULL() { return TNULL; }
    
    int getAltura() { return calcularAltura(raiz); }
    
    bool estaVacio() { return raiz == TNULL; }
    
    // Obtener nodos por niveles para visualización
    std::vector<std::vector<Nodo<T>*>> getNodosPorNivel() {
        std::vector<std::vector<Nodo<T>*>> niveles;
        if (raiz == TNULL) return niveles;
        
        std::queue<Nodo<T>*> cola;
        cola.push(raiz);
        
        while (!cola.empty()) {
            int size = cola.size();
            std::vector<Nodo<T>*> nivel;
            
            for (int i = 0; i < size; i++) {
                Nodo<T>* actual = cola.front();
                cola.pop();
                nivel.push_back(actual);
                
                if (actual->izq != TNULL) {
                    cola.push(actual->izq);
                }
                if (actual->der != TNULL) {
                    cola.push(actual->der);
                }
            }
            niveles.push_back(nivel);
        }
        return niveles;
    }
    
    // Recorrer el árbol y ejecutar una función en cada nodo
    void recorrerInorden(std::function<void(Nodo<T>*)> func) {
        std::function<void(Nodo<T>*)> inorden = [&](Nodo<T>* nodo) {
            if (nodo != TNULL) {
                inorden(nodo->izq);
                func(nodo);
                inorden(nodo->der);
            }
        };
        inorden(raiz);
    }
};

#endif
