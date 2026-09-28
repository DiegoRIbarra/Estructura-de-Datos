# cython: language_level=3

# Definir tipos estáticos para mejorar el rendimiento
def merge_sort(list arr):
    """
    Función principal del algoritmo Merge Sort en Cython
    Divide el arreglo en mitades hasta tener elementos individuales,
    luego los combina de manera ordenada
    """
    cdef int longitud = len(arr)
    
    # Caso base: si el arreglo tiene 1 o 0 elementos, ya está ordenado
    if longitud <= 1:
        return arr
    
    # Encontrar el punto medio del arreglo
    cdef int medio = longitud // 2
    
    # Dividir el arreglo en dos mitades
    cdef list izquierda = arr[:medio]  # Primera mitad
    cdef list derecha = arr[medio:]     # Segunda mitad
    
    # Llamadas recursivas para ordenar cada mitad
    cdef list izquierda_ordenada = merge_sort(izquierda)
    cdef list derecha_ordenada = merge_sort(derecha)
    
    # Combinar las dos mitades ordenadas
    return merge(izquierda_ordenada, derecha_ordenada)


def merge(list izquierda, list derecha):
    """
    Función que combina dos arreglos ordenados en uno solo ordenado
    """
    cdef list resultado = []  # Arreglo que contendrá el resultado final
    cdef int i = 0, j = 0  # Índices para recorrer izquierda y derecha
    cdef int len_izq = len(izquierda)
    cdef int len_der = len(derecha)
    
    # Comparar elementos de ambos arreglos y agregar el menor
    while i < len_izq and j < len_der:
        if izquierda[i] <= derecha[j]:
            resultado.append(izquierda[i])
            i += 1
        else:
            resultado.append(derecha[j])
            j += 1
    
    # Agregar los elementos restantes de izquierda (si hay)
    while i < len_izq:
        resultado.append(izquierda[i])
        i += 1
    
    # Agregar los elementos restantes de derecha (si hay)
    while j < len_der:
        resultado.append(derecha[j])
        j += 1
    
    return resultado
