#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;

/*
Naive:
Multiplicación clásica de matrices cuadradas.
Complejidad: O(n^3)
*/
Matrix naive(Matrix& A, Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}
