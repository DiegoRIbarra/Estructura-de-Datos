import random
import time
import mergeSort_cython  # Importar el módulo compilado

if __name__ == "__main__":
    # DEFINE EL TAMAÑO DEL ARREGLO AQUÍ
    n = 10000000  # Cambia este valor para definir el tamaño del arreglo
    
    # Generar un arreglo de números aleatorios de tamaño n
    # Rango de números: de 0 a 1000000
    numeros = [random.randint(0, 1000000) for _ in range(n)]
    
    print(f"Tamaño del arreglo: {n}")
    print(f"Primeros 10 elementos desordenados: {numeros[:10]}")
    
    # Registrar el tiempo de inicio
    tiempo_inicio = time.time()
    
    # Ordenar el arreglo usando merge sort de Cython
    numeros_ordenados = mergeSort_cython.merge_sort(numeros)
    
    # Registrar el tiempo de fin
    tiempo_fin = time.time()
    
    # Calcular el tiempo total de ejecución
    tiempo_total = tiempo_fin - tiempo_inicio
    
    print(f"Primeros 10 elementos ordenados: {numeros_ordenados[:10]}")
    print(f"\n⏱️  Tiempo de ejecución (Cython): {tiempo_total:.6f} segundos")
    print(f"⏱️  Tiempo de ejecución (Cython): {tiempo_total * 1000:.2f} milisegundos")
