# cython: language_level=3
"""
BFS con Cython - Versión optimizada
Usa tipos estáticos de C para mejor rendimiento
"""

from libc.stdlib cimport malloc, free
from cpython.list cimport PyList_New, PyList_SET_ITEM
from cpython.ref cimport Py_INCREF
import numpy as np
cimport numpy as np

cdef class BFSCython:
    """
    Implementación de BFS en Cython con tipos estáticos
    para mejor rendimiento
    """
    cdef int num_vertices
    cdef list grafo
    
    def __init__(self, int vertices):
        self.num_vertices = vertices
        self.grafo = [[] for _ in range(vertices)]
    
    cpdef void agregar_arista(self, int u, int v):
        """Agrega una arista al grafo"""
        self.grafo[u].append(v)
    
    cpdef list bfs_rapido(self, int inicio):
        """
        BFS optimizado con Cython
        Retorna el orden de visita
        """
        cdef int i, actual, vecino
        cdef list visitados = [False] * self.num_vertices
        cdef list cola = [inicio]
        cdef list resultado = []
        cdef int idx_cola = 0
        
        visitados[inicio] = True
        
        while idx_cola < len(cola):
            actual = cola[idx_cola]
            idx_cola += 1
            resultado.append(actual)
            
            for vecino in self.grafo[actual]:
                if not visitados[vecino]:
                    visitados[vecino] = True
                    cola.append(vecino)
        
        return resultado
    
    cpdef dict bfs_con_niveles(self, int inicio):
        """
        BFS que retorna los niveles de cada nodo
        """
        cdef int actual, vecino
        cdef list visitados = [False] * self.num_vertices
        cdef list niveles = [-1] * self.num_vertices
        cdef list cola = [inicio]
        cdef int idx_cola = 0
        
        visitados[inicio] = True
        niveles[inicio] = 0
        
        while idx_cola < len(cola):
            actual = cola[idx_cola]
            idx_cola += 1
            
            for vecino in self.grafo[actual]:
                if not visitados[vecino]:
                    visitados[vecino] = True
                    niveles[vecino] = niveles[actual] + 1
                    cola.append(vecino)
        
        return {i: niveles[i] for i in range(self.num_vertices) if niveles[i] != -1}
    
    cpdef list camino_mas_corto(self, int inicio, int destino):
        """
        Encuentra el camino más corto entre dos nodos
        Retorna la lista de nodos en el camino
        """
        if inicio == destino:
            return [inicio]
        
        cdef int actual, vecino
        cdef list visitados = [False] * self.num_vertices
        cdef list padres = [-1] * self.num_vertices
        cdef list cola = [inicio]
        cdef int idx_cola = 0
        cdef bint encontrado = False
        
        visitados[inicio] = True
        
        while idx_cola < len(cola) and not encontrado:
            actual = cola[idx_cola]
            idx_cola += 1
            
            for vecino in self.grafo[actual]:
                if not visitados[vecino]:
                    visitados[vecino] = True
                    padres[vecino] = actual
                    cola.append(vecino)
                    
                    if vecino == destino:
                        encontrado = True
                        break
        
        if not encontrado:
            return []
        
        # Reconstruir camino
        cdef list camino = []
        cdef int nodo = destino
        while nodo != -1:
            camino.append(nodo)
            nodo = padres[nodo]
        
        camino.reverse()
        return camino
