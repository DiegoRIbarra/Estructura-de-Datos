import random  # Para generar números aleatorios
import time    # Para medir el tiempo de ejecución

def merge_sort(arr):
    """
    Función principal del algoritmo Merge Sort
    Divide el arreglo en mitades hasta tener elementos individuales,
    luego los combina de manera ordenada
    """
    # Caso base: si el arreglo tiene 1 o 0 elementos, ya está ordenado
    if len(arr) <= 1:
        return arr
    
    # Encontrar el punto medio del arreglo
    medio = len(arr) // 2
    
    # Dividir el arreglo en dos mitades
    izquierda = arr[:medio]  # Primera mitad
    derecha = arr[medio:]     # Segunda mitad
    
    # Llamadas recursivas para ordenar cada mitad
    izquierda_ordenada = merge_sort(izquierda)
    derecha_ordenada = merge_sort(derecha)
    
    # Combinar las dos mitades ordenadas
    return merge(izquierda_ordenada, derecha_ordenada)


def merge(izquierda, derecha):
    """
    Función que combina dos arreglos ordenados en uno solo ordenado
    """
    resultado = []  # Arreglo que contendrá el resultado final
    i = j = 0  # Índices para recorrer izquierda y derecha
    
    # Comparar elementos de ambos arreglos y agregar el menor
    while i < len(izquierda) and j < len(derecha):
        if izquierda[i] <= derecha[j]:
            resultado.append(izquierda[i])
            i += 1
        else:
            resultado.append(derecha[j])
            j += 1
    
    # Agregar los elementos restantes de izquierda (si hay)
    while i < len(izquierda):
        resultado.append(izquierda[i])
        i += 1
    
    # Agregar los elementos restantes de derecha (si hay)
    while j < len(derecha):
        resultado.append(derecha[j])
        j += 1
    
    return resultado


# Ejemplo de uso
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
    
    # Ordenar el arreglo usando merge sort
    numeros_ordenados = merge_sort(numeros)
    
    # Registrar el tiempo de fin
    tiempo_fin = time.time()
    
    # Calcular el tiempo total de ejecución
    tiempo_total = tiempo_fin - tiempo_inicio
    
    print(f"Primeros 10 elementos ordenados: {numeros_ordenados[:10]}")
    print(f"\n⏱️  Tiempo de ejecución: {tiempo_total:.6f} segundos")
    print(f"⏱️  Tiempo de ejecución: {tiempo_total * 1000:.2f} milisegundos")