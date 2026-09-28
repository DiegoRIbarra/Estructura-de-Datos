#include <iostream>
#include <vector>

// Usamos define para que sea fácil cambiar el tamaño del tablero si quisieras
#define N 8

using namespace std;

/**
 * Función para imprimir el tablero de ajedrez.
 * Se ve "bonito" con coordenadas.
 */
void printBoard(int board[N][N]) {
    cout << "\n    "; // Espacio para los encabezados de columna
    for (int i = 0; i < N; i++) {
        cout << " " << (char)('a' + i) << "  ";
    }
    cout << "\n  +---+---+---+---+---+---+---+---+\n";

    for (int i = 0; i < N; i++) {
        cout << i + 1 << " |"; // Encabezado de fila
        for (int j = 0; j < N; j++) {
            // Imprime 'Q' si hay una reina, '.' si está vacío
            cout << " " << (board[i][j] ? 'Q' : '.') << " |";
        }
        cout << "\n  +---+---+---+---+---+---+---+---+\n";
    }
}

/**
 * Función de utilidad para checar si una reina puede ser colocada
 * en board[row][col].
 * Solo necesitamos checar el lado izquierdo (columnas anteriores)
 * porque vamos llenando el tablero de izquierda a derecha.
 */
bool isSafe(int board[N][N], int row, int col) {
    int i, j;

    // 1. Checar la fila hacia la izquierda
    for (i = 0; i < col; i++) {
        if (board[row][i]) {
            return false;
        }
    }

    // 2. Checar la diagonal superior izquierda
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    // 3. Checar la diagonal inferior izquierda
    for (i = row, j = col; j >= 0 && i < N; i++, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    // Si pasó todas las pruebas, es seguro
    return true;
}

/**
 * La función principal de backtracking para resolver el problema.
 * Recibe el tablero, la columna actual en la que estamos trabajando
 * y un contador de soluciones.
 */
void solveNQueens(int board[N][N], int col, int& solutionCount) {
    // --- Caso Base ---
    // Si ya pasamos la última columna (col == N),
    // significa que logramos poner las 8 reinas.
    if (col == N) {
        solutionCount++;
        cout << "\n--- Solución #" << solutionCount << " ---";
        printBoard(board);
        return; // No retornamos 'true', solo contamos y seguimos buscando
    }

    // --- Paso Recursivo ---
    // Considerar esta columna (col) e intentar poner
    // una reina en cada una de las filas (i).
    for (int i = 0; i < N; i++) {
        // 1. Checar si es seguro poner la reina en board[i][col]
        if (isSafe(board, i, col)) {
            
            // 2. Colocar la reina (Acción)
            board[i][col] = 1;

            // 3. Llamada recursiva (Explorar)
            // Llama a la función para la SIGUIENTE columna (col + 1)
            solveNQueens(board, col + 1, solutionCount);

            // 4. Backtrack (Deshacer)
            // Si la llamada recursiva termina (ya sea porque encontró
            // una solución o porque llegó a un callejón sin salida),
            // quitamos la reina para probar la siguiente fila.
            board[i][col] = 0; 
        }
    }
    
    // Si el 'for' termina, significa que probamos todas las filas
    // en esta columna y regresamos a la llamada anterior.
}

/**
 * Función main
 */
int main() {
    // Inicializar el tablero a 0 (vacío)
    int board[N][N] = { {0} };
    int solutionCount = 0;

    cout << "Buscando todas las soluciones para el problema de las " << N << " reinas...\n";
    
    // Empezamos a resolver desde la primera columna (columna 0)
    solveNQueens(board, 0, solutionCount);

    if (solutionCount == 0) {
        cout << "No se encontró ninguna solución.\n";
    } else {
        cout << "\n¡Se encontraron " << solutionCount << " soluciones en total!\n";
    }

    return 0;
}