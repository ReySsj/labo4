#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Función: allocateMatrix
 * ------------------------
 * Reserva memoria dinámicamente para una matriz cuadrada de tamaño dado.
 */
void allocateMatrix(int ***matrix, int size) {
    *matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        *(*matrix + i) = (int *)malloc(size * sizeof(int));
    }
}

/*
 * Función: fillMatrix
 * --------------------
 * Llena la matriz con valores binarios aleatorios (0 o 1).
 */
void fillMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            *(*(matrix + i) + j) = rand() % 2;
        }
    }
}

/*
 * Función: printMatrix
 * ---------------------
 * Imprime la matriz.
 */
void printMatrix(int **matrix, int size) {
    printf("Matriz generada (%dx%d):\n", size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

/*
 * Función: findLongestLineOfOnes
 * -------------------------------
 * Recorre la matriz en orden fila por fila usando aritmética de punteros
 * y encuentra la secuencia más larga de 1s consecutivos.
 */
void findLongestLineOfOnes(int **matrix, int size, int *result) {
    int maxStreak = 0;
    int currentStreak = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (*(*(matrix + i) + j) == 1) {
                currentStreak++;
                if (currentStreak > maxStreak) {
                    maxStreak = currentStreak;
                }
            } else {
                currentStreak = 0;
            }
        }
    }

    *result = maxStreak;
}

/*
 * Función: freeMatrix
 * --------------------
 * Libera la memoria reservada dinámicamente para la matriz.
 */
void freeMatrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(*(matrix + i));
    }
    free(matrix);
}

/*
 * Función principal
 */
int main() {
    int size;
    int **matrix = NULL;
    int maxLineLength;

    // Inicializamos la semilla aleatoria
    srand(time(NULL));

    // Solicitamos el tamaño de la matriz
    printf("Ingrese el tamano de la matriz cuadrada: ");
    scanf("%d", &size);

    // Reservamos memoria y llenamos la matriz
    allocateMatrix(&matrix, size);
    fillMatrix(matrix, size);
    printMatrix(matrix, size);

    // Se busca la secuencia de 1s mas larga
    findLongestLineOfOnes(matrix, size, &maxLineLength);
    printf("La secuencia de 1s mas larga tiene longitud: %d\n", maxLineLength);

    // Liberamos la memoria 
    freeMatrix(matrix, size);

    return 0;
}
