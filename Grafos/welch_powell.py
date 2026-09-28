"""
ALGORITMO DE WELCH-POWELL PARA COLOREADO DE GRAFOS

¿QUÉ ES?
Es un algoritmo greedy (codicioso) para colorear vértices de un grafo
usando el mínimo número de colores posible, de manera que dos vértices
adyacentes nunca tengan el mismo color.

¿CÓMO FUNCIONA?
1. Ordenar los vértices por grado (número de conexiones) de mayor a menor
2. Asignar el primer color al vértice de mayor grado
3. Recorrer la lista y asignar el mismo color a vértices que no sean adyacentes
4. Repetir con un nuevo color hasta que todos los vértices estén coloreados

APLICACIONES:
- Planificación de horarios (exámenes, clases)
- Asignación de frecuencias de radio
- Resolución de Sudoku
- Coloración de mapas
- Asignación de registros en compiladores
"""

import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np

class WelchPowell:
    def __init__(self):
        self.grafo = nx.Graph()
        self.colores = {}
        self.num_colores = 0
        
    def agregar_arista(self, u, v):
        """Agrega una arista al grafo"""
        self.grafo.add_edge(u, v)
    
    def crear_desde_matriz(self, matriz):
        """Crea grafo desde matriz de adyacencia"""
        n = len(matriz)
        for i in range(n):
            for j in range(i + 1, n):
                if matriz[i][j] == 1:
                    self.grafo.add_edge(i, j)
    
    def algoritmo_welch_powell(self):
        """
        Implementación del algoritmo Welch-Powell
        
        Retorna:
            dict: Diccionario {nodo: color}
            int: Número cromático (número de colores usados)
        """
        # Paso 1: Ordenar vértices por grado (mayor a menor)
        vertices_ordenados = sorted(self.grafo.nodes(), 
                                   key=lambda x: self.grafo.degree(x), 
                                   reverse=True)
        
        print("\n" + "="*60)
        print("PASO 1: Ordenar vértices por grado")
        print("="*60)
        for v in vertices_ordenados:
            print(f"Vértice {v}: grado {self.grafo.degree(v)}")
        
        # Inicializar
        self.colores = {}
        color_actual = 0
        vertices_sin_colorear = set(vertices_ordenados)
        
        print("\n" + "="*60)
        print("PROCESO DE COLOREADO")
        print("="*60)
        
        # Mientras haya vértices sin colorear
        while vertices_sin_colorear:
            print(f"\n--- COLOR {color_actual} ---")
            
            # Tomar el primer vértice sin colorear (mayor grado)
            vertices_disponibles = [v for v in vertices_ordenados 
                                   if v in vertices_sin_colorear]
            
            if not vertices_disponibles:
                break
            
            # Asignar color al primer vértice disponible
            primer_vertice = vertices_disponibles[0]
            self.colores[primer_vertice] = color_actual
            vertices_sin_colorear.remove(primer_vertice)
            coloreados_este_color = [primer_vertice]
            
            print(f"Asignando color {color_actual} a vértice {primer_vertice}")
            
            # Intentar colorear más vértices con el mismo color
            for v in vertices_disponibles[1:]:
                # Verificar si v es adyacente a algún vértice ya coloreado con este color
                puede_colorear = True
                for vertice_coloreado in coloreados_este_color:
                    if self.grafo.has_edge(v, vertice_coloreado):
                        puede_colorear = False
                        break
                
                if puede_colorear:
                    self.colores[v] = color_actual
                    vertices_sin_colorear.remove(v)
                    coloreados_este_color.append(v)
                    print(f"Asignando color {color_actual} a vértice {v}")
            
            color_actual += 1
        
        self.num_colores = color_actual
        
        print("\n" + "="*60)
        print("RESULTADO FINAL")
        print("="*60)
        print(f"Número cromático (colores usados): {self.num_colores}")
        print("\nAsignación de colores:")
        for nodo, color in sorted(self.colores.items()):
            print(f"  Vértice {nodo}: Color {color}")
        
        return self.colores, self.num_colores
    
    def verificar_coloreado(self):
        """
        Verifica que el coloreado sea válido
        (ningún par de vértices adyacentes tiene el mismo color)
        """
        for u, v in self.grafo.edges():
            if self.colores[u] == self.colores[v]:
                return False, f"Error: {u} y {v} son adyacentes y tienen el mismo color"
        return True, "Coloreado válido ✓"
    
    def visualizar_grafo(self):
        """Visualiza el grafo con los colores asignados"""
        if not self.colores:
            print("⚠ Primero ejecuta el algoritmo de Welch-Powell")
            return
        
        # Verificar validez
        valido, mensaje = self.verificar_coloreado()
        
        plt.figure(figsize=(14, 10))
        
        # Layout del grafo
        pos = nx.spring_layout(self.grafo, k=2, iterations=50, seed=42)
        
        # Paleta de colores
        colores_visuales = plt.cm.Set3(np.linspace(0, 1, self.num_colores))
        
        # Dibujar aristas
        nx.draw_networkx_edges(self.grafo, pos, edge_color='gray', 
                              width=2, alpha=0.6)
        
        # Dibujar nodos agrupados por color
        for color_idx in range(self.num_colores):
            nodos_con_color = [nodo for nodo, c in self.colores.items() 
                              if c == color_idx]
            nx.draw_networkx_nodes(self.grafo, pos,
                                  nodelist=nodos_con_color,
                                  node_color=[colores_visuales[color_idx]],
                                  node_size=800,
                                  alpha=0.9,
                                  edgecolors='black',
                                  linewidths=2)
        
        # Etiquetas de nodos
        nx.draw_networkx_labels(self.grafo, pos, font_size=14, 
                               font_weight='bold')
        
        # Leyenda
        leyenda = [mpatches.Patch(color=colores_visuales[i], 
                                 label=f'Color {i}')
                  for i in range(self.num_colores)]
        plt.legend(handles=leyenda, loc='upper left', fontsize=12)
        
        # Título
        titulo = f'Coloreado de Grafo - Algoritmo Welch-Powell\n'
        titulo += f'Número Cromático: {self.num_colores}\n'
        titulo += f'{mensaje}'
        plt.title(titulo, fontsize=14, fontweight='bold', pad=20)
        
        plt.axis('off')
        plt.tight_layout()
        plt.show()
    
    def visualizar_paso_a_paso(self):
        """Visualización animada del proceso de coloreado"""
        if not self.colores:
            print("⚠ Primero ejecuta el algoritmo de Welch-Powell")
            return
        
        # Recrear el proceso
        vertices_ordenados = sorted(self.grafo.nodes(), 
                                   key=lambda x: self.grafo.degree(x), 
                                   reverse=True)
        
        pos = nx.spring_layout(self.grafo, k=2, iterations=50, seed=42)
        colores_visuales = plt.cm.Set3(np.linspace(0, 1, self.num_colores))
        
        # Crear figura con subplots
        fig = plt.figure(figsize=(16, 10))
        
        # Recrear el coloreado paso a paso
        colores_temp = {}
        color_actual = 0
        vertices_sin_colorear = set(vertices_ordenados)
        paso = 0
        
        while vertices_sin_colorear:
            vertices_disponibles = [v for v in vertices_ordenados 
                                   if v in vertices_sin_colorear]
            
            if not vertices_disponibles:
                break
            
            primer_vertice = vertices_disponibles[0]
            colores_temp[primer_vertice] = color_actual
            vertices_sin_colorear.remove(primer_vertice)
            coloreados_este_color = [primer_vertice]
            
            # Dibujar después de asignar primer vértice
            paso += 1
            ax = plt.subplot(2, (self.num_colores + 1) // 2 + 1, paso)
            self._dibujar_estado(ax, pos, colores_temp, colores_visuales,
                               f'Paso {paso}: Color {color_actual} → {primer_vertice}')
            
            for v in vertices_disponibles[1:]:
                puede_colorear = True
                for vertice_coloreado in coloreados_este_color:
                    if self.grafo.has_edge(v, vertice_coloreado):
                        puede_colorear = False
                        break
                
                if puede_colorear:
                    colores_temp[v] = color_actual
                    vertices_sin_colorear.remove(v)
                    coloreados_este_color.append(v)
            
            color_actual += 1
        
        plt.suptitle('Proceso Paso a Paso - Algoritmo Welch-Powell', 
                    fontsize=16, fontweight='bold')
        plt.tight_layout()
        plt.show()
    
    def _dibujar_estado(self, ax, pos, colores_temp, colores_visuales, titulo):
        """Dibuja un estado del grafo durante el proceso"""
        ax.clear()
        
        # Aristas
        nx.draw_networkx_edges(self.grafo, pos, ax=ax,
                              edge_color='gray', width=2, alpha=0.4)
        
        # Nodos coloreados
        for nodo in self.grafo.nodes():
            if nodo in colores_temp:
                color_idx = colores_temp[nodo]
                nx.draw_networkx_nodes(self.grafo, pos, ax=ax,
                                      nodelist=[nodo],
                                      node_color=[colores_visuales[color_idx]],
                                      node_size=600,
                                      edgecolors='black',
                                      linewidths=2)
            else:
                # Sin colorear
                nx.draw_networkx_nodes(self.grafo, pos, ax=ax,
                                      nodelist=[nodo],
                                      node_color='white',
                                      node_size=600,
                                      edgecolors='gray',
                                      linewidths=2)
        
        # Etiquetas
        nx.draw_networkx_labels(self.grafo, pos, ax=ax,
                               font_size=10, font_weight='bold')
        
        ax.set_title(titulo, fontsize=10)
        ax.axis('off')
    
    def obtener_numero_cromatico(self):
        """Retorna el número cromático del grafo"""
        return self.num_colores
    
    def mostrar_informacion(self):
        """Muestra información detallada del grafo"""
        print("\n" + "="*60)
        print("INFORMACIÓN DEL GRAFO")
        print("="*60)
        print(f"Número de vértices: {self.grafo.number_of_nodes()}")
        print(f"Número de aristas: {self.grafo.number_of_edges()}")
        
        grados = dict(self.grafo.degree())
        print(f"\nGrado máximo: {max(grados.values())}")
        print(f"Grado mínimo: {min(grados.values())}")
        print(f"Grado promedio: {sum(grados.values()) / len(grados):.2f}")
        
        print("\nGrados de cada vértice:")
        for v in sorted(grados.keys()):
            print(f"  Vértice {v}: grado {grados[v]}")
        
        print(f"\n¿Es completo?: {nx.is_connected(self.grafo)}")
        print(f"¿Es bipartito?: {nx.is_bipartite(self.grafo)}")
        
        if self.colores:
            print(f"\nNúmero cromático: {self.num_colores}")
            print(f"Cota superior (Δ+1): {max(grados.values()) + 1}")
            print(f"Cota inferior (ω): {nx.graph_clique_number(self.grafo)}")


def menu_principal():
    """Menú interactivo"""
    wp = WelchPowell()
    
    while True:
        print("\n" + "="*60)
        print("ALGORITMO DE WELCH-POWELL - Coloreado de Grafos")
        print("="*60)
        print("1. Crear grafo ejemplo 1 (Ciclo de 5 vértices)")
        print("2. Crear grafo ejemplo 2 (Grafo completo K5)")
        print("3. Crear grafo ejemplo 3 (Grafo bipartito)")
        print("4. Crear grafo ejemplo 4 (Petersen)")
        print("5. Agregar aristas manualmente")
        print("6. Crear desde matriz de adyacencia")
        print("7. Ejecutar algoritmo Welch-Powell")
        print("8. Visualizar grafo coloreado")
        print("9. Visualizar proceso paso a paso")
        print("10. Mostrar información del grafo")
        print("0. Salir")
        print("="*60)
        
        opcion = input("Selecciona una opción: ").strip()
        
        if opcion == "1":
            # Ciclo de 5 vértices (C5) - Necesita 3 colores
            wp = WelchPowell()
            for i in range(5):
                wp.agregar_arista(i, (i + 1) % 5)
            print("✓ Grafo ciclo C5 creado")
            
        elif opcion == "2":
            # Grafo completo K5 - Necesita 5 colores
            wp = WelchPowell()
            for i in range(5):
                for j in range(i + 1, 5):
                    wp.agregar_arista(i, j)
            print("✓ Grafo completo K5 creado")
            
        elif opcion == "3":
            # Grafo bipartito K(3,3) - Necesita 2 colores
            wp = WelchPowell()
            for i in range(3):
                for j in range(3, 6):
                    wp.agregar_arista(i, j)
            print("✓ Grafo bipartito K(3,3) creado")
            
        elif opcion == "4":
            # Grafo de Petersen - Necesita 3 colores
            wp = WelchPowell()
            # Pentágono exterior
            for i in range(5):
                wp.agregar_arista(i, (i + 1) % 5)
            # Pentagrama interior
            for i in range(5, 10):
                wp.agregar_arista(i, 5 + ((i - 5 + 2) % 5))
            # Conexiones entre exterior e interior
            for i in range(5):
                wp.agregar_arista(i, i + 5)
            print("✓ Grafo de Petersen creado")
            
        elif opcion == "5":
            wp = WelchPowell()
            print("\nIngresa las aristas (formato: vertice1 vertice2)")
            print("Escribe 'fin' cuando termines")
            while True:
                entrada = input("Arista: ").strip()
                if entrada.lower() == 'fin':
                    break
                try:
                    partes = entrada.split()
                    if len(partes) != 2:
                        print("Formato inválido")
                        continue
                    try:
                        u = int(partes[0])
                        v = int(partes[1])
                    except ValueError:
                        u = partes[0]
                        v = partes[1]
                    wp.agregar_arista(u, v)
                    print(f"✓ Arista ({u}, {v}) agregada")
                except Exception as e:
                    print(f"Error: {e}")
            print("✓ Grafo creado")
            
        elif opcion == "6":
            try:
                n = int(input("Tamaño de la matriz: "))
                print(f"Ingresa la matriz {n}x{n} (1=arista, 0=no):")
                matriz = []
                for i in range(n):
                    fila = list(map(int, input(f"Fila {i}: ").split()))
                    if len(fila) != n:
                        print(f"Error: se esperaban {n} valores")
                        break
                    matriz.append(fila)
                if len(matriz) == n:
                    wp = WelchPowell()
                    wp.crear_desde_matriz(matriz)
                    print("✓ Grafo creado desde matriz")
            except Exception as e:
                print(f"Error: {e}")
                
        elif opcion == "7":
            if wp.grafo.number_of_nodes() == 0:
                print("⚠ Primero crea un grafo")
                continue
            wp.algoritmo_welch_powell()
            
        elif opcion == "8":
            if wp.grafo.number_of_nodes() == 0:
                print("⚠ Primero crea un grafo")
                continue
            if not wp.colores:
                print("⚠ Primero ejecuta el algoritmo (opción 7)")
                continue
            wp.visualizar_grafo()
            
        elif opcion == "9":
            if wp.grafo.number_of_nodes() == 0:
                print("⚠ Primero crea un grafo")
                continue
            if not wp.colores:
                print("⚠ Primero ejecuta el algoritmo (opción 7)")
                continue
            wp.visualizar_paso_a_paso()
            
        elif opcion == "10":
            if wp.grafo.number_of_nodes() == 0:
                print("⚠ Primero crea un grafo")
                continue
            wp.mostrar_informacion()
            
        elif opcion == "0":
            print("\n¡Hasta luego!")
            break
            
        else:
            print("⚠ Opción inválida")


if __name__ == "__main__":
    print("""
╔════════════════════════════════════════════════════════════╗
║                                                            ║
║    ALGORITMO DE WELCH-POWELL                              ║
║    Coloreado de Grafos                                    ║
║                                                            ║
║    El algoritmo asigna colores a los vértices de un       ║
║    grafo de manera que vértices adyacentes tengan         ║
║    colores diferentes, usando el mínimo número posible.   ║
║                                                            ║
║    Aplicaciones:                                          ║
║    • Planificación de horarios                            ║
║    • Asignación de frecuencias                            ║
║    • Coloración de mapas                                  ║
║    • Resolución de Sudoku                                 ║
║                                                            ║
╚════════════════════════════════════════════════════════════╝
    """)
    
    menu_principal()
