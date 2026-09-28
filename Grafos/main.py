import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.patches import FancyArrowPatch
import numpy as np

class AnalizadorGrafos:
    def __init__(self):
        self.grafo = nx.Graph()
        
    def agregar_arista(self, u, v):
        """Agrega una arista al grafo"""
        self.grafo.add_edge(u, v)
    
    def crear_desde_matriz(self, matriz):
        """Crea un grafo desde una matriz de adyacencia"""
        n = len(matriz)
        for i in range(n):
            for j in range(i, n):
                if matriz[i][j] == 1:
                    self.grafo.add_edge(i, j)
    
    def es_euleriano(self):
        """Verifica si el grafo tiene un camino o ciclo euleriano"""
        if not nx.is_connected(self.grafo):
            return "No euleriano (no conexo)"
        
        grados_impares = [v for v in self.grafo.nodes() if self.grafo.degree(v) % 2 == 1]
        
        if len(grados_impares) == 0:
            return "Ciclo Euleriano"
        elif len(grados_impares) == 2:
            return "Camino Euleriano"
        else:
            return "No euleriano"
    
    def obtener_camino_euleriano(self):
        """Obtiene el camino euleriano si existe"""
        tipo = self.es_euleriano()
        
        if tipo == "Ciclo Euleriano":
            return list(nx.eulerian_circuit(self.grafo))
        elif tipo == "Camino Euleriano":
            # Encontrar nodos con grado impar
            nodos_impares = [v for v in self.grafo.nodes() if self.grafo.degree(v) % 2 == 1]
            # Crear grafo temporal con arista adicional
            G_temp = self.grafo.copy()
            if len(nodos_impares) == 2:
                G_temp.add_edge(nodos_impares[0], nodos_impares[1])
                circuito = list(nx.eulerian_circuit(G_temp))
                # Remover la arista temporal del circuito
                camino = [(u, v) for u, v in circuito if not (
                    (u == nodos_impares[0] and v == nodos_impares[1]) or 
                    (u == nodos_impares[1] and v == nodos_impares[0])
                )]
                return camino
        return None
    
    def es_hamiltoniano(self):
        """Verifica si el grafo tiene un ciclo hamiltoniano (aproximación)"""
        # Para grafos pequeños, intentamos encontrar un camino hamiltoniano
        n = len(self.grafo.nodes())
        
        if n < 3:
            return False
        
        # Intentar encontrar un ciclo hamiltoniano mediante búsqueda
        for nodo_inicio in self.grafo.nodes():
            camino = self._buscar_ciclo_hamiltoniano(nodo_inicio)
            if camino:
                return True
        return False
    
    def _buscar_ciclo_hamiltoniano(self, inicio, camino=None, visitados=None):
        """Búsqueda recursiva de ciclo hamiltoniano"""
        if camino is None:
            camino = [inicio]
            visitados = {inicio}
        
        if len(camino) == len(self.grafo.nodes()):
            # Verificar si podemos regresar al inicio
            if inicio in self.grafo.neighbors(camino[-1]):
                return camino + [inicio]
            return None
        
        for vecino in self.grafo.neighbors(camino[-1]):
            if vecino not in visitados:
                visitados.add(vecino)
                camino.append(vecino)
                
                resultado = self._buscar_ciclo_hamiltoniano(inicio, camino, visitados)
                if resultado:
                    return resultado
                
                camino.pop()
                visitados.remove(vecino)
        
        return None
    
    def obtener_ciclo_hamiltoniano(self):
        """Obtiene un ciclo hamiltoniano si existe"""
        for nodo_inicio in self.grafo.nodes():
            camino = self._buscar_ciclo_hamiltoniano(nodo_inicio)
            if camino:
                return [(camino[i], camino[i+1]) for i in range(len(camino)-1)]
        return None
    
    def dibujar_grafo(self, camino=None, titulo="Grafo"):
        """Dibuja el grafo y opcionalmente resalta un camino"""
        plt.figure(figsize=(12, 8))
        
        # Posición de los nodos usando layout circular para mejor visualización
        pos = nx.spring_layout(self.grafo, k=2, iterations=50)
        
        # Dibujar todos los nodos
        nx.draw_networkx_nodes(self.grafo, pos, node_color='lightblue', 
                              node_size=700, alpha=0.9)
        
        # Dibujar todas las aristas en gris claro
        nx.draw_networkx_edges(self.grafo, pos, edge_color='gray', 
                              width=2, alpha=0.3)
        
        # Dibujar etiquetas de nodos
        nx.draw_networkx_labels(self.grafo, pos, font_size=16, 
                               font_weight='bold')
        
        # Si hay un camino, resaltarlo
        if camino:
            # Dibujar el camino con colores
            colores = plt.cm.rainbow(np.linspace(0, 1, len(camino)))
            
            for idx, (u, v) in enumerate(camino):
                # Dibujar arista del camino
                nx.draw_networkx_edges(
                    self.grafo, pos,
                    edgelist=[(u, v)],
                    edge_color=[colores[idx]],
                    width=4,
                    alpha=0.8,
                    arrows=True,
                    arrowsize=20,
                    arrowstyle='->'
                )
                
                # Agregar número de orden
                x = (pos[u][0] + pos[v][0]) / 2
                y = (pos[u][1] + pos[v][1]) / 2
                plt.text(x, y, str(idx+1), fontsize=10, 
                        bbox=dict(boxstyle='round,pad=0.3', 
                                facecolor='yellow', alpha=0.7),
                        ha='center')
        
        plt.title(titulo, fontsize=16, fontweight='bold')
        plt.axis('off')
        plt.tight_layout()
        plt.show()
    
    def analizar_y_dibujar(self):
        """Analiza el grafo y dibuja el resultado apropiado"""
        print("=" * 60)
        print("ANÁLISIS DEL GRAFO")
        print("=" * 60)
        print(f"Número de nodos: {len(self.grafo.nodes())}")
        print(f"Número de aristas: {len(self.grafo.edges())}")
        print(f"Grados de los nodos: {dict(self.grafo.degree())}")
        print()
        
        # Verificar si es euleriano
        tipo_euler = self.es_euleriano()
        print(f"Tipo Euleriano: {tipo_euler}")
        
        # Verificar si es hamiltoniano
        es_ham = self.es_hamiltoniano()
        print(f"¿Es Hamiltoniano?: {'Sí' if es_ham else 'No'}")
        print("=" * 60)
        print()
        
        # Dibujar según el tipo
        if "Euleriano" in tipo_euler and tipo_euler != "No euleriano (no conexo)" and tipo_euler != "No euleriano":
            print(f"Dibujando {tipo_euler}...")
            camino = self.obtener_camino_euleriano()
            if camino:
                print(f"\nRecorrido Euleriano (aristas):")
                for i, (u, v) in enumerate(camino, 1):
                    print(f"  {i}. {u} → {v}")
                self.dibujar_grafo(camino, f"{tipo_euler}")
        elif es_ham:
            print("Dibujando Ciclo Hamiltoniano...")
            camino = self.obtener_ciclo_hamiltoniano()
            if camino:
                print(f"\nRecorrido Hamiltoniano (aristas):")
                for i, (u, v) in enumerate(camino, 1):
                    print(f"  {i}. {u} → {v}")
                # Mostrar secuencia de nodos
                nodos = [camino[0][0]]
                for u, v in camino:
                    nodos.append(v)
                print(f"\nSecuencia de nodos: {' → '.join(map(str, nodos))}")
                self.dibujar_grafo(camino, "Ciclo Hamiltoniano")
        else:
            print("El grafo no es Euleriano ni Hamiltoniano")
            print("Dibujando grafo sin recorrido especial...")
            self.dibujar_grafo(None, "Grafo (No Euleriano ni Hamiltoniano)")


