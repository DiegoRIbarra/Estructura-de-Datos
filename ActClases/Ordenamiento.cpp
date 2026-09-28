#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>
#include <thread>

// Comprueba si un vector esta ordenado (ascendente)
template<typename T>
bool isSorted(const std::vector<T>& v) {
    for (size_t i = 1; i < v.size(); ++i) {
        if (v[i-1] > v[i]) return false;
    }
    return true;
}

// Imprime el contenido de un vector
template<typename T>
void printVec(const std::vector<T>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) std::cout << ' ';
        std::cout << v[i];
    }
    std::cout << '\n';
}

// Selection sort generico para vectors
template<typename T>
void selectionSort(std::vector<T>& a) {
    const size_t n = a.size();
    for (size_t i = 0; i + 1 < n; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (a[j] < a[min_idx]) min_idx = j;
        }
        if (min_idx != i) std::swap(a[i], a[min_idx]);
    }
}

template<typename T>
void insertionSort(std::vector<T>& a) {
    const size_t n = a.size();
    for (size_t i = 1; i < n; ++i) {
        T key = a[i];
        size_t j = i;
        while (j > 0 && a[j-1] > key) {
            a[j] = a[j-1];
            --j;
        }
        a[j] = key;
    }
}

template<typename T>
void bubbleSort(std::vector<T>& a) {
    const size_t n = a.size();
    for (size_t i = 0; i < n; ++i) {
        bool swapped = false;
        for (size_t j = 0; j + 1 < n - i; ++j) {
            if (a[j] > a[j+1]) {
                std::swap(a[j], a[j+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Merge sort: función auxiliar para mezclar dos subvectores ordenados
template<typename T>
void merge(std::vector<T>& a, size_t left, size_t mid, size_t right) {
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;
    
    std::vector<T> L(n1), R(n2);
    for (size_t i = 0; i < n1; ++i) L[i] = a[left + i];
    for (size_t i = 0; i < n2; ++i) R[i] = a[mid + 1 + i];
    
    size_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k++] = L[i++];
        } else {
            a[k++] = R[j++];
        }
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

template<typename T>
void mergeSortHelper(std::vector<T>& a, size_t left, size_t right) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        mergeSortHelper(a, left, mid);
        mergeSortHelper(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

template<typename T>
void mergeSort(std::vector<T>& a) {
    if (a.size() > 1) {
        mergeSortHelper(a, 0, a.size() - 1);
    }
}

// Merge sort paralelo usando threads
template<typename T>
void mergeSortParallelHelper(std::vector<T>& a, size_t left, size_t right, int depth) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        
        // Limita la profundidad de paralelización para evitar demasiados threads
        // Típicamente creamos threads solo en los primeros niveles de recursión
        const int MAX_DEPTH = 4; // Controla cuántos niveles usan threads
        
        if (depth < MAX_DEPTH) {
            // Crea threads para ordenar las mitades en paralelo
            std::thread leftThread([&]() {
                mergeSortParallelHelper(a, left, mid, depth + 1);
            });
            std::thread rightThread([&]() {
                mergeSortParallelHelper(a, mid + 1, right, depth + 1);
            });
            
            // Espera a que ambos threads terminen
            leftThread.join();
            rightThread.join();
        } else {
            // Usa versión secuencial en niveles profundos
            mergeSortHelper(a, left, mid);
            mergeSortHelper(a, mid + 1, right);
        }
        
        // Mezcla las dos mitades ordenadas
        merge(a, left, mid, right);
    }
}

template<typename T>
void mergeSortParallel(std::vector<T>& a) {
    if (a.size() > 1) {
        mergeSortParallelHelper(a, 0, a.size() - 1, 0);
    }
}

// QuickSort: función de partición (esquema de Hoare)
template<typename T>
size_t partition(std::vector<T>& a, size_t left, size_t right) {
    T pivot = a[left + (right - left) / 2]; // Pivote en el medio
    size_t i = left;
    size_t j = right;
    
    while (true) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        
        if (i >= j) return j;
        
        std::swap(a[i], a[j]);
        i++;
        j--;
    }
}

template<typename T>
void quickSortHelper(std::vector<T>& a, size_t left, size_t right) {
    if (left < right) {
        size_t p = partition(a, left, right);
        
        // Ordena recursivamente las dos particiones
        if (p > 0 && left < p) {
            quickSortHelper(a, left, p);
        }
        if (p + 1 < right) {
            quickSortHelper(a, p + 1, right);
        }
    }
}

template<typename T>
void quickSort(std::vector<T>& a) {
    if (a.size() > 1) {
        quickSortHelper(a, 0, a.size() - 1);
    }
}

// Mide el tiempo en milisegundos que tarda una función de ordenación
template<typename SortFunc, typename T>
double measure_ms(SortFunc sortFn, std::vector<T> &v) {
    auto start = std::chrono::steady_clock::now();
    sortFn(v);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> dur = end - start;
    return dur.count();
}

// Función para ejecutar las pruebas con un tamaño específico
void runBenchmark(size_t N) {
    std::cout << "\n========================================\n";
    std::cout << "Prueba con " << N / 1000000.0 << " millones de elementos\n";
    std::cout << "========================================\n";
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(-20000000, 20000000);
    
    // Vector original aleatorio
    std::vector<int> original(N);
    for (size_t i = 0; i < N; ++i) original[i] = distrib(gen);
    
    // Copias para cada algoritmo
    auto v_mer = original;
    auto v_mer_par = original;
    auto v_quick = original;
    
    // Mide merge sort
    double t_mer = measure_ms([](auto &v){ mergeSort(v); }, v_mer);
    std::cout << "Merge sort:          " << t_mer << " ms";
    std::cout << " | ordenado: " << (isSorted(v_mer) ? "✓" : "✗") << '\n';
    
    // Mide merge sort paralelo
    double t_mer_par = measure_ms([](auto &v){ mergeSortParallel(v); }, v_mer_par);
    std::cout << "Merge sort paralelo: " << t_mer_par << " ms";
    std::cout << " | ordenado: " << (isSorted(v_mer_par) ? "✓" : "✗") << '\n';
    
    // Mide quicksort
    double t_quick = measure_ms([](auto &v){ quickSort(v); }, v_quick);
    std::cout << "Quick sort:          " << t_quick << " ms";
    std::cout << " | ordenado: " << (isSorted(v_quick) ? "✓" : "✗") << '\n';
    
    // Muestra las aceleraciones
    std::cout << "\nAceleración merge paralelo vs secuencial: " << (t_mer / t_mer_par) << "x\n";
    std::cout << "Quick sort vs merge secuencial: " << (t_mer / t_quick) << "x\n";
}

int main() {
    // Pruebas con diferentes tamaños
    runBenchmark(1000000);   // 1 millón
    runBenchmark(5000000);   // 5 millones
    runBenchmark(10000000);  // 10 millones
    runBenchmark(20000000);  // 20 millones

    return 0;
}