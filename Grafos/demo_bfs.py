"""
Demostración de BFS con NetworkX
Incluye ejemplos y menú interactivo
"""

from bfs_networkx import BFS_NetworkX
import time

def crear_grafo_ejemplo_1():
    r"""
    Grafo ejemplo:
         0
        / \
       1   2
      / \   \
     3   4   5
          \ /
           6
    """
    bfs = BFS_NetworkX()
    bfs.agregar_arista(0, 1)
    bfs.agregar_arista(0, 2)
    bfs.agregar_arista(1, 3)
    bfs.agregar_arista(1, 4)
    bfs.agregar_arista(2, 5)
    bfs.agregar_arista(4, 6)
    bfs.agregar_arista(5, 6)
    return bfs

def crear_grafo_ejemplo_2():
    """
    Grafo más complejo - Red social
    """
    bfs = BFS_NetworkX()
    # Conexiones
    conexiones = [
        ('Alice', 'Bob'),
        ('Alice', 'Carol'),
        ('Bob', 'David'),
        ('Bob', 'Eve'),
        ('Carol', 'Frank'),
        ('David', 'Grace'),
        ('Eve', 'Grace'),
        ('Frank', 'Grace'),
    ]
    for u, v in conexiones:
        bfs.agregar_arista(u, v)
    return bfs

def crear_grafo_ejemplo_3():
    """
    Grafo de laberinto
    """
    bfs = BFS_NetworkX()
    # Grid 4x4 con algunas conexiones bloqueadas
    for i in range(4):
        for j in range(4):
            nodo = i * 4 + j
            # Derecha
            if j < 3:
                bfs.agregar_arista(nodo, nodo + 1)
            # Abajo
            if i < 3:
                bfs.agregar_arista(nodo, nodo + 4)
    
    # Agregar algunas conexiones diagonales
    bfs.agregar_arista(0, 5)
    bfs.agregar_arista(5, 10)
    bfs.agregar_arista(10, 15)
    
    return bfs

