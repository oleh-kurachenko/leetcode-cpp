#include <stdlib.h>

int less_int(const void *v1, const void *v2) {
    return *(int *) v1 - *(int *) v2;
}

int largestSubmatrix(int **matrix, int matrixSize, int *matrixColSize) {
    for (size_t i = 1; i < matrixSize; i++) {
        for (size_t j = 0; j < matrixColSize[0]; j++) {
            if (matrix[i][j] != 0) {
                matrix[i][j] += matrix[i - 1][j];
            }
        }
    }

    for (size_t i = 0; i < matrixSize; i++) {
        qsort(matrix[i], matrixColSize[0], sizeof(int), less_int);
    }

    int result = 0;

    for (size_t i = 0; i < matrixSize; i++) {
        for (size_t j = 0; j < matrixColSize[0]; ++j) {
            if (matrix[i][j] != 0) {
                const int submatrix_size = (int) (
                    matrix[i][j] * (matrixColSize[0] - j));
                result = result < submatrix_size ? submatrix_size : result;
            }
        }
    }

    return result;
}
