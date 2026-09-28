"""
BFS con NetworkX y visualización
Combina la potencia de NetworkX con visualización interactiva
"""

import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque
import numpy as np

class BFS_NetworkX:
    def __init__(self):
        self.grafo = nx.DiGraph()  # Grafo dirigido
        self.pos = None
        
    def agregar_arista(self, u, v):
        """Agrega una arista al grafo"""
        self.grafo.add_edge(u, v)
    
    def crear_desde_matriz(self, matriz):
        """Crea grafo desde matriz de adyacencia"""
        n = len(matriz)
        for i in range(n):
            for j in range(n):
                if matriz[i][j] == 1:
                    self.grafo.add_edge(i, j)
    
    def bfs_basico(self, inicio):
        """
        BFS básico usando NetworkX
        Retorna el orden de visita
        """
        return list(nx.bfs_tree(self.grafo, inicio).nodes())
    
    def bfs_por_niveles(self, inicio):
        """
        BFS que retorna nodos agrupados por nivel
        """
        niveles = {}
        visitados = {inicio}
        cola = deque([(inicio, 0)])
        
        while cola:
            nodo, nivel = cola.popleft()
            
            if nivel not in niveles:
                niveles[nivel] = []
            niveles[nivel].append(nodo)
            
            for vecino in self.grafo.successors(nodo):
                if vecino not in visitados:
                    visitados.add(vecino)
                    cola.append((vecino, nivel + 1))
        
        return niveles
    
    def bfs_con_padres(self, inicio):
        """
        BFS que retorna el árbol de padres
        Útil para reconstruir caminos
        """
        padres = {inicio: None}
        visitados = {inicio}
        cola = deque([inicio])
        orden = []
        
        while cola:
            actual = cola.popleft()
            orden.append(actual)
            
            for vecino in self.grafo.successors(actual):
                if vecino not in visitados:
                    visitados.add(vecino)
                    padres[vecino] = actual
                    cola.append(vecino)
        
        return padres, orden
    
    def camino_mas_corto(self, inicio, destino):
        """
        Encuentra el camino más corto usando BFS
        """
        try:
            return nx.shortest_path(self.grafo, inicio, destino)
        except nx.NetworkXNoPath:
            return None
    
    def visualizar_bfs_estatico(self, inicio):
        """
        Visualización estática del BFS con niveles
        """
        niveles = self.bfs_por_niveles(inicio)
        
        # Calcular posiciones por niveles
        if self.pos is None:
            self.pos = self._posiciones_por_nivel(niveles)
        
        plt.figure(figsize=(14, 8))
        
        # Dibujar el grafo base
        nx.draw_networkx_edges(self.grafo, self.pos, edge_color='gray', 
                              alpha=0.3, width=2, arrows=True, 
                              arrowsize=20, arrowstyle='->')
        
        # Colorear nodos por nivel
        colores = plt.cm.rainbow(np.linspace(0, 1, len(niveles)))
        
        for nivel, color in zip(niveles.keys(), colores):
            nodos_nivel = niveles[nivel]
            nx.draw_networkx_nodes(self.grafo, self.pos, 
                                  nodelist=nodos_nivel,
                                  node_color=[color],
                                  node_size=800,
                                  alpha=0.9,
                                  label=f'Nivel {nivel}')
        
        # Etiquetas
        nx.draw_networkx_labels(self.grafo, self.pos, 
                               font_size=14, font_weight='bold')
        
        # Resaltar nodo inicial
        nx.draw_networkx_nodes(self.grafo, self.pos, 
                              nodelist=[inicio],
                              node_color='red',
                              node_size=1000,
                              alpha=0.7)
        
        plt.title(f'BFS desde nodo {inicio} - Vista por niveles', 
                 fontsize=16, fontweight='bold')
        plt.legend(loc='best', fontsize=10)
        plt.axis('off')
        plt.tight_layout()
        plt.show()
    
    def visualizar_bfs_animado(self, inicio):
        """
        Visualización animada del proceso BFS
        """
        padres, orden = self.bfs_con_padres(inicio)
        
        if self.pos is None:
            self.pos = nx.spring_layout(self.grafo, k=2, iterations=50)
        
        fig, ax = plt.subplots(figsize=(14, 8))
        
        def actualizar(frame):
            ax.clear()
            
            # Nodos visitados hasta este frame
            visitados = orden[:frame+1]
            no_visitados = [n for n in self.grafo.nodes() if n not in visitados]
            
            # Dibujar aristas
            nx.draw_networkx_edges(self.grafo, self.pos, ax=ax,
                                  edge_color='gray', alpha=0.3, 
                                  width=2, arrows=True, 
                                  arrowsize=20, arrowstyle='->')
            
            # Aristas del árbol BFS
            aristas_bfs = []
            for nodo in visitados:
                if padres[nodo] is not None:
                    aristas_bfs.append((padres[nodo], nodo))
            
            if aristas_bfs:
                nx.draw_networkx_edges(self.grafo, self.pos, ax=ax,
                                      edgelist=aristas_bfs,
                                      edge_color='blue', alpha=0.6,
                                      width=4, arrows=True,
                                      arrowsize=25, arrowstyle='->')
            
            # Nodos no visitados
            if no_visitados:
                nx.draw_networkx_nodes(self.grafo, self.pos, ax=ax,
                                      nodelist=no_visitados,
                                      node_color='lightgray',
                                      node_size=700, alpha=0.5)
            
            # Nodos visitados
            if visitados:
                nx.draw_networkx_nodes(self.grafo, self.pos, ax=ax,
                                      nodelist=visitados,
                                      node_color='lightgreen',
                                      node_size=800, alpha=0.9)
            
            # Nodo actual
            if frame < len(orden):
                nx.draw_networkx_nodes(self.grafo, self.pos, ax=ax,
                                      nodelist=[orden[frame]],
                                      node_color='red',
                                      node_size=1000, alpha=0.9)
            
            # Etiquetas
            nx.draw_networkx_labels(self.grafo, self.pos, ax=ax,
                                   font_size=14, font_weight='bold')
            
            ax.set_title(f'BFS Animado - Paso {frame+1}/{len(orden)} - Visitando: {orden[frame]}',
                        fontsize=16, fontweight='bold')
            ax.axis('off')
        
        ani = animation.FuncAnimation(fig, actualizar, frames=len(orden),
                                     interval=1000, repeat=True)
        plt.tight_layout()
        plt.show()
        
        return ani
    
    def visualizar_camino(self, inicio, destino):
        """
        Visualiza el camino más corto entre dos nodos
        """
        camino = self.camino_mas_corto(inicio, destino)
        
        if camino is None:
            print(f"No hay camino de {inicio} a {destino}")
            return
        
        if self.pos is None:
            self.pos = nx.spring_layout(self.grafo, k=2, iterations=50)
        
        plt.figure(figsize=(14, 8))
        
        # Aristas del grafo
        nx.draw_networkx_edges(self.grafo, self.pos, 
                              edge_color='gray', alpha=0.3,
                              width=2, arrows=True,
                              arrowsize=20, arrowstyle='->')
        
        # Aristas del camino
        aristas_camino = [(camino[i], camino[i+1]) 
                         for i in range(len(camino)-1)]
        
        colores = plt.cm.rainbow(np.linspace(0, 1, len(aristas_camino)))
        
        for idx, arista in enumerate(aristas_camino):
            nx.draw_networkx_edges(self.grafo, self.pos,
                                  edgelist=[arista],
                                  edge_color=[colores[idx]],
                                  width=5, alpha=0.9,
                                  arrows=True, arrowsize=25,
                                  arrowstyle='->')
            
            # Número de paso
            u, v = arista
            x = (self.pos[u][0] + self.pos[v][0]) / 2
            y = (self.pos[u][1] + self.pos[v][1]) / 2
            plt.text(x, y, str(idx+1), fontsize=12,
                    bbox=dict(boxstyle='round,pad=0.3',
                            facecolor='yellow', alpha=0.8),
                    ha='center')
        
        # Nodos
        otros_nodos = [n for n in self.grafo.nodes() if n not in camino]
        if otros_nodos:
            nx.draw_networkx_nodes(self.grafo, self.pos,
                                  nodelist=otros_nodos,
                                  node_color='lightgray',
                                  node_size=700, alpha=0.5)
        
        # Nodos del camino
        nx.draw_networkx_nodes(self.grafo, self.pos,
                              nodelist=camino,
                              node_color='lightgreen',
                              node_size=800, alpha=0.9)
        
        # Nodo inicio y fin
        nx.draw_networkx_nodes(self.grafo, self.pos,
                              nodelist=[inicio],
                              node_color='blue',
                              node_size=1000, alpha=0.9)
        nx.draw_networkx_nodes(self.grafo, self.pos,
                              nodelist=[destino],
                              node_color='red',
                              node_size=1000, alpha=0.9)
        
        # Etiquetas
        nx.draw_networkx_labels(self.grafo, self.pos,
                               font_size=14, font_weight='bold')
        
        plt.title(f'Camino más corto: {" → ".join(map(str, camino))} (Distancia: {len(camino)-1})',
                 fontsize=16, fontweight='bold')
        plt.axis('off')
        plt.tight_layout()
        plt.show()
    
    def _posiciones_por_nivel(self, niveles):
        """
        Calcula posiciones de nodos organizados por nivel
        """
        pos = {}
        max_nivel = max(niveles.keys())
        
        for nivel, nodos in niveles.items():
            n_nodos = len(nodos)
            y = 1 - (nivel / max_nivel)  # De arriba hacia abajo
            
            for i, nodo in enumerate(nodos):
                x = (i + 1) / (n_nodos + 1)
                pos[nodo] = (x, y)
        
        return pos
    
    def mostrar_informacion(self, inicio):
        """
        Muestra información completa del BFS
        """
        print("=" * 60)
        print("INFORMACIÓN DEL GRAFO")
        print("=" * 60)
        print(f"Número de nodos: {self.grafo.number_of_nodes()}")
        print(f"Número de aristas: {self.grafo.number_of_edges()}")
        print(f"¿Es conexo?: {nx.is_weakly_connected(self.grafo)}")
        print()
        
        print("=" * 60)
        print(f"BFS DESDE NODO {inicio}")
        print("=" * 60)
        
        orden = self.bfs_basico(inicio)
        print(f"\nOrden de visita: {' → '.join(map(str, orden))}")
        
        niveles = self.bfs_por_niveles(inicio)
        print(f"\nNodos por nivel:")
        for nivel, nodos in sorted(niveles.items()):
            print(f"  Nivel {nivel}: {nodos}")
        
        print("=" * 60)