def menu_principal():
    """
    Menú interactivo
    """
    bfs = None
    
    while True:
        print("\n" + "=" * 60)
        print("BFS CON NETWORKX - Visualización y Análisis")
        print("=" * 60)
        print("1. Crear grafo ejemplo 1 (Árbol simple)")
        print("2. Crear grafo ejemplo 2 (Red social)")
        print("3. Crear grafo ejemplo 3 (Laberinto 4x4)")
        print("4. Crear grafo manualmente")
        print("5. Crear grafo desde matriz")
        print("6. Visualizar BFS estático (por niveles)")
        print("7. Visualizar BFS animado")
        print("8. Encontrar y visualizar camino más corto")
        print("9. Mostrar información del grafo")
        print("10. Comparar rendimiento Cython vs Python")
        print("0. Salir")
        print("=" * 60)
        
        opcion = input("Selecciona una opción: ").strip()
        
        if opcion == "1":
            bfs = crear_grafo_ejemplo_1()
            print("✓ Grafo ejemplo 1 creado")
            
        elif opcion == "2":
            bfs = crear_grafo_ejemplo_2()
            print("✓ Grafo ejemplo 2 creado (Red social)")
            
        elif opcion == "3":
            bfs = crear_grafo_ejemplo_3()
            print("✓ Grafo ejemplo 3 creado (Laberinto)")
            
        elif opcion == "4":
            bfs = BFS_NetworkX()
            print("\nIngresa las aristas (formato: origen destino)")
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
                    # Intentar convertir a número
                    try:
                        u = int(partes[0])
                        v = int(partes[1])
                    except ValueError:
                        u = partes[0]
                        v = partes[1]
                    bfs.agregar_arista(u, v)
                    print(f"✓ Arista ({u}, {v}) agregada")
                except Exception as e:
                    print(f"Error: {e}")
            print("✓ Grafo creado")
            
        elif opcion == "5":
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
                    bfs = BFS_NetworkX()
                    bfs.crear_desde_matriz(matriz)
                    print("✓ Grafo creado desde matriz")
            except Exception as e:
                print(f"Error: {e}")
        
        elif opcion == "6":
            if bfs is None:
                print("⚠ Primero crea un grafo")
                continue
            inicio = input("Nodo de inicio: ").strip()
            try:
                inicio = int(inicio)
            except ValueError:
                pass
            if inicio not in bfs.grafo.nodes():
                print(f"⚠ El nodo {inicio} no existe en el grafo")
                continue
            bfs.mostrar_informacion(inicio)
            bfs.visualizar_bfs_estatico(inicio)
            
        elif opcion == "7":
            if bfs is None:
                print("⚠ Primero crea un grafo")
                continue
            inicio = input("Nodo de inicio: ").strip()
            try:
                inicio = int(inicio)
            except ValueError:
                pass
            if inicio not in bfs.grafo.nodes():
                print(f"⚠ El nodo {inicio} no existe en el grafo")
                continue
            print("Mostrando animación BFS...")
            bfs.visualizar_bfs_animado(inicio)
            
        elif opcion == "8":
            if bfs is None:
                print("⚠ Primero crea un grafo")
                continue
            inicio = input("Nodo de inicio: ").strip()
            destino = input("Nodo destino: ").strip()
            try:
                inicio = int(inicio)
                destino = int(destino)
            except ValueError:
                pass
            if inicio not in bfs.grafo.nodes():
                print(f"⚠ El nodo {inicio} no existe")
                continue
            if destino not in bfs.grafo.nodes():
                print(f"⚠ El nodo {destino} no existe")
                continue
            
            camino = bfs.camino_mas_corto(inicio, destino)
            if camino:
                print(f"\nCamino: {' → '.join(map(str, camino))}")
                print(f"Distancia: {len(camino) - 1} pasos")
                bfs.visualizar_camino(inicio, destino)
            else:
                print(f"⚠ No hay camino de {inicio} a {destino}")
        
        elif opcion == "9":
            if bfs is None:
                print("⚠ Primero crea un grafo")
                continue
            inicio = input("Nodo de inicio para BFS: ").strip()
            try:
                inicio = int(inicio)
            except ValueError:
                pass
            if inicio not in bfs.grafo.nodes():
                print(f"⚠ El nodo {inicio} no existe")
                continue
            bfs.mostrar_informacion(inicio)
        
        elif opcion == "10":
            print("\n⚠ Para usar Cython, primero compila el módulo con:")
            print("  python setup_bfs.py build_ext --inplace")
            print("\nEsta opción requiere el módulo compilado.")
            
            try:
                from bfs_cython import BFSCython
                
                # Crear grafo grande
                n = int(input("\nNúmero de nodos para prueba (ej: 1000): "))
                
                # Grafo Python
                print("\nCreando grafo en Python...")
                bfs_py = BFS_NetworkX()
                for i in range(n-1):
                    bfs_py.agregar_arista(i, i+1)
                    if i % 3 == 0 and i+3 < n:
                        bfs_py.agregar_arista(i, i+3)
                
                # Grafo Cython
                print("Creando grafo en Cython...")
                bfs_cy = BFSCython(n)
                for i in range(n-1):
                    bfs_cy.agregar_arista(i, i+1)
                    if i % 3 == 0 and i+3 < n:
                        bfs_cy.agregar_arista(i, i+3)
                
                # Benchmark
                print("\nEjecutando BFS...")
                
                inicio_py = time.time()
                for _ in range(100):
                    resultado_py = bfs_py.bfs_basico(0)
                tiempo_py = time.time() - inicio_py
                
                inicio_cy = time.time()
                for _ in range(100):
                    resultado_cy = bfs_cy.bfs_rapido(0)
                tiempo_cy = time.time() - inicio_cy
                
                print(f"\nTiempo Python (100 iteraciones): {tiempo_py:.4f}s")
                print(f"Tiempo Cython (100 iteraciones): {tiempo_cy:.4f}s")
                print(f"Speedup: {tiempo_py/tiempo_cy:.2f}x más rápido")
                
            except ImportError:
                print("\n⚠ Módulo bfs_cython no compilado")
            except Exception as e:
                print(f"Error: {e}")
        
        elif opcion == "0":
            print("\n¡Hasta luego!")
            break
        
        else:
            print("⚠ Opción inválida")

if __name__ == "__main__":
    print("""
╔════════════════════════════════════════════════════════════╗
║                                                            ║
║    BFS - BREADTH-FIRST SEARCH                             ║
║    Implementación con NetworkX y Cython                   ║
║                                                            ║
║    Características:                                        ║
║    ✓ Visualización estática por niveles                   ║
║    ✓ Animación del proceso BFS                            ║
║    ✓ Búsqueda de caminos más cortos                       ║
║    ✓ Versión optimizada con Cython                        ║
║                                                            ║
╚════════════════════════════════════════════════════════════╝
    """)
    
    menu_principal()