def menu_principal():
    """Menú principal del programa"""
    analizador = AnalizadorGrafos()
    
    while True:
        print("\n" + "=" * 60)
        print("ANALIZADOR DE GRAFOS - Euleriano y Hamiltoniano")
        print("=" * 60)
        print("1. Agregar aristas manualmente")
        print("2. Crear grafo desde matriz de adyacencia")
        print("3. Usar grafo de ejemplo (Ciclo Euleriano)")
        print("4. Usar grafo de ejemplo (Camino Euleriano)")
        print("5. Usar grafo de ejemplo (Hamiltoniano)")
        print("6. Analizar y dibujar grafo")
        print("7. Salir")
        print("=" * 60)
        
        opcion = input("Selecciona una opción: ").strip()
        
        if opcion == "1":
            print("\nIngresa las aristas (formato: nodo1 nodo2)")
            print("Escribe 'fin' cuando termines")
            while True:
                entrada = input("Arista: ").strip()
                if entrada.lower() == 'fin':
                    break
                try:
                    u, v = entrada.split()
                    analizador.agregar_arista(u, v)
                    print(f"Arista ({u}, {v}) agregada")
                except:
                    print("Formato inválido. Usa: nodo1 nodo2")
        
        elif opcion == "2":
            print("\nIngresa el tamaño de la matriz:")
            try:
                n = int(input("N = "))
                print(f"Ingresa la matriz de adyacencia {n}x{n}")
                print("(1 para conexión, 0 para no conexión)")
                matriz = []
                for i in range(n):
                    fila = list(map(int, input(f"Fila {i}: ").split()))
                    if len(fila) != n:
                        print(f"Error: se esperaban {n} valores")
                        break
                    matriz.append(fila)
                if len(matriz) == n:
                    analizador.crear_desde_matriz(matriz)
                    print("Grafo creado desde matriz")
            except:
                print("Error al crear la matriz")
        
        elif opcion == "3":
            # Grafo euleriano (todos los nodos tienen grado par)
            analizador = AnalizadorGrafos()
            analizador.agregar_arista('A', 'B')
            analizador.agregar_arista('B', 'C')
            analizador.agregar_arista('C', 'D')
            analizador.agregar_arista('D', 'A')
            analizador.agregar_arista('A', 'C')
            analizador.agregar_arista('B', 'D')
            print("Grafo de ejemplo (Ciclo Euleriano) creado")
        
        elif opcion == "4":
            # Camino euleriano (exactamente 2 nodos con grado impar)
            analizador = AnalizadorGrafos()
            analizador.agregar_arista('A', 'B')
            analizador.agregar_arista('B', 'C')
            analizador.agregar_arista('C', 'D')
            analizador.agregar_arista('D', 'E')
            analizador.agregar_arista('E', 'A')
            analizador.agregar_arista('B', 'D')
            print("Grafo de ejemplo (Camino Euleriano) creado")
        
        elif opcion == "5":
            # Grafo hamiltoniano (ciclo completo)
            analizador = AnalizadorGrafos()
            analizador.agregar_arista('A', 'B')
            analizador.agregar_arista('B', 'C')
            analizador.agregar_arista('C', 'D')
            analizador.agregar_arista('D', 'E')
            analizador.agregar_arista('E', 'A')
            analizador.agregar_arista('A', 'C')
            analizador.agregar_arista('B', 'E')
            print("Grafo de ejemplo (Hamiltoniano) creado")
        
        elif opcion == "6":
            if len(analizador.grafo.nodes()) == 0:
                print("\n¡El grafo está vacío! Agrega aristas primero.")
            else:
                analizador.analizar_y_dibujar()
        
        elif opcion == "7":
            print("\n¡Hasta luego!")
            break
        
        else:
            print("\nOpción inválida")


if __name__ == "__main__":
    menu_principal()
